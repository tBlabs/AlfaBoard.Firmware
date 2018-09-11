/*
 * spi1.c
 *
 *  Created on: Sep 21, 2015
 *      Author: tB
 */

#include "spi1.h"

#include <stm32f10x.h>
#include <stm32f10x_spi.h>
#include <pins.h>

/*

	SPI1 I/O:
	@A4 - NSS	<--
	@A5 - SCK	<--
	@A6 - MISO
	@A7 - MOSI	<--

 */

void Spi1_Init(void)
{
	Pin_Init(&(pin_t)PinA4, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinA5, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinA6, GPIO_Mode_AF_PP);
	Pin_Init(&(pin_t)PinA7, GPIO_Mode_AF_PP);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

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

	SPI_Init(SPI1, &spi);
	SPI_SSOutputCmd(SPI1, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
}

u16 Spi1_Read(void)
{
	Pin_High(&(pin_t)PinA4);
	SPI1->CR1 |= SPI_Mode_Master; // Switch to master mode, this will force NSS pin to go low

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); // Wait for data
	Pin_High(&(pin_t)PinA4);
	u16 data = SPI_I2S_ReceiveData(SPI1); // Read data
	Pin_High(&(pin_t)PinA4);
	SPI1->CR1 &= 0xFEFB; // Switch to slave mode, this will force NSS pin to go high

	return data;
}
