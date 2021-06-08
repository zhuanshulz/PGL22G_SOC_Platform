#include "PANGO_M1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "udp_echo.h"
#include "sys_arch.h"
#include "PANGO_sdcard.h"
#include "ff.h"
#include "diskio.h"

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

static TaskHandle_t AppTaskCreate_Handle = NULL;						/* 创建任务句柄 */
static TaskHandle_t Test1_Task_Handle = NULL;							/* LED任务句柄 */
static TaskHandle_t Test2_Task_Handle = NULL;							/* KEY任务句柄 */

static void AppTaskCreate(void);										/* 用于创建任务 */
static void Test1_Task(void* pvParameters);								/* Test1_Task任务实现 */
static void Test2_Task(void* pvParameters);								/* Test2_Task任务实现 */

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
 ** 函数名称：fputc
 ** 函数功能：重定义fputc打印字符函数
 ** 输入参数：ch:打印字符
 ** 输出参数：无
 ** 返回参数：ch:打印字符
 ********************************************************************/
int fputc(int ch, FILE *f)
{
	UART_SendChar(UART0, (char)ch);
	return ch;
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
		if(iic_irq_cnt%32 == 0)
		{
			DEBUG_P("EEPROM irq cnt = %d!!!! \n",iic_irq_cnt);
		}
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
	for(j=0; j<10; j++)
	{
		Memory_Write_Bytes(BANK_RAM_BASE1 + j*4, j + 20);
	}
	DEBUG_P("Get BANK_RAM_BASE1 Data = ");
	for(j=0; j<10; j++)
	{
		DEBUG_P(" %d", Memory_Read_Bytes(BANK_RAM_BASE1 + j*4));
	}
	DEBUG_P("\r\n");
	for(j=0; j<10; j++)
	{
		Memory_Write_Bytes(BANK_RAM_BASE2 + j*4, j + 30);
	}
	DEBUG_P("Get BANK_RAM_BASE2 Data = ");
	for(j=0; j<10; j++)
	{
		DEBUG_P(" %d", Memory_Read_Bytes(BANK_RAM_BASE2 + j*4));
	}
	DEBUG_P("\r\n");
	for(j=0; j<10; j++)
	{
		Memory_Write_Bytes(BANK_RAM_BASE3 + j*4, j + 40);
	}
	DEBUG_P("Get BANK_RAM_BASE3 Data = ");
	for(j=0; j<10; j++)
	{
		DEBUG_P(" %d", Memory_Read_Bytes(BANK_RAM_BASE3 + j*4));
	}
	DEBUG_P("\r\n");
}

/********************************************************************
 ** 函数名称：Test1_Task
 ** 函数功能：Test1_Task任务
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
这个函数这里可以设置成为通过按键进行控制的函数，以满足题目要求
 ********************************************************************/
static void Test1_Task(void* parameter)
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
 ** 函数名称：Test2_Task
 ** 函数功能：Test2_Task任务
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
static void Test2_Task(void* parameter)
{	 
	static uint32_t test_cnt = 0;
	while(1)
	{
		vTaskDelay(500);
		test_cnt++;
		if(test_cnt == LED_CNT*2)
		{
//			DEBUG_P("Test2_Task......\n");
			test_cnt = 0;
		}
	}
}

/********************************************************************
 ** 函数名称：AppTaskCreate
 ** 函数功能：为了方便管理，所有的任务创建函数都放在这个函数里面
 ** 输入参数：无
 ** 输出参数：无
 ** 返回参数：无
 ********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;											/* 定义一个创建信息返回值，默认为pdPASS */
	
	TCPIP_Init();	
	udpecho_init();		// 这个任务就是启动udp回应功能的。

	//DEBUG_P("本例程演示UDP回显实验,电脑发送数据到开发板,开发板将数据返回到电脑上\n\n");

	//DEBUG_P("网络连接模型如下：\n\t 电脑<--网线-->路由<--网线-->开发板\n\n");

	//DEBUG_P("本例程的IP地址均在User/arch/sys_arch.h文件中修改\n\n");

	//DEBUG_P("本例程参考<<LwIP应用实战开发指南>> 使用 NETCONN 接口编程\n\n");

	//DEBUG_P("如需修改IP地址与端口号，则修改对应的宏定义:IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3,LOCAL_PORT\n\n"); 

	/* 创建Test1_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Test1_Task, 						/* 任务入口函数 */
						(const char*    )"Test1_Task",						/* 任务名字 */
						(uint16_t       )512,   							/* 任务栈大小 */
						(void*          )NULL,								/* 任务入口函数参数 */
						(UBaseType_t    )1,	    							/* 任务的优先级 */
						(TaskHandle_t*  )&Test1_Task_Handle);				/* 任务控制块指针 */
	if(pdPASS == xReturn)
	DEBUG_P("Create Test1_Task sucess...\r\n");

	/* 创建Test2_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Test2_Task,  					/* 任务入口函数 */
						(const char*    )"Test2_Task",						/* 任务名字 */
						(uint16_t       )512,  								/* 任务栈大小 */
						(void*          )NULL,								/* 任务入口函数参数 */
						(UBaseType_t    )2, 								/* 任务的优先级 */
						(TaskHandle_t*  )&Test2_Task_Handle);				/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	DEBUG_P("Create Test2_Task sucess...\n\n");

	vTaskDelete(AppTaskCreate_Handle); 										/* 删除AppTaskCreate任务 */
}
char        write_buf[] = "123456";
UINT        bw;
FATFS fatfs;   ///定义一个文件系统对象 
FIL         fp;
FRESULT res;
//#define _MAX_SS 64
int main(void)
{
	BaseType_t xReturn = pdPASS;											/* 定义一个创建信息返回值，默认为pdPASS */
	SystemInit();
	TimerInit();
	GpioInit();
	UartInit();
	/* 创建AppTaskCreate任务 */
	//	// 以下代码是为了测试文件系统
	static unsigned char buffer[1024];
	res = f_mount(&fatfs, "0:", 1);
	if(res == FR_OK){
		 res = f_open(&fp, "0:ABC.jpg", FA_READ);
		res = f_read(&fp, buffer, 24, &bw);
		DEBUG_P("\r\n f_read res = %d , read_buf = \r\n", res);
		for(int i =0;i<24;i++)
			DEBUG_P(" %x ", buffer[i]);
		res = f_close(&fp);
	}
	else 
		DEBUG_P("\r\n file system error \r\n");
	
	
	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  					/* 任务入口函数 */
                        (const char*    )"AppTaskCreate",					/* 任务名字 */
                        (uint16_t       )512,  								/* 任务栈大小 */
                        (void*          )NULL,								/* 任务入口函数参数 */
                        (UBaseType_t    )1, 								/* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);			/* 任务控制块指针 */ 							
	DEBUG_P("PANGO Cortex-M1 FreeRTOS Start Run......\r\n");
	DEBUG_P("JEDEC  id = 0x%x\r\n",SFLASH_ReadJEDEC_ID());


	/* 启动任务调度 */           
	if(pdPASS == xReturn)
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	else
		return -1;

    while(1)
	{
		Delay(200);
	}
}



