#include "PANGO_M1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "PANGO_spi_flash.h"
#include "PANGO_sdcard.h"
//#include "ff.h"

#define DELAY_CNT		8000000
#define LED_CNT			(2)
#define KEY_PIN			GPIO_Pin_0					// input P17 key3
#define LED_PIN			GPIO_Pin_1					// output V10	LED2
#define UART0_Baud		115200
#define WATCH_DOG 		800000000
#define DATA_LEN		64									//ע�⣺IIC����ҳ�������ݳ��ȱ�����ҳ����С��λ������64����������
#define SPI_DATA_LEN	100	
#define IIC_DATA_ADD	0									//���ݶ�д��ʼ��ַ
#define BUF_SIZE		32
#define SPI_DATA_ADD	0x100000							//SPI���ݶ�д��ʼ��ַ
//#define DDR_DATA_ADD	0x100000							//DDR���ݶ�д��ʼ��ַ

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

xTimerHandle SoftTmr = NULL;									//�����ʱ�����
xQueueHandle Queue1 = NULL;										//��Ϣ���о��
#define Queue1_Length	10										//��Ϣ����
#define Queue1_ItemSize	10										//ÿ����Ϣ�Ĵ�С���ֽڳ��ȣ�
#define UART_TASK  	"UART"										//UART��Ϣ����
#define SPI_TASK  	"SPI"										//SPI��Ϣ����
#define IIC_TASK  	"IIC"										//IIC��Ϣ����
#define DDR_TASK  	"DDR"										//DDR��Ϣ����
#define MEMORY_TASK "MEMORY"									//MEMORY��Ϣ����

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
 ** �������ƣ�Delay
 ** �������ܣ���ʱ����
 ** ���������nCount:��ʱ����ֵ
 ** �����������
 ** ���ز�������
 ********************************************************************/
void Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

