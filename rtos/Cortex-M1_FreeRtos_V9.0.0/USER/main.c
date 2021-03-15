#include "PANGO_M1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#define DELAY_CNT		8000000
#define LED_CNT			(2)
#define KEY_PIN			GPIO_Pin_0
#define LED_PIN			GPIO_Pin_1
#define UART0_Baud		115200
#define WATCH_DOG 		800000000
#define DATA_LEN		64									//注意：IIC单独页操作数据长度必须是页的最小单位（即：64的整数倍）
#define SPI_DATA_LEN	100	
#define IIC_DATA_ADD	0									//数据读写起始地址
#define BUF_SIZE		32
#define SPI_DATA_ADD	0x100000							//SPI数据读写起始地址
//#define DDR_DATA_ADD	0x100000							//DDR数据读写起始地址

uint8_t Outburst_Len = 8;	
uint32_t temp_state = 0;
uint32_t data_len = 0;
uint32_t set_buf[BUF_SIZE];
uint32_t get_buf[BUF_SIZE];

volatile bool key_flag = false;
volatile uint32_t timer_counter = 0;
volatile uint32_t wdg_counter = 0;
uint32_t wdg_value = 0;
uint32_t key_temp_cnt = 0;
uint16_t iic_irq_cnt = 0;

char  send_buf1[SPI_DATA_LEN];
char  read_buf1[SPI_DATA_LEN];
char  send_buf2[DATA_LEN];
char  read_buf2[DATA_LEN];
void GpioInit(void);
void TimerInit(void);
void UartInit(void);
void SPIInit0(void);
void SPI_Flash_Test(void);
void WatchDogInit(unsigned int cycle, int type);
                                       /* Program watchdog: */
                                       /* type = 0 : No action */
                                       /* type = 1 : Interrupt */
                                       /* type = 2 : Reset */
void watchdog_set(unsigned int cycle);
void I2CInit(void);
void DDRInit(uint8_t burst_len);
void Smemory_test(void);
void DDR_test(void);
void Timer_test(int cnt);

xTimerHandle SoftTmr = NULL;									//软件定时器句柄
xQueueHandle Queue1 = NULL;										//消息队列句柄
#define Queue1_Length	10										//消息个数
#define Queue1_ItemSize	10										//每个消息的大小（字节长度）
#define UART_TASK  	"UART"										//UART消息传输
#define SPI_TASK  	"SPI"										//SPI消息传输
#define IIC_TASK  	"IIC"										//IIC消息传输
#define DDR_TASK  	"DDR"										//DDR消息传输
#define MEMORY_TASK "MEMORY"									//MEMORY消息传输
void vApplicationTickHook()
{
}

void vApplicationMallocFailedHook()
{
}

void vApplicationStackOverflowHook()
{
}

