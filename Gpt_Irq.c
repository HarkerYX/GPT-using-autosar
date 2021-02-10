/*
 * Gpt_Irq.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#include "Gpt.h"
#include "Gpt_MemMap.h"

extern f32 NumOfOverflow;

extern u32 Preload;

extern f32 CompareMatchValue;

#define NumofGptNormal    3

#define NumofGptCTC    4

static void (*Gpt_NormalCallBack[NumofGptNormal])(void)={NULL,NULL,NULL};

static void (*Gpt_CTCCallBack[NumofGptCTC])(void)={NULL,NULL,NULL,NULL};

void InterruptEnableNormal0(void)
{
	SET_BIT(TIMSK_REG,TOIE0);
}

void InterruptDisableNormal0(void)
{
	CLEAR_BIT(TIMSK_REG,TOIE0);

}
void InterruptEnableCTC0(void)
{
	SET_BIT(TIMSK_REG,OCIE0);
}

void InterruptDisableCTC0(void)
{
	CLEAR_BIT(TIMSK_REG,OCIE0);
}



void InterruptEnableNormal1(void)
{
	SET_BIT(TIMSK_REG,TOIE1);
}

void InterruptDisableNormal1(void)
{
	CLEAR_BIT(TIMSK_REG,TOIE1);

}
void InterruptEnableCTC1(void)
{
	SET_BIT(TIMSK_REG,OCIE1A);
	SET_BIT(TIMSK_REG,OCIE1B);
}

void InterruptDisableCTC1(void)
{
	CLEAR_BIT(TIMSK_REG,OCIE1A);
	SET_BIT(TIMSK_REG,OCIE1B);
}



void InterruptEnableNormal2(void)
{
	SET_BIT(TIMSK_REG,TOIE2);
}

void InterruptDisableNormal2(void)
{
	CLEAR_BIT(TIMSK_REG,TOIE2);

}
void InterruptEnableCTC2(void)
{
	SET_BIT(TIMSK_REG,OCIE2);
}

void InterruptDisableCTC2(void)
{
	CLEAR_BIT(TIMSK_REG,OCIE2);
}

void Gpt_SetCallBackNormal(void(*CallBack)(void),Gpt_ChannelType Channel)
{
	if(CallBack!=NULL)
	{
		Gpt_NormalCallBack[Channel]=CallBack;
	}
}

void Gpt_SetCallBackCTC(void(*CallBack)(void),Gpt_ChannelType Channel)
{
	if(CallBack!=NULL)
	{
		Gpt_CTCCallBack[Channel]=CallBack;
	}
}

//Normal

void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	static u16 counter=0;
	counter++;
	if(counter==(NumOfOverflow+1))
	{
		TCNT0_REG=Preload;
		counter =0;
		if(Gpt_NormalCallBack!=NULL)
		{
			Gpt_NormalCallBack[Timer0_]();
		}
	}
}

void __vector_9(void)   __attribute__((signal));
void __vector_9(void)
{
	static u16 counter=0;
	counter++;
	if(counter==(NumOfOverflow+1))
	{
		TCNT0_REG=Preload;
		counter =0;
		if(Gpt_NormalCallBack!=NULL)
		{
			Gpt_NormalCallBack[Timer1_]();
		}
	}
}


void __vector_5(void)   __attribute__((signal));
void __vector_5(void)
{
	static u16 counter=0;
	counter++;
	if(counter==(NumOfOverflow+1))
	{
		TCNT0_REG=Preload;
		counter =0;
		if(Gpt_NormalCallBack!=NULL)
		{
			Gpt_NormalCallBack[Timer2_]();
		}
	}
}

//CTC

void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	static u16 counter;
	if(counter==CompareMatchValue)
	{
		counter=0;
		Gpt_CTCCallBack[Timer0_CTC]();
	}
}

void __vector_7(void)  __attribute__((signal));
void __vector_7(void)
{
	static u16 counter;
	if(counter==CompareMatchValue)
	{
		counter=0;
		Gpt_CTCCallBack[Timer1A_CTC]();
	}
}

void __vector_8(void)  __attribute__((signal));
void __vector_8(void)
{
	static u16 counter;
	if(counter==CompareMatchValue)
	{
		counter=0;
		Gpt_CTCCallBack[Timer1B_CTC]();
	}
}

void __vector_4(void)  __attribute__((signal));
void __vector_4(void)
{
	static u16 counter;
	if(counter==CompareMatchValue)
	{
		counter=0;
		Gpt_CTCCallBack[Timer2_CTC]();
	}
}