/********************************************************************
 ** �������ƣ�GpioInit
 ** �������ܣ�GPIO��ʼ������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void GpioInit(void)
{
	GPIO_InitTypeDef GPIO_0_0;
	GPIO_0_0.GPIO_Pin = KEY_PIN;
	GPIO_0_0.GPIO_Mode = GPIO_Mode_IN;										//����GPIO_Pin_0Ϊ����ģʽ
	GPIO_0_0.GPIO_Int = GPIO_Int_Falling_Edge;								//����GPIO_Pin_0Ϊ�½��ش���
	GPIO_Init(GPIO0, &GPIO_0_0);
	NVIC_EnableIRQ(GPIO0_IRQn);
	
	GPIO_InitTypeDef GPIO_0_1;
	GPIO_0_1.GPIO_Pin = LED_PIN;
	GPIO_0_1.GPIO_Mode = GPIO_Mode_OUT;										//����GPIO_Pin_1Ϊ����ģʽ
	GPIO_0_1.GPIO_Int = GPIO_Int_Disable;									//����GPIO_Pin_1Ϊ��ͨIO���������ж�ģʽ
	GPIO_Init(GPIO0, &GPIO_0_1);
}

/********************************************************************
 ** �������ƣ�GPIO0_Handler
 ** �������ܣ�GPIO�жϺ���
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void GPIO0_Handler(void)
{
	GPIO_IntClear(GPIO0, KEY_PIN);												//���gpio�ж�
	DEBUG_P("\n key input detected \n");
}

/********************************************************************
 ** �������ƣ�TimerInit
 ** �������ܣ���ʱ����ʼ������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void TimerInit(void)
{
	TIMER_InitTypeDef TIME_InitStruct;
	TIME_InitStruct.Reload = SystemCoreClock;						//���ö�ʱ���жϴ���ʱ��Ϊ1s(�������������жϴ���ʱ��)
	TIME_InitStruct.TIMER_Exti = TIMER_DISABLE;						//�ر��ⲿ������ʱ���ж�
	TIME_InitStruct.TIMER_Int = ENABLE;								//�򿪶�ʱ���ж�
	
	TIMER_Init(TIMER0, &TIME_InitStruct);
	NVIC_EnableIRQ(TIMER0_IRQn);									//��ʼ����ʱ���ж�
}

/********************************************************************
 ** �������ƣ�TIMER0_Handler
 ** �������ܣ���ʱ���жϺ���
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void TIMER0_Handler(void)
{
	if(TIMER_GetIRQStatus(TIMER0) != RESET)
	{
		timer_counter++;
		TIMER_ClearIRQ(TIMER0);											//�����ʱ���ж�
	}
}

/********************************************************************
 ** �������ƣ�UartInit
 ** �������ܣ����ڳ�ʼ������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void UartInit(void)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;					//�򿪴��ڷ���ģʽ
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;					//�򿪴��ڽ���ģʽ
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;					//�رմ��ڷ����ж�
	UART_InitStruct.UART_Int.UARTInt_Rx = ENABLE;					//ʹ�ܴ��ڽ����ж�
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;					//�رմ��ڷ������
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = ENABLE;					//�򿪴��ڽ�������ж�
	UART_InitStruct.UART_Hstm = DISABLE;							//�رմ��ڿ���ģʽ
	UART_InitStruct.UART_BaudRate = UART0_Baud;						//���ô��ڲ�����

	UART_Init(UART0, &UART_InitStruct);
	NVIC_EnableIRQ(UART0_IRQn);										//��ʼ�������ж�
}

/********************************************************************
 ** �������ƣ�UART0_Handler
 ** �������ܣ������жϺ���
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void UART0_Handler(void)
{
	if(UART_GetRxIRQStatus(UART0) != RESET)
	{
		UART_ClearRxIRQ(UART0);										//��������ж�
		UART_SendChar(UART0, UART_ReceiveChar(UART0));				//��ӡ���յ�������
	}
}

/********************************************************************
 ** �������ƣ�SPIInit0
 ** �������ܣ�SPI��ʼ��(�û�ֻ�������÷�Ƶϵ�����������ò�����Ч)
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void SPIInit0(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	SPI_InitStruct.CLKSEL= CLKSEL_CLK_DIV_32;						//����SPIʱ��Ƶ�ʣ�ϵͳ4��Ƶ
	SPI_InitStruct.DIRECTION = DISABLE;								
	SPI_InitStruct.PHASE =DISABLE;									
	SPI_InitStruct.POLARITY =DISABLE;								

	SPI_Init(&SPI_InitStruct);
	SPI0_CS_ENABLE;													//SPIƬѡ����
	SPI1_CS_ENABLE;													//SPIƬѡ����
}


/********************************************************************
 ** �������ƣ�SPI_Flash_Test
 ** �������ܣ�SPI Flashѭ����д����
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void SPI_Flash_Test(void)
{
	SPI_CS_DISABLE;
	for(int j = 0;j < DATA_LEN; j++)
	{
		send_buf1[j] = j+ 1;
		read_buf1[j] = 0;
	}
	SFLASH_WriteNByte((uint8_t*)send_buf1, 0, DATA_LEN); 		//д��send_buf�����ݳ���ΪDATA_LEN		
	SFLASH_ReadNByte((uint8_t*)read_buf1, 0, DATA_LEN);  		//����read_buf�����ݳ���ΪDATA_LEN            
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
 ** �������ƣ�WatchDogInit
 ** �������ܣ����Ź���ʼ��
** ���������cycle:ι����ʱ����ֵ
**			 type:���Ź�����
 ** �����������
 ** ���ز�������
 ********************************************************************/
void WatchDogInit(unsigned int cycle, int type)
{
	UART_SendString(UART0,"WatchDog Initialization!\r\n");
	WDOG_UnlockWriteAccess();

	WDOG_RestartCounter(cycle);									//����ι����ʱ������
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
	NVIC_EnableIRQ(NonMaskableInt_IRQn);						//��ʼ�����Ź��ж�
}

/********************************************************************
 ** �������ƣ�watchdog_set
 ** �������ܣ����¿��Ź���ʱ����
** ���������cycle:ι����ʱ����ֵ
 ** �����������
 ** ���ز�������
 ********************************************************************/