/********************************************************************
 ** 函数名称：Delay
 ** 函数功能：延时函数
 ** 输入参数：nCount:延时计数值
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

/********************************************************************
 ** 函数名称：GpioInit
 ** 函数功能：GPIO初始化函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void GpioInit(void)
{
	GPIO_InitTypeDef GPIO_0_0;
	GPIO_0_0.GPIO_Pin = KEY_PIN;
	GPIO_0_0.GPIO_Mode = GPIO_Mode_IN;										//设置GPIO_Pin_0为输入模式
	GPIO_0_0.GPIO_Int = GPIO_Int_Falling_Edge;								//设置GPIO_Pin_0为下降沿触发
	GPIO_Init(GPIO0, &GPIO_0_0);
	NVIC_EnableIRQ(GPIO0_IRQn);
	
	GPIO_InitTypeDef GPIO_0_1;
	GPIO_0_1.GPIO_Pin = LED_PIN;
	GPIO_0_1.GPIO_Mode = GPIO_Mode_OUT;										//设置GPIO_Pin_1为输入模式
	GPIO_0_1.GPIO_Int = GPIO_Int_Disable;									//设置GPIO_Pin_1为普通IO，不设置中断模式
	GPIO_Init(GPIO0, &GPIO_0_1);
}

/********************************************************************
 ** 函数名称：GPIO0_Handler
 ** 函数功能：GPIO中断函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void GPIO0_Handler(void)
{
	uint32_t temp_cnt = 1;
	GPIO_IntClear(GPIO0, KEY_PIN);												//清除gpio中断
	while(!(GPIO_ReadBits(GPIO0)&0x0001))
	{
		temp_cnt++;
		if(temp_cnt >= 0x1000000)
		{
			temp_cnt = 0;
			break;
		}
	}
	if(temp_cnt == 0)
	{
		key_flag = false;
	}
	else
	{
		key_flag = true;
	}
}

/********************************************************************
 ** 函数名称：TimerInit
 ** 函数功能：定时器初始化函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void TimerInit(void)
{
	TIMER_InitTypeDef TIME_InitStruct;
	TIME_InitStruct.Reload = SystemCoreClock;						//设置定时器中断触发时间为1s(根据需求设置中断触发时间)
	TIME_InitStruct.TIMER_Exti = TIMER_DISABLE;						//关闭外部触发定时器中断
	TIME_InitStruct.TIMER_Int = ENABLE;								//打开定时器中断
	
	TIMER_Init(TIMER0, &TIME_InitStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);									//初始化定时器中断
}

/********************************************************************
 ** 函数名称：TIMER0_Handler
 ** 函数功能：定时器中断函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void TIMER0_Handler(void)
{
	if(TIMER_GetIRQStatus(TIMER0) != RESET)
	{
		timer_counter++;
		TIMER_ClearIRQ(TIMER0);											//清除定时器中断
	}
}

/********************************************************************
 ** 函数名称：UartInit
 ** 函数功能：串口初始化函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void UartInit(void)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;					//打开串口发送模式
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;					//打开串口接收模式
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;					//关闭串口发送中断
	UART_InitStruct.UART_Int.UARTInt_Rx = ENABLE;					//使能串口接收中断
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;					//关闭串口发送溢出
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = ENABLE;					//打开串口接收溢出中断
	UART_InitStruct.UART_Hstm = DISABLE;							//关闭串口快速模式
	UART_InitStruct.UART_BaudRate = UART0_Baud;						//设置串口波特率

	UART_Init(UART0, &UART_InitStruct);
	NVIC_EnableIRQ(UART0_IRQn);										//初始化串口中断
}

/********************************************************************
 ** 函数名称：UART0_Handler
 ** 函数功能：串口中断函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void UART0_Handler(void)
{
	if(UART_GetRxIRQStatus(UART0) != RESET)
	{
		UART_ClearRxIRQ(UART0);										//清除串口中断
		UART_SendChar(UART0, UART_ReceiveChar(UART0));				//打印接收到的数据
	}
}

/********************************************************************
 ** 函数名称：SPIInit0
 ** 函数功能：SPI初始化(用户只可以设置分频系数，其他设置操作无效)
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void SPIInit0(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	SPI_InitStruct.CLKSEL= CLKSEL_CLK_DIV_4;						//设置SPI时钟频率，系统4分频
	SPI_InitStruct.DIRECTION = DISABLE;								
	SPI_InitStruct.PHASE =DISABLE;									
	SPI_InitStruct.POLARITY =DISABLE;								

	SPI_Init(&SPI_InitStruct);
	SPI_CS_ENABLE;													//SPI片选拉高
}

/********************************************************************
 ** 函数名称：SPI_Flash_Test
 ** 函数功能：SPI Flash循环读写测试
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void SPI_Flash_Test(void)
{
	for(int j = 0;j < DATA_LEN; j++)
	{
		send_buf1[j] = j+ 1;
		read_buf1[j] = 0;
	}
	SFLASH_WriteNByte((uint8_t*)send_buf1, 0, DATA_LEN); 		//写入send_buf，数据长度为DATA_LEN		
	SFLASH_ReadNByte((uint8_t*)read_buf1, 0, DATA_LEN);  		//读出read_buf，数据长度为DATA_LEN            
	if(!strncmp(send_buf1, read_buf1, DATA_LEN))
	{
		DEBUG_P("SPI Read data OK!!!! \n");
	}
	else
	{
		DEBUG_P("SPI Read data ERROR!!!! \n");
	}
}

/********************************************************************
 ** 函数名称：WatchDogInit
 ** 函数功能：看门狗初始化
** 输入参数：cycle:喂狗超时计数值
**			 type:看门狗类型
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void WatchDogInit(unsigned int cycle, int type)
{
	UART_SendString(UART0,"WatchDog Initialization!\r\n");
	WDOG_UnlockWriteAccess();

	WDOG_RestartCounter(cycle);									//设置喂狗超时计数器
	if (type==0)
	{
		WDOG->CTRL = 0;
	}
	else if (type==1)
	{
		WDOG_SetIntEnable();
	}
	else
	{
		WDOG->CTRL = 3;
	}

	WDOG_LockWriteAccess();
	NVIC_EnableIRQ(NonMaskableInt_IRQn);						//初始化看门狗中断
}

/********************************************************************
 ** 函数名称：watchdog_set
 ** 函数功能：更新看门狗计时参数
** 输入参数：cycle:喂狗超时计数值
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void watchdog_set(unsigned int cycle)
{
	WDOG_UnlockWriteAccess();
	WDOG_RestartCounter(cycle);
	WDOG_LockWriteAccess();
}

/********************************************************************
 ** 函数名称：NMI_Handler
 ** 函数功能：看门狗中断处理函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void NMI_Handler(void)
{
	while(1);
	/*wdg_counter = 4;
	WDOG_UnlockWriteAccess();
	WDOG_ClrIntEnable();
	WDOG_LockWriteAccess();*/
}

