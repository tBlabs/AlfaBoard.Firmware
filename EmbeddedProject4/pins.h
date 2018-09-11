/*
 * pins.h
 *
 *  Created on: May 11, 2015
 *      Author: tB
 */

#ifndef PINS_H_
#define PINS_H_

/*************************************************************************************************/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "typedefs.h"

/*************************************************************************************************/

#define PinA0 	{ GPIOA, GPIO_Pin_0,  RCC_APB2Periph_GPIOA } // Adc #1
#define PinA1 	{ GPIOA, GPIO_Pin_1,  RCC_APB2Periph_GPIOA } // Adc #2
#define PinA2 	{ GPIOA, GPIO_Pin_2,  RCC_APB2Periph_GPIOA } // Usart2 Tx
#define PinA3 	{ GPIOA, GPIO_Pin_3,  RCC_APB2Periph_GPIOA } // Usart2 Rx
#define PinA4 	{ GPIOA, GPIO_Pin_4,  RCC_APB2Periph_GPIOA } // Buzzer
#define PinA5 	{ GPIOA, GPIO_Pin_5,  RCC_APB2Periph_GPIOA }
#define PinA6 	{ GPIOA, GPIO_Pin_6,  RCC_APB2Periph_GPIOA }
#define PinA7 	{ GPIOA, GPIO_Pin_7,  RCC_APB2Periph_GPIOA }
#define PinA8 	{ GPIOA, GPIO_Pin_8,  RCC_APB2Periph_GPIOA } // Led #1
#define PinA9 	{ GPIOA, GPIO_Pin_9,  RCC_APB2Periph_GPIOA } // Led #2
#define PinA10 	{ GPIOA, GPIO_Pin_10, RCC_APB2Periph_GPIOA } // Led #3
#define PinA11 	{ GPIOA, GPIO_Pin_11, RCC_APB2Periph_GPIOA } // Led #4
#define PinA12 	{ GPIOA, GPIO_Pin_12, RCC_APB2Periph_GPIOA }
#define PinA13 	{ GPIOA, GPIO_Pin_13, RCC_APB2Periph_GPIOA } // Display #4 Data
#define PinA14 	{ GPIOA, GPIO_Pin_14, RCC_APB2Periph_GPIOA } // Display #4 Clock
#define PinA15 	{ GPIOA, GPIO_Pin_15, RCC_APB2Periph_GPIOA } // Display #4 Latch

#define PinB0 	{ GPIOB, GPIO_Pin_0,  RCC_APB2Periph_GPIOB } // Display #3 Data
#define PinB1 	{ GPIOB, GPIO_Pin_1,  RCC_APB2Periph_GPIOB } // Display #3 Clock
#define PinB2 	{ GPIOB, GPIO_Pin_2,  RCC_APB2Periph_GPIOB } // Display #3 Latch
#define PinB3 	{ GPIOB, GPIO_Pin_3,  RCC_APB2Periph_GPIOB }
#define PinB4 	{ GPIOB, GPIO_Pin_4,  RCC_APB2Periph_GPIOB }
#define PinB5 	{ GPIOB, GPIO_Pin_5,  RCC_APB2Periph_GPIOB } // Display #1 Data
#define PinB6 	{ GPIOB, GPIO_Pin_6,  RCC_APB2Periph_GPIOB } // Display #1 Clock
#define PinB7 	{ GPIOB, GPIO_Pin_7,  RCC_APB2Periph_GPIOB } // Display #1 Latch
#define PinB8 	{ GPIOB, GPIO_Pin_8,  RCC_APB2Periph_GPIOB } // Button #1
#define PinB9 	{ GPIOB, GPIO_Pin_9,  RCC_APB2Periph_GPIOB } // Button #2
#define PinB10 	{ GPIOB, GPIO_Pin_10, RCC_APB2Periph_GPIOB } // Button #3
#define PinB11 	{ GPIOB, GPIO_Pin_11, RCC_APB2Periph_GPIOB } // Button #4
#define PinB12 	{ GPIOB, GPIO_Pin_12, RCC_APB2Periph_GPIOB } // TC77 NSS
#define PinB13 	{ GPIOB, GPIO_Pin_13, RCC_APB2Periph_GPIOB } // TC77 SCK
#define PinB14 	{ GPIOB, GPIO_Pin_14, RCC_APB2Periph_GPIOB }
#define PinB15 	{ GPIOB, GPIO_Pin_15, RCC_APB2Periph_GPIOB } // TC77 MOSI

