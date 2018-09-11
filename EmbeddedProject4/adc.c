/*
 * adc.c
 *
 *  Created on: Mar 3, 2015
 *      Author: tB
 */

/*************************************************************************************************/

#include "adc.h"

#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"
#include "pins.h"

/*************************************************************************************************/

#define ADC_DEBUG_ENABLE	1


#if (ADC_DEBUG_ENABLE==0)
	#define AdcDebug(str,...)
#else
	#include "debug.h"
	#include "delay.h"
	#include "timeout.h"
	#define AdcDebug(str,...) Debug(str,##__VA_ARGS__)
#endif

/*************************************************************************************************/
/*
	ADC pins:
	@A0 - ADC_IN0 <-- in use
	@A1 - ADC_IN1 <-- in use
	@A2 - ADC_IN2
	@A3 - ADC_IN3
	@A4 - ADC_IN4
	@A5 - ADC_IN5
	@A6 - ADC_IN6
	@A7 - ADC_IN7
	@B0 - ADC_IN8
	@B1 - ADC_IN9
	@C0 - ADC_IN10
	@C1 - ADC_IN11
	@C2 - ADC_IN12
	@C3 - ADC_IN13
	@C4 - ADC_IN14
	@C5 - ADC_IN15
 */

/*************************************************************************************************/

typedef struct
{
	pin_t pin;
	u8 channel;
	u12 oldValue; // for engine
	percent_t value;
	u32 samplesSum;
	u8 sampleIndex;
}
adc_t;

/*************************************************************************************************/

// ENUM | PIN | ADC CHANNEL
#define AdcChannelsList(channel) \
	channel(adcChannel_1, 		PinA0,	ADC_Channel_0) \
	channel(adcChannel_2, 		PinA1,	ADC_Channel_1) \

/*************************************************************************************************/

#define AdcChannelEnum(e,pin,channel) e,
enum { AdcChannelsList(AdcChannelEnum) };

#define AdcChannel(e,pin,channel) {pin,channel},
adc_t adcChannels[] = { AdcChannelsList(AdcChannel) };

#define adcChannelsCount (sizeof(adcChannels)/sizeof(adc_t))

/*************************************************************************************************/

volatile uint16_t adcValues[adcChannelsCount];


#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define RANGE_CHANGE		41	// Adc is 12-bit: 0-4095

/*************************************************************************************************/

static void DMA_Conf(void)
{
	RCC->AHBENR |= 1; // DMA Clock enable

	DMA_DeInit(DMA1_Channel1);

	DMA_InitTypeDef DMA_InitStruct;
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&adcValues;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = adcChannelsCount;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(DMA1_Channel1, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel1, ENABLE);
}

/*************************************************************************************************/
/*
 * Channel #0 - @A0
 * Channel #1 - @A1
 * Temperature (channel #16) - @internal
 */
void Adc_Init(void)
{
	// Enable ADC clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);

	//IoInit(GPIOA, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_AIN);
	for (u8 i=0; i<adcChannelsCount; i++)
	{
		Pin_Init(&adcChannels[i].pin, GPIO_Mode_AIN);
	}

	DMA_Conf();

	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = adcChannelsCount;

	ADC_Init(ADC1, &ADC_InitStruct);

	u8 rank = 1;

	for (u8 i=0; i<adcChannelsCount; i++)
	{
		ADC_RegularChannelConfig(ADC1, adcChannels[i].channel, rank++, ADC_SampleTime_71Cycles5);
	}

	ADC_DMACmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE);


	ADC_ResetCalibration(ADC1);

	while (ADC_GetResetCalibrationStatus(ADC1)) {};

	ADC_StartCalibration(ADC1);

	while (ADC_GetCalibrationStatus(ADC1)) {};

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/*************************************************************************************************/

static void Adc_Engine(adc_t * adc)
{
	#define MAX_SAMPLES_COUNT	128

	if ((adc->oldValue - RANGE_CHANGE > adcValues[adc->channel]) || (adcValues[adc->channel] > adc->oldValue + RANGE_CHANGE))
	{
		adc->oldValue = (u16)((adcValues[adc->channel]*100) / 4096);

		adc->samplesSum += adc->oldValue;

		if ((adc->sampleIndex++) > MAX_SAMPLES_COUNT)
		{
			adc->value = adc->samplesSum / MAX_SAMPLES_COUNT;
			adc->samplesSum = 0;
			adc->sampleIndex = 0;
		}
	}
}

/*************************************************************************************************/

u16 Adc1_Value(void)
{
	 Adc_Engine(&adcChannels[adcChannel_1]);

	 return adcChannels[adcChannel_1].value;
}

/*************************************************************************************************/

u16 Adc2_Value(void)
{
	 Adc_Engine(&adcChannels[adcChannel_2]);

	 return adcChannels[adcChannel_2].value;
}

/*************************************************************************************************/

u16 Thermo1_Value(void)
{
	// COŒ NIE DZIA£A W TEJ FUNKCJI. KIEDYŒ GRA£O. I TAK LEPSZY BY£Y ZEWNÊTRZNY CZUJNIK...
	return 0;//(1430 - ((float)adcValues[adcChannel_Thermo1])*0.805) / 4.3 + 25;
	//u32 t = adcValues[adcChannel_Thermo1]*1000;
	//return ((((u32)1430000 - (u32)(t*805)) / 4300) + 25000)/1000;
}

/*************************************************************************************************/

#if (ADC_DEBUG_ENABLE==1)

void Adc_Test(void)
{
	static timeout_t printMoment;

	Adc_Init();

	while(1)
	{
		Adc_Engine(&adcChannels[adcChannel_1]);
		Adc_Engine(&adcChannels[adcChannel_2]);

		if (Tick(&printMoment, 250))
		{
			AdcDebug("Adc1: %u (%u)", Adc1_Value(), adcValues[adcChannel_1]);
			AdcDebug("Adc2: %u (%u)", Adc2_Value(), adcValues[adcChannel_2]);
		//	AdcDebug("Thermo1: %u (%u)", Thermo1_Value(), adcValues[adcChannel_Thermo1]);
		}
	}
}

#endif

/*************************************************************************************************/
