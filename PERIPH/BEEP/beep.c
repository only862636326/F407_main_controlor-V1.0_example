/**
  ******************************************************************************
  * @file    beep.c
  * @author  xjc
  * @version v1.0
  * @date    19-11-20
  * @brief   Beep_On();
						 Beep_Off();
						 需要使用时将Beep_Task = Beep_Task_On;即可
  ******************************************************************************
  */

#include "beep.h"

uint8_t Beep_Flag = Beep_Task_Off;

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
}

void Beep_On(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
}

void Beep_Off(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
}

void Beep_Change(void)
{
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0))
	{
		Beep_Off();
	}
	else
	{
		Beep_On();
	}
}

void Beep_Task(void)
{
	if(Beep_Flag)
	{
		Beep_Flag --;
		Beep_On();
		if(!Beep_Flag)
		{
			Beep_Off();
		}
	}
}
