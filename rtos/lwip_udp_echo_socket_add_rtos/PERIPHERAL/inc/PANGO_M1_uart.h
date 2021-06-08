#ifndef PANGO_M1_UART_H
#define PANGO_M1_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"

typedef struct
{
  FunctionalState UARTMode_Tx;  	/* TX使能 */
  FunctionalState UARTMode_Rx;  	/* RX使能 */
}UARTMode_TypeDef;

typedef struct
{
  FunctionalState UARTInt_Tx;  		/* Tx中断使能 */
  FunctionalState UARTInt_Rx;  		/* Rx中断使能 */
}UARTInt_TypeDef;

typedef struct
{
  FunctionalState UARTOvr_Tx;  		/* Tx溢出中断使能 */
  FunctionalState UARTOvr_Rx;  		/* Rx溢出中断使能 */
}UARTOvr_TypeDef;

typedef struct
{
  uint32_t UART_BaudRate;         /* 波特率      			*/

  UARTMode_TypeDef UART_Mode;     /* 串口模式（发送/接收）  */

  UARTInt_TypeDef UART_Int;       /* 串口中断           	*/

  UARTOvr_TypeDef UART_Ovr;       /* 串口溢出              	*/

  FunctionalState UART_Hstm;      /* 串口高速测试模式 		*/

}UART_InitTypeDef;

#define UART_STATE_TXBF_Pos     0  /* UART STATE: TXBF Position            */
#define UART_STATE_RXBF_Pos     1  /* UART STATE: RXBF Position            */
#define UART_STATE_TXOR_Pos     2  /* UART STATE: TXOR Position            */
#define UART_STATE_RXOR_Pos     3  /* UART STATE: RXOR Position            */

#define UART_CTRL_TXEN_Pos      0  /* UART CTRL: TXEN Position             */
#define UART_CTRL_RXEN_Pos      1  /* UART CTRL: RXEN Position             */
#define UART_CTRL_TXIRQEN_Pos   2  /* UART CTRL: TXIRQEN Position          */
#define UART_CTRL_RXIRQEN_Pos   3  /* UART CTRL: RXIRQEN Position          */
#define UART_CTRL_TXORIRQEN_Pos 4  /* UART CTRL: TXORIRQEN Position        */
#define UART_CTRL_RXORIRQEN_Pos 5  /* UART CTRL: RXORIRQEN Position        */
#define UART_CTRL_HSTM_Pos      6  /* UART CTRL: HSTM Position             */

#define UART_INTSTATUS_TXIRQ_Pos    0  /* UART INTSTATUS: TXIRQ Position  */
#define UART_INTSTATUS_RXIRQ_Pos    1  /* UART INTSTATUS: RXIRQ Position   */
#define UART_INTSTATUS_TXORIRQ_Pos  2  /* UART INTSTATUS: TXORIRQ Position */
#define UART_INTSTATUS_RXORIRQ_Pos  3  /* UART INTSTATUS: RXORIRQ Position */

#define UART_INTCLEAR_TXIRQ_Pos     0  /* UART INTCLEAR: TXIRQ Position    */
#define UART_INTCLEAR_RXIRQ_Pos     1  /* UART INTCLEAR: RXIRQ Position    */
#define UART_INTCLEAR_TXORIRQ_Pos   2  /* UART INTCLEAR: TXORIRQ Position  */
#define UART_INTCLEAR_RXORIRQ_Pos   3  /* UART INTCLEAR: RXORIRQ Position  */

extern ErrorStatus UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
extern FlagStatus UART_GetRxBufferFull(UART_TypeDef* UARTx);
extern FlagStatus UART_GetTxBufferFull(UART_TypeDef* UARTx);
extern FlagStatus UART_GetRxBufferOverrunStatus(UART_TypeDef* UARTx);
extern FlagStatus UART_GetTxBufferOverrunStatus(UART_TypeDef* UARTx);
extern void UART_ClearRxBufferOverrunStatus(UART_TypeDef* UARTx);
extern void UART_ClearTxBufferOverrunStatus(UART_TypeDef* UARTx);
extern void UART_SendChar(UART_TypeDef* UARTx, char txchar);
extern void UART_SendString(UART_TypeDef* UARTx, char *str);
extern char UART_ReceiveChar(UART_TypeDef* UARTx);
extern uint32_t UART_GetBaudDivider(UART_TypeDef* UARTx);
extern ITStatus UART_GetTxIRQStatus(UART_TypeDef* UARTx);
extern ITStatus UART_GetRxIRQStatus(UART_TypeDef* UARTx);
extern void UART_ClearTxIRQ(UART_TypeDef* UART);
extern void UART_ClearRxIRQ(UART_TypeDef* UART);
extern ITStatus UART_GetTxOverrunIRQStatus(UART_TypeDef* UARTx);
extern ITStatus UART_GetRxOverrunIRQStatus(UART_TypeDef* UARTx);
extern void UART_ClearTxOverrunIRQ(UART_TypeDef* UARTx);
extern void UART_ClearRxOverrunIRQ(UART_TypeDef* UARTx);
extern void UART_SetHSTM(UART_TypeDef* UARTx);
extern void UART_ClrHSTM(UART_TypeDef* UARTx);

#ifdef __cplusplus
}
#endif

#endif /* PANGO_M1_UART_H */
 