#define PinC0 	{ GPIOC, GPIO_Pin_0,  RCC_APB2Periph_GPIOC }
#define PinC1 	{ GPIOC, GPIO_Pin_1,  RCC_APB2Periph_GPIOC } // Display #2 Data
#define PinC2 	{ GPIOC, GPIO_Pin_2,  RCC_APB2Periph_GPIOC } // Display #2 Clock
#define PinC3 	{ GPIOC, GPIO_Pin_3,  RCC_APB2Periph_GPIOC } // Display #2 Latch
#define PinC4 	{ GPIOC, GPIO_Pin_4,  RCC_APB2Periph_GPIOC } // Pwm #1
#define PinC5 	{ GPIOC, GPIO_Pin_5,  RCC_APB2Periph_GPIOC } // Pwm #2
#define PinC6 	{ GPIOC, GPIO_Pin_6,  RCC_APB2Periph_GPIOC } // Pwm #3
#define PinC7 	{ GPIOC, GPIO_Pin_7,  RCC_APB2Periph_GPIOC } // Pwm #4
#define PinC8 	{ GPIOC, GPIO_Pin_8,  RCC_APB2Periph_GPIOC }
#define PinC9 	{ GPIOC, GPIO_Pin_9,  RCC_APB2Periph_GPIOC }
#define PinC10 	{ GPIOC, GPIO_Pin_10, RCC_APB2Periph_GPIOC }
#define PinC11 	{ GPIOC, GPIO_Pin_11, RCC_APB2Periph_GPIOC }
#define PinC12 	{ GPIOC, GPIO_Pin_12, RCC_APB2Periph_GPIOC }
#define PinC13 	{ GPIOC, GPIO_Pin_13, RCC_APB2Periph_GPIOC }
#define PinC14 	{ GPIOC, GPIO_Pin_14, RCC_APB2Periph_GPIOC }
#define PinC15 	{ GPIOC, GPIO_Pin_15, RCC_APB2Periph_GPIOC }

#define PinD0 	{ GPIOD, GPIO_Pin_0,  RCC_APB2Periph_GPIOD }
#define PinD1 	{ GPIOD, GPIO_Pin_1,  RCC_APB2Periph_GPIOD }
#define PinD2 	{ GPIOD, GPIO_Pin_2,  RCC_APB2Periph_GPIOD }
#define PinD3 	{ GPIOD, GPIO_Pin_3,  RCC_APB2Periph_GPIOD }
#define PinD4 	{ GPIOD, GPIO_Pin_4,  RCC_APB2Periph_GPIOD }
#define PinD5 	{ GPIOD, GPIO_Pin_5,  RCC_APB2Periph_GPIOD }
#define PinD6 	{ GPIOD, GPIO_Pin_6,  RCC_APB2Periph_GPIOD }
#define PinD7 	{ GPIOD, GPIO_Pin_7,  RCC_APB2Periph_GPIOD }
#define PinD8 	{ GPIOD, GPIO_Pin_8,  RCC_APB2Periph_GPIOD }
#define PinD9 	{ GPIOD, GPIO_Pin_9,  RCC_APB2Periph_GPIOD }
#define PinD10 	{ GPIOD, GPIO_Pin_10, RCC_APB2Periph_GPIOD }
#define PinD11 	{ GPIOD, GPIO_Pin_11, RCC_APB2Periph_GPIOD }
#define PinD12 	{ GPIOD, GPIO_Pin_12, RCC_APB2Periph_GPIOD }
#define PinD13 	{ GPIOD, GPIO_Pin_13, RCC_APB2Periph_GPIOD }
#define PinD14 	{ GPIOD, GPIO_Pin_14, RCC_APB2Periph_GPIOD }
#define PinD15 	{ GPIOD, GPIO_Pin_15, RCC_APB2Periph_GPIOD }


/*************************************************************************************************/

typedef struct
{
	GPIO_TypeDef * gpio;
	uint16_t pin;
	uint32_t clock;
}
pin_t;

/*************************************************************************************************/

void Pin_Init(pin_t * pin, GPIOMode_TypeDef mode);
void Pin_Low(pin_t * pin);
void Pin_High(pin_t * pin);
void Pin_Toggle(pin_t * pin);
typedef enum { pinState_HIGH, pinState_LOW } pinState_t;
void Pin_Set(pin_t * pin, pinState_t state);
boolean Pin_IsLow(pin_t * pin);
boolean Pin_IsHigh(pin_t * pin);

/*************************************************************************************************/

#endif /* PINS_H_ */