void watchdog_set(unsigned int cycle)
{
	WDOG_UnlockWriteAccess();
	WDOG_RestartCounter(cycle);
	WDOG_LockWriteAccess();
}

/********************************************************************
 ** �������ƣ�NMI_Handler
 ** �������ܣ����Ź��жϴ�����
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�I2CInit
 ** �������ܣ�IIC��ʼ������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void I2CInit(void)
{
	I2C_Init(I2C, EEPROM_SPEED, EEPROM_IRQ);					
	NVIC_EnableIRQ(I2C_IRQn);
	NVIC_SetPriority(I2C_IRQn, 0);								//IIC�ж����ȼ�1
}

/********************************************************************
 ** �������ƣ�IIC_Test
 ** �������ܣ�IIC_Testѭ����д����
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�I2C_Handler
 ** �������ܣ�IIC�жϺ���(�ڽ��յ��ӻ�ack/stop�ź�ʱ�������ж�)
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�Smemory_test
 ** �������ܣ�Smemory��д����
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�queue_task
 ** �������ܣ���Ϣ���մ�������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
void queue_task(void *temp)
{
	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(3000);							//�������ȴ�ʱ��(����ʱ��)
	uint8_t receive_buf[10] = {0};
	while(1)
	{
		xResult = xQueueReceive(Queue1, 											//��Ϣ���о��
								receive_buf, 										//������Ϣ����
								(TickType_t)xMaxBlockTime);							//��������ʱ��
		if(pdPASS == xResult)
		{
			if(!memcmp(receive_buf, SPI_TASK, sizeof(SPI_TASK)))//memcmp ����ֵ��������s1 ��s2 ��ָ���ڴ����ݶ���ȫ��ͬ�򷵻�0 ֵ��
																													//s1 ������s2 �򷵻ش���0 ��ֵ��s1 ��С��s2 �򷵻�С��0 ��ֵ��
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
 ** �������ƣ�led_task
 ** �������ܣ�led��˸����
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�SoftTmr_Callback
 ** �������ܣ���ʱ���ص�����
 ** �����������
 ** �����������
 ** ���ز�������
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
				if(xQueueSend(Queue1, SPI_TASK, (TickType_t)10) != pdPASS)						//����Ϣ���з������ݣ������Ϣ���������ȴ�10��ϵͳʱ�ӽ���
				{
					DEBUG_P("xQueueSend SPI_TASK Fail......\r\n");								//���ͳ�ʱ��ӡ��Ϣ
				}
				else
				{
					DEBUG_P("xQueueSend SPI_TASK Success......\r\n");							//���ͳɹ���ӡ��Ϣ
				}
			break;
//			case 1:
//				if(xQueueSend(Queue1, IIC_TASK, (TickType_t)10) != pdPASS)						//����Ϣ���з������ݣ������Ϣ���������ȴ�10��ϵͳʱ�ӽ���
//				{
//					DEBUG_P("xQueueSend IIC_TASK Fail......\r\n");								//���ͳ�ʱ��ӡ��Ϣ
//				}
//				else
//				{
//					DEBUG_P("xQueueSend IIC_TASK Success......\r\n");							//���ͳɹ���ӡ��Ϣ
//				}
//			break;
			case 2:
				if(xQueueSend(Queue1, MEMORY_TASK, (TickType_t)10) != pdPASS)					//����Ϣ���з������ݣ������Ϣ���������ȴ�10��ϵͳʱ�ӽ���
				{
					DEBUG_P("xQueueSend MEMORY_TASK Fail......\r\n");							//���ͳ�ʱ��ӡ��Ϣ
				}
				else
				{
					DEBUG_P("xQueueSend MEMORY_TASK Success......\r\n");						//���ͳɹ���ӡ��Ϣ
				}
			break;
			default:
				temp_cnt = 0;
			break;
		}

	}
}
#define cmd0_1  0x40
#define cmd0_2  0x00
#define cmd0_3  0x00
#define cmd0_4  0x00
#define cmd0_5  0x00
#define cmd0_6  0x95
#define cmd1		0xff

void test(void)
{
	Delay(2000000);
	SFLASH_WriteEnable();                          //дʹ��

	SPI1_CS_ENABLE;                                 //ʹ������
	SPI_WriteByte((uint8_t)(cmd0_1));     //����24bit��ַ
	SPI_WriteByte((uint8_t)(cmd0_2));
	SPI_WriteByte((uint8_t)cmd0_3);
	SPI_WriteByte((uint8_t)cmd0_4);
	SPI_WriteByte((uint8_t)cmd0_5);
	SPI_WriteByte((uint8_t)cmd0_6);
	uint8_t pBuffer;
	pBuffer = SPI_ReadByte();
	DEBUG_P("-----%x----",pBuffer);
	SPI_CS_DISABLE;
	SFLASH_WaitForNoBusy();                        //�ȴ����У��ȴ�д�������
}

int main(void)
{
	SystemInit();
	TimerInit();
	GpioInit();
	UartInit();
	SPIInit0();	//SPI0 for spi flash and spi sdcard device
	//I2CInit();								
	DEBUG_P("\n--- RTOS starting ---\n");
	while(1)
	{
			if (SD_Init()==1)
			{
				DEBUG_P("\n--- SD init success---\n");
				DEBUG_P("\n  %x   \n",(uint32_t)(SDCARD->INITIALISED));
				break;
			}
			else
				DEBUG_P("\n--- SD init failed---\n");
			Delay(200);
	}
	while(1)
	{
	}
//	Delay(2000000);
//		uint8_t pBuffer;
//	SPI_CS_DISABLE;
//	SPI1_CS_ENABLE;                                 //ʹ������
//	DEBUG_P("-");
//	SPI_WriteByte((uint8_t)(cmd0_1));     //����24bit��ַ
//	
//	SPI_WriteByte((uint8_t)(cmd0_2));
//	SPI_WriteByte((uint8_t)cmd0_3);
//	SPI_WriteByte((uint8_t)cmd0_4);
//	SPI_WriteByte((uint8_t)cmd0_5);
//	SPI_WriteByte((uint8_t)cmd0_6);
//// ����д����CMD0
//	while(1)
//	{
//	pBuffer = SPI_ReadByte();
//		if (pBuffer != 0xff)
//			break;
//			SPI_WriteByte((uint8_t)cmd1);
//	}
//	DEBUG_P("\n-----%x----\n",pBuffer);
//	
//	SPI_CS_DISABLE;
//	SFLASH_WaitForNoBusy();                        //�ȴ����У��ȴ�д��������������flash��ָ������������spi���裬�����sdcard������Ҫ��ӡ�
//	DEBUG_P("PANGO Cortex-M1 FreeRTOS Start Run......\r\n");
//	DEBUG_P("JEDEC  id = 0x%x\n",SFLASH_ReadJEDEC_ID());

//	xTaskCreate(queue_task,"queue",80,NULL,1,NULL);
//	xTaskCreate(led_task,"led",40,NULL,1,NULL);
//	Queue1 = xQueueCreate(Queue1_Length, Queue1_ItemSize);
//	if(0 == Queue1)
//	{
//		DEBUG_P("Queue1 Create Fail......\r\n");
//		return 0;
//	}
//	SoftTmr = xTimerCreate(	"AutoReloadTimer", 
//							(TickType_t)300, 							//��ʱ������1000(tick)
//							(UBaseType_t)pdTRUE, 						//����ģʽ
//							(void *)1, 									//Ϊÿ����ʱ������һ��ΨһID
//							(TimerCallbackFunction_t)SoftTmr_Callback);	//��ʱ���ص�����
//	if(NULL != SoftTmr)
//	{
//		xTimerStart(SoftTmr, 0);						//������ʱ��
//	}
//	vTaskStartScheduler();
	while(1)
	{
		Delay(200);
	}
}
