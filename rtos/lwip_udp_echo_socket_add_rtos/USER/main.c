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

static TaskHandle_t AppTaskCreate_Handle = NULL;						/* ���������� */
static TaskHandle_t Test1_Task_Handle = NULL;							/* LED������ */
static TaskHandle_t Test2_Task_Handle = NULL;							/* KEY������ */

static void AppTaskCreate(void);										/* ���ڴ������� */
static void Test1_Task(void* pvParameters);								/* Test1_Task����ʵ�� */
static void Test2_Task(void* pvParameters);								/* Test2_Task����ʵ�� */

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
 ** �������ƣ�fputc
 ** �������ܣ��ض���fputc��ӡ�ַ�����
 ** ���������ch:��ӡ�ַ�
 ** �����������
 ** ���ز�����ch:��ӡ�ַ�
 ********************************************************************/
int fputc(int ch, FILE *f)
{
	UART_SendChar(UART0, (char)ch);
	return ch;
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
	uint32_t temp_cnt = 1;
	GPIO_IntClear(GPIO0, KEY_PIN);												//���gpio�ж�
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

	SPI_InitStruct.CLKSEL= CLKSEL_CLK_DIV_4;						//����SPIʱ��Ƶ�ʣ�ϵͳ4��Ƶ
	SPI_InitStruct.DIRECTION = DISABLE;								
	SPI_InitStruct.PHASE =DISABLE;									
	SPI_InitStruct.POLARITY =DISABLE;								

	SPI_Init(&SPI_InitStruct);
	SPI_CS_ENABLE;													//SPIƬѡ����
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
		if(iic_irq_cnt%32 == 0)
		{
			DEBUG_P("EEPROM irq cnt = %d!!!! \n",iic_irq_cnt);
		}
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
 ** �������ƣ�Test1_Task
 ** �������ܣ�Test1_Task����
 ** �����������
 ** �����������
 ** ���ز�������
�����������������ó�Ϊͨ���������п��Ƶĺ�������������ĿҪ��
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
 ** �������ƣ�Test2_Task
 ** �������ܣ�Test2_Task����
 ** �����������
 ** �����������
 ** ���ز�������
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
 ** �������ƣ�AppTaskCreate
 ** �������ܣ�Ϊ�˷���������е����񴴽����������������������
 ** �����������
 ** �����������
 ** ���ز�������
 ********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;											/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	TCPIP_Init();	
	udpecho_init();		// ��������������udp��Ӧ���ܵġ�

	//DEBUG_P("��������ʾUDP����ʵ��,���Է������ݵ�������,�����彫���ݷ��ص�������\n\n");

	//DEBUG_P("��������ģ�����£�\n\t ����<--����-->·��<--����-->������\n\n");

	//DEBUG_P("�����̵�IP��ַ����User/arch/sys_arch.h�ļ����޸�\n\n");

	//DEBUG_P("�����̲ο�<<LwIPӦ��ʵս����ָ��>> ʹ�� NETCONN �ӿڱ��\n\n");

	//DEBUG_P("�����޸�IP��ַ��˿ںţ����޸Ķ�Ӧ�ĺ궨��:IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3,LOCAL_PORT\n\n"); 

	/* ����Test1_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Test1_Task, 						/* ������ں��� */
						(const char*    )"Test1_Task",						/* �������� */
						(uint16_t       )512,   							/* ����ջ��С */
						(void*          )NULL,								/* ������ں������� */
						(UBaseType_t    )1,	    							/* ��������ȼ� */
						(TaskHandle_t*  )&Test1_Task_Handle);				/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
	DEBUG_P("Create Test1_Task sucess...\r\n");

	/* ����Test2_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Test2_Task,  					/* ������ں��� */
						(const char*    )"Test2_Task",						/* �������� */
						(uint16_t       )512,  								/* ����ջ��С */
						(void*          )NULL,								/* ������ں������� */
						(UBaseType_t    )2, 								/* ��������ȼ� */
						(TaskHandle_t*  )&Test2_Task_Handle);				/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	DEBUG_P("Create Test2_Task sucess...\n\n");

	vTaskDelete(AppTaskCreate_Handle); 										/* ɾ��AppTaskCreate���� */
}
char        write_buf[] = "123456";
UINT        bw;
FATFS fatfs;   ///����һ���ļ�ϵͳ���� 
FIL         fp;
FRESULT res;
//#define _MAX_SS 64
int main(void)
{
	BaseType_t xReturn = pdPASS;											/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	SystemInit();
	TimerInit();
	GpioInit();
	UartInit();
	/* ����AppTaskCreate���� */
	//	// ���´�����Ϊ�˲����ļ�ϵͳ
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
	
	
	xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  					/* ������ں��� */
                        (const char*    )"AppTaskCreate",					/* �������� */
                        (uint16_t       )512,  								/* ����ջ��С */
                        (void*          )NULL,								/* ������ں������� */
                        (UBaseType_t    )1, 								/* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);			/* ������ƿ�ָ�� */ 							
	DEBUG_P("PANGO Cortex-M1 FreeRTOS Start Run......\r\n");
	DEBUG_P("JEDEC  id = 0x%x\r\n",SFLASH_ReadJEDEC_ID());


	/* ����������� */           
	if(pdPASS == xReturn)
		vTaskStartScheduler();   /* �������񣬿������� */
	else
		return -1;

    while(1)
	{
		Delay(200);
	}
}