/********************************************************************
 ** 函数名称：I2CInit
 ** 函数功能：IIC初始化函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void I2CInit(void)
{
	I2C_Init(I2C, EEPROM_SPEED, EEPROM_IRQ);					
	NVIC_EnableIRQ(I2C_IRQn);
	NVIC_SetPriority(I2C_IRQn, 0);								//IIC中断优先级1
}

/********************************************************************
 ** 函数名称：IIC_Test
 ** 函数功能：IIC_Test循环读写测试
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void IIC_Test(void)
{
	for(int j = 0;j < DATA_LEN; j++)
	{
		send_buf2[j] = j+ 1;
		read_buf2[j] = 0;
	}
	I2C_EE_BufferWrite(I2C, (uint8_t*)send_buf2, IIC_DATA_ADD, DATA_LEN);
	I2C_EE_BufferRead(I2C, (uint8_t*)read_buf2, IIC_DATA_ADD, DATA_LEN);
	DEBUG_P("EEPROM irq cnt = %d!!!! \n",iic_irq_cnt);
	iic_irq_cnt = 0;
	if(!strncmp(send_buf2, read_buf2, DATA_LEN))
	{
		DEBUG_P("EEPROM Read data OK,EEPROM_SPEED = %dKHz!!!! \n",EEPROM_SPEED);
	}
	else
	{
		for(int i = 0;i < DATA_LEN; i++)
		{
			DEBUG_P("\n%d %d",send_buf2[i], read_buf2[i]);
		}
		DEBUG_P("\nEEPROM Read data ERROR!!! \n");
	}
}

/********************************************************************
 ** 函数名称：I2C_Handler
 ** 函数功能：IIC中断函数(在接收到从机ack/stop信号时，触发中断)
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void I2C_Handler(void)
{
	if(~(I2C->SR &I2C_SR_TIP))											//Translate Over
	{
		iic_irq_cnt++;
	}
	
	I2C->CR = I2C_CMD_IACK;												//Clear the Interrupt Flag
}
/********************************************************************
 ** 函数名称：Smemory_test
 ** 函数功能：Smemory读写测试
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void Smemory_test(void)
{
	int j = 0;
	for(j=0; j<10; j++)
	{
		Memory_Write_Bytes(BANK_RAM_BASE0 + j*4, j + 10);
	}
	DEBUG_P("Get BANK_RAM_BASE0 Data = ");
	for(j=0; j<10; j++)
	{
		DEBUG_P(" %d", Memory_Read_Bytes(BANK_RAM_BASE0 + j*4));
	}
	DEBUG_P("\r\n");
}

/********************************************************************
 ** 函数名称：queue_task
 ** 函数功能：消息接收处理任务
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void queue_task(void *temp)
{
	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(3000);							//设置最大等待时间(阻塞时间)
	uint8_t receive_buf[10] = {0};
	while(1)
	{
		xResult = xQueueReceive(Queue1, 											//消息队列句柄
								receive_buf, 										//接收消息缓存
								(TickType_t)xMaxBlockTime);							//设置阻塞时间
		if(pdPASS == xResult)
		{
			if(!memcmp(receive_buf, SPI_TASK, sizeof(SPI_TASK)))//memcmp 返回值：若参数s1 和s2 所指的内存内容都完全相同则返回0 值。
																													//s1 若大于s2 则返回大于0 的值。s1 若小于s2 则返回小于0 的值。
			{
				SPI_Flash_Test();
			}
//			else if(!memcmp(receive_buf, IIC_TASK, sizeof(IIC_TASK)))
//			{
//				IIC_Test();
//			}
			else if(!memcmp(receive_buf, MEMORY_TASK, sizeof(MEMORY_TASK)))
			{
				Smemory_test();
			}
		}
		vTaskDelay(10);
	}
}

/********************************************************************
 ** 函数名称：led_task
 ** 函数功能：led闪烁任务
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void led_task(void *temp)
{
	static uint32_t led_cnt = 0;
	while(1)
	{
		vTaskDelay(500);
		led_cnt++;
		if(led_cnt == LED_CNT)
		{
			GPIO_SetBit(GPIO0,LED_PIN);
		}
		else if(led_cnt == LED_CNT*2)
		{
			GPIO_ResetBit(GPIO0,LED_PIN);
			led_cnt = 0;
		}
	}
}

/********************************************************************
 ** 函数名称：SoftTmr_Callback
 ** 函数功能：软定时器回调函数
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
void SoftTmr_Callback(void *temp)
{
	static uint32_t temp_cnt = 0;
	temp_cnt++;
	if((temp_cnt - 1)%3 == 0)
	{
		switch((temp_cnt - 1)/3)
		{
			case 0:
				if(xQueueSend(Queue1, SPI_TASK, (TickType_t)10) != pdPASS)						//向消息队列发送数据，如果消息队列满，等待10个系统时钟节拍
				{
					DEBUG_P("xQueueSend SPI_TASK Fail......\r\n");								//发送超时打印信息
				}
				else
				{
					DEBUG_P("xQueueSend SPI_TASK Success......\r\n");							//发送成功打印信息
				}
			break;
//			case 1:
//				if(xQueueSend(Queue1, IIC_TASK, (TickType_t)10) != pdPASS)						//向消息队列发送数据，如果消息队列满，等待10个系统时钟节拍
//				{
//					DEBUG_P("xQueueSend IIC_TASK Fail......\r\n");								//发送超时打印信息
//				}
//				else
//				{
//					DEBUG_P("xQueueSend IIC_TASK Success......\r\n");							//发送成功打印信息
//				}
//			break;
			case 2:
				if(xQueueSend(Queue1, MEMORY_TASK, (TickType_t)10) != pdPASS)					//向消息队列发送数据，如果消息队列满，等待10个系统时钟节拍
				{
					DEBUG_P("xQueueSend MEMORY_TASK Fail......\r\n");							//发送超时打印信息
				}
				else
				{
					DEBUG_P("xQueueSend MEMORY_TASK Success......\r\n");						//发送成功打印信息
				}
			break;
			default:
				temp_cnt = 0;
			break;
		}

	}
}


int main(void)
{
	SystemInit();
	TimerInit();
	GpioInit();
	UartInit();
	SPIInit0();
	I2CInit();								
	DEBUG_P("--- RTSO starting ---");
	
	DEBUG_P("PANGO Cortex-M1 FreeRTOS Start Run......\r\n");
	DEBUG_P("JEDEC  id = 0x%x\n",SFLASH_ReadJEDEC_ID());

	xTaskCreate(queue_task,"queue",80,NULL,1,NULL);
	xTaskCreate(led_task,"led",40,NULL,1,NULL);
	Queue1 = xQueueCreate(Queue1_Length, Queue1_ItemSize);
	if(0 == Queue1)
	{
		DEBUG_P("Queue1 Create Fail......\r\n");
		return 0;
	}
	SoftTmr = xTimerCreate(	"AutoReloadTimer", 
							(TickType_t)300, 							//定时器周期1000(tick)
							(UBaseType_t)pdTRUE, 						//周期模式
							(void *)1, 									//为每个计时器分配一个唯一ID
							(TimerCallbackFunction_t)SoftTmr_Callback);	//软定时器回调函数
	if(NULL != SoftTmr)
	{
		xTimerStart(SoftTmr, 0);						//开启定时器
	}
	vTaskStartScheduler();
	while(1)
	{
		Delay(200);
	}
}
