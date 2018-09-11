/*
 * spi2.c
 *
 *  Created on: Dec 19, 2015
 *      Author: tB
 */

#include "spi2.h"

#include <stm32f10x.h>
#include <stm32f10x_spi.h>
#include <pins.h>

/*
	SPI2 I/O:

	NSS @ B12	<-- in use
	SCK	@ B13	<-- in use
	MISO @ B14	<-- not used
	MOSI @ B15	<-- in use
 */

void Spi2_Init(void)
{
	Pin_Init(&(pin_t)PinB12, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinB13, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinB15, GPIO_Mode_AF_PP);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitTypeDef spi;
	spi.SPI_Direction = SPI_Direction_1Line_Rx;
	spi.SPI_Mode = SPI_Mode_Slave;
	spi.SPI_DataSize = SPI_DataSize_16b;
	spi.SPI_CPOL = SPI_CPOL_Low; // Low clock signal at idle
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Hard;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // 24MHz/256=93.750kHz
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;

	SPI_Init(SPI2, &spi);
	SPI_SSOutputCmd(SPI2, ENABLE);
	SPI_Cmd(SPI2, ENABLE);
}

u16 Spi2_Read(void)
{
	Pin_High(&(pin_t)PinB12);
	SPI2->CR1 |= SPI_Mode_Master; // Switch to master mode, this will force NSS pin to go low
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); // Wait for data
	Pin_High(&(pin_t)PinB12);
	u16 data = SPI_I2S_ReceiveData(SPI2); // Read data
	Pin_High(&(pin_t)PinB12);
	SPI2->CR1 &= 0xFEFB; // Switch to slave mode, this will force NSS pin to go high

	return data;
}
