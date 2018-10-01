/*
 * usart2.c
 *
 *  Created on: Feb 12, 2015
 *      Author: TomB
 */

/*************************************************************************************************/

#include "usart2.h"
#include <misc.h>
#include "stm32f10x.h"
#include "typedefs.h"
#include "general.h"
#include "cycleBuffer.h"
#include "global.h"
#include "pins.h"
#include <stm32f10x_usart.h>

/*************************************************************************************************/

#define RxBufferNotEmptyInterrupt(usart) 	((usart)->SR & (1<<5))
#define ReceivedByte(usart) 				((usart)->DR)
#define SendByte(usart,byte)				((usart)->DR=(byte))
#define TxInterruptDisable(usart)			((usart)->CR1 &= ~(1<<7))
#define TxInterruptEnable(usart)			((usart)->CR1 |= (1<<7))
#define TxInterrupt(usart) 					(usart->SR & (1<<7))

/*************************************************************************************************/

void USART2_IRQHandler(void)
{
	// TX
	if (TxInterrupt(USART2))
	{
		static u8 b;

		if (CycleBuffer_GetNewByte(&usart2TxCycleBuffer, &b))
		{
			SendByte(USART2, b);
		}
		else TxInterruptDisable(USART2);
	}


	// RX (CLEAR ERRORS)
	volatile u32 temp UNUSED = USART2->SR; // This clears errors flags (overrun etc.)

	// RX
	if (RxBufferNotEmptyInterrupt(USART2))
	{
		CycleBuffer_Add(&usart2RxCycleBuffer, ReceivedByte(USART2));
	}
}

/*************************************************************************************************/

void Usart2_EnableTxInterrupt()
{
	TxInterruptEnable(USART2);
}

/*************************************************************************************************/

/*
 *
    256000:8:1:n
    Tx: A.2
    Rx: A.3
    NVIC Priority: 0+0
    Interrupts: Rx

 */

void Usart2_Init()
{
	USART_DeInit(USART2);

	// GPIO init
	Pin_Init(&(pin_t)PinA2, GPIO_Mode_AF_PP); // Tx pin
	Pin_Init(&(pin_t)PinA3, GPIO_Mode_IN_FLOATING); // Rx pin

	// USART INTERRUPT PRIORITY SET

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// USART INIT

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitTypeDef UsartConfig;
	UsartConfig.USART_BaudRate = 19200;
	UsartConfig.USART_WordLength = USART_WordLength_8b;
	UsartConfig.USART_StopBits = USART_StopBits_1;
	UsartConfig.USART_Parity = USART_Parity_No;
	UsartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UsartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &UsartConfig);

	USART2->CR1 |= (1<<7); // bit #7: TXEIE: TXE interrupt enable
	USART2->CR1 |= (1<<5); // bit #5: RXNEIE: RXNE interrupt enab

	// ENABLE UART
	USART_Cmd(USART2, ENABLE);
}

/*************************************************************************************************/

void Usart2_SendChar(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

	USART_SendData(USART2, c);
}

/*************************************************************************************************/

void Usart2_SendString(char * str)
{
	while (*str)
		Usart2_SendChar(*(str++));
}

/*************************************************************************************************/
