/*
 * Gpt.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */


#include "Gpt.h"
#include "Det.h"
#include "Gpt_MemMap.h"
#include "SchM_Gpt.h"

static  u32  prescaler;
static  GptChannelTickFrequency ChannelTickFrequency;
static  GptChannelTickValueMax ChannelTickValueMax;
f32 NumOfOverflow;
f32 CompareMatchValue;
static  u32 OverFlowTick;
u32 Preload;
Gpt_ValueType Total_Time;
Gpt_GenrateError GenrateError;
Gpt_ModeType Mode;
static u32 counter;
static volatile u8 FlagEnableInterrupt;
Gpt_GenratationMode GenratationMode;
Gpt_ChannelType Channel;

Gpt_ValueType  SelectChannel(Gpt_ChannelType Channel)
{
	Gpt_ValueType Value=0;
	if(Channel==Timer0_)
	{
		Value=TCNT0_REG;
	}
	if(Channel==Timer1_)
	{
		Value=TCNT1_REG;

	}
	if(Channel==Timer2_)
	{
		Value=TCNT2_REG;
	}
	return Value;

}

void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
	if(ConfigPtr->Channel==Timer0_)
	{
		switch(ConfigPtr->GenratationMode)
		{
		case Normal:
			CLEAR_BIT(TCCR0_REG,WGM01);
			CLEAR_BIT(TCCR0_REG,WGM00);
			break;
		case CTC:
			SET_BIT(TCCR0_REG,WGM01);
			CLEAR_BIT(TCCR0_REG,WGM00);
			break;
		}
		switch(ConfigPtr->Prescaler)
		{
		case No_clock_source:
			CLEAR_BIT(TCCR0_REG,CS02);
			CLEAR_BIT(TCCR0_REG,CS01);
			CLEAR_BIT(TCCR0_REG,CS00);
			prescaler=0;
			break;
		case No_prescaling:
			CLEAR_BIT(TCCR0_REG,CS02);
			CLEAR_BIT(TCCR0_REG,CS01);
			SET_BIT(TCCR0_REG,CS00);
			prescaler=F_CPU;
			break;
		case Prescaler8:
			CLEAR_BIT(TCCR0_REG,CS02);
			SET_BIT(TCCR0_REG,CS01);
			CLEAR_BIT(TCCR0_REG,CS00);
			prescaler=8;
			break;
		case Prescaler64:
			CLEAR_BIT(TCCR0_REG,CS02);
			SET_BIT(TCCR0_REG,CS01);
			SET_BIT(TCCR0_REG,CS00);
			prescaler=64;
			break;
		case Prescaler256:
			SET_BIT(TCCR0_REG,CS02);
			CLEAR_BIT(TCCR0_REG,CS01);
			CLEAR_BIT(TCCR0_REG,CS00);
			prescaler=256;
			break;
		case Prescaler1024:
			SET_BIT(TCCR0_REG,CS02);
			CLEAR_BIT(TCCR0_REG,CS01);
			SET_BIT(TCCR0_REG,CS00);
			prescaler=1024;
			break;
		case ExternalRisingEdge:
			SET_BIT(TCCR0_REG,CS02);
			SET_BIT(TCCR0_REG,CS01);
			CLEAR_BIT(TCCR0_REG,CS00);
			break;
		case ExternalFallingEdge:
			SET_BIT(TCCR0_REG,CS02);
			SET_BIT(TCCR0_REG,CS01);
			SET_BIT(TCCR0_REG,CS00);
			break;
		}
	}
	else if(ConfigPtr->Channel==Timer1_)
	{
		switch(ConfigPtr->GenratationMode)
		{
		case Normal:
			CLEAR_BIT(TCCR1A_REG,WGM10);
			CLEAR_BIT(TCCR1A_REG,WGM11);
			CLEAR_BIT(TCCR1B_REG,WGM12);
			CLEAR_BIT(TCCR1B_REG,WGM13);
			break;
		case CTC:
			CLEAR_BIT(TCCR1A_REG,WGM10);
			CLEAR_BIT(TCCR1A_REG,WGM11);
			SET_BIT(TCCR1B_REG,WGM12);
			CLEAR_BIT(TCCR1B_REG,WGM13);

			break;
		}

		switch(ConfigPtr->Prescaler)
		{
		case No_clock_source:
			CLEAR_BIT(TCCR1B_REG,CS02);
			CLEAR_BIT(TCCR1B_REG,CS01);
			CLEAR_BIT(TCCR1B_REG,CS00);

			break;
		case No_prescaling:
			CLEAR_BIT(TCCR1B_REG,CS12);
			CLEAR_BIT(TCCR1B_REG,CS11);
			SET_BIT(TCCR1B_REG,CS10);
			prescaler=F_CPU;
			break;
		case Prescaler8:
			CLEAR_BIT(TCCR1B_REG,CS12);
			SET_BIT(TCCR1B_REG,CS11);
			CLEAR_BIT(TCCR1B_REG,CS10);
			prescaler=8;
			break;
		case Prescaler64:
			CLEAR_BIT(TCCR1B_REG,CS12);
			SET_BIT(TCCR1B_REG,CS11);
			SET_BIT(TCCR1B_REG,CS10);
			prescaler=64;
			break;
		case Prescaler256:
			SET_BIT(TCCR1B_REG,CS12);
			CLEAR_BIT(TCCR1B_REG,CS11);
			CLEAR_BIT(TCCR1B_REG,CS10);
			prescaler=256;
			break;
		case Prescaler1024:
			SET_BIT(TCCR1B_REG,CS12);
			CLEAR_BIT(TCCR1B_REG,CS11);
			SET_BIT(TCCR1B_REG,CS10);
			prescaler=1024;
			break;
		case ExternalRisingEdge:
			SET_BIT(TCCR1B_REG,CS12);
			SET_BIT(TCCR1B_REG,CS11);
			CLEAR_BIT(TCCR1B_REG,CS10);
			break;
		case ExternalFallingEdge:
			SET_BIT(TCCR1B_REG,CS12);
			SET_BIT(TCCR1B_REG,CS11);
			SET_BIT(TCCR1B_REG,CS10);
			break;
		}
	}

	else if(ConfigPtr->Channel==Timer2_)
	{
		switch(ConfigPtr->GenratationMode)
		{
		case Normal:
			CLEAR_BIT(TCCR2_REG,WGM21);
			CLEAR_BIT(TCCR2_REG,WGM20);

			break;
		case CTC:
			SET_BIT(TCCR2_REG,WGM21);
			CLEAR_BIT(TCCR2_REG,WGM20);

			break;
		}
		switch(ConfigPtr->Prescaler)
		{
		case No_clock_source:
			CLEAR_BIT(TCCR2_REG,CS22);
			CLEAR_BIT(TCCR2_REG,CS21);
			CLEAR_BIT(TCCR2_REG,CS20);

			break;
		case No_prescaling:
			CLEAR_BIT(TCCR2_REG,CS22);
			CLEAR_BIT(TCCR2_REG,CS21);
			SET_BIT(TCCR2_REG,CS20);
			prescaler=F_CPU;
			break;
		case Prescaler8:
			CLEAR_BIT(TCCR2_REG,CS22);
			SET_BIT(TCCR2_REG,CS21);
			CLEAR_BIT(TCCR2_REG,CS20);
			prescaler=8;
			break;
		case Prescaler32:
			CLEAR_BIT(TCCR2_REG,CS22);
			SET_BIT(TCCR2_REG,CS21);
			SET_BIT(TCCR2_REG,CS10);
			prescaler=32;
			break;
		case Prescaler64:
			SET_BIT(TCCR2_REG,CS22);
			CLEAR_BIT(TCCR2_REG,CS21);
			CLEAR_BIT(TCCR2_REG,CS20);
			prescaler=64;
			break;
		case Prescaler128:
			SET_BIT(TCCR2_REG,CS22);
			CLEAR_BIT(TCCR2_REG,CS21);
			SET_BIT(TCCR2_REG,CS20);
			prescaler=128;
			break;
		case Prescaler256:
			SET_BIT(TCCR2_REG,CS22);
			SET_BIT(TCCR2_REG,CS21);
			CLEAR_BIT(TCCR2_REG,CS20);
			prescaler=256;
			break;
		case Prescaler1024:
			SET_BIT(TCCR2_REG,CS22);
			SET_BIT(TCCR2_REG,CS21);
			SET_BIT(TCCR2_REG,CS20);
			prescaler=1024;
			break;
		}
	}

#if (GptDevErrorDetect==E_OK)
	if(GenrateError==Gpt_AlreadyInitillized)
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_Init_API,GPT_E_ALREADY_INITIALIZED);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_Init_API,GPT_E_UNINIT);
	}
	if(ConfigPtr==NULL)
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_Init_API,GPT_E_PARAM_POINTER);
	}
#endif
	Mode=GPT_MODE_NORMAL;
	Preload=0;
	Channel=ConfigPtr->Channel;
}

void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value)
{
	Total_Time=Value;
	ChannelTickFrequency=F_CPU/prescaler;
	ChannelTickValueMax=1/ChannelTickFrequency;

	switch(Channel)
	{
	case Timer0_:
		OverFlowTick=256;
		NumOfOverflow=Value/OverFlowTick;
		Preload=OverFlowTick-(OverFlowTick*(f32)(NumOfOverflow-(u32)NumOfOverflow));
		TCNT0_REG=Preload;
	break;
	case Timer1_:
		OverFlowTick=65536;
		NumOfOverflow=Value/OverFlowTick;
		Preload=OverFlowTick-(OverFlowTick*(f32)(NumOfOverflow-(u32)NumOfOverflow));
		TCNT1L_REG=Preload;
		TCNT1H_REG=Preload>>8;
	break;
	case Timer2_:
		OverFlowTick=256;
		NumOfOverflow=Value/OverFlowTick;
		Preload=OverFlowTick-(OverFlowTick*(f32)(NumOfOverflow-(u32)NumOfOverflow));
		TCNT2_REG=Preload;
	break;

	}
	if(Mode==GPT_CH_MODE_CONTINUOUS)
	{
		counter++;
	}
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StartTimer,GPT_E_PARAM_CHANNEL);
	}
	if(Value>OverFlowTick)
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StartTimer,GPT_E_PARAM_VALUE);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StartTimer,GPT_E_UNINIT);
	}
	if(GenrateError==Gpt_Busy )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StartTimer,GPT_E_BUSY);
	}
#endif

}

#if(GptDeInitApi==E_OK)
void Gpt_DeInit(void)
{

}
#endif


#if(GptTimeElapsedApi==E_OK)
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
	Gpt_ValueType Value;
	Value=SelectChannel(Channel);
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeElapsed_API,GPT_E_PARAM_CHANNEL);
	}
	if(Value>OverFlowTick)
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeElapsed_API,GPT_E_PARAM_VALUE);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeElapsed_API,GPT_E_UNINIT);
	}
	if(GenrateError==Gpt_Busy )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeElapsed_API,GPT_E_BUSY);
	}
#endif
	return Value;
}
#endif

#if (GptTimeRemainingApi==E_OK)
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
	Gpt_ValueType Value;
	Value=Total_Time-Gpt_GetTimeElapsed(Channel);
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeRemaining_API,GPT_E_PARAM_CHANNEL);
	}
	if(Value>OverFlowTick)
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeRemaining_API,GPT_E_PARAM_VALUE);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeRemaining_API,GPT_E_UNINIT);

	}
	if(GenrateError==Gpt_Busy )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_GetTimeRemaining_API,GPT_E_BUSY);
	}
#endif
	return Value;
}
#endif

void Gpt_StopTimer(Gpt_ChannelType Channel)
{
	Gpt_ValueType Value;
	if(Mode==GPT_CH_MODE_ONESHOT)
	{

		Value=SelectChannel(Channel);
		prescaler=No_clock_source;
	}
	else
	{
		Value=SelectChannel(Channel);
		Value=Total_Time*counter;
	}
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StopTimer_API,GPT_E_PARAM_CHANNEL);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_StopTimer_API,GPT_E_UNINIT);
	}
#endif
}

#if (GptEnableDisableNotificationApi==E_OK)
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
	Mode=GPT_MODE_NORMAL;
	if(GenratationMode==Normal)
	{
		if(Channel==Timer0_)
		{
			InterruptEnableNormal0();
			if(!READ_BIT(TIFR_REG,OCF0))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}

		if(Channel==Timer1_)
		{
			InterruptEnableNormal1();
			if(!READ_BIT(TIFR_REG,OCF1A)&&!READ_BIT(TIFR_REG,OCF1B))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}
		if(Channel==Timer2_)
		{
			InterruptEnableNormal2();
			if(!READ_BIT(TIFR_REG,OCF2))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}
	}

	else if(GenratationMode==CTC)
	{
		if(Channel==Timer0_)
		{
			InterruptEnableCTC0();
			if(!READ_BIT(TIFR_REG,TOV0))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}

		if(Channel==Timer1_)
		{
			InterruptEnableCTC1();
			if(!READ_BIT(TIFR_REG,TOV1))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}
		if(Channel==Timer2_)
		{
			InterruptEnableCTC2();
			if(!READ_BIT(TIFR_REG,TOV2))
			{
				FlagEnableInterrupt=1;
			}
			else
			{
				FlagEnableInterrupt=0;
			}
		}
	}
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_EnableNotification_API,GPT_E_PARAM_CHANNEL);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_EnableNotification_API,GPT_E_UNINIT);
	}
#endif
}
#endif

#if (GptEnableDisableNotificationApi==E_OK)
void  Gpt_DisableNotification(Gpt_ChannelType Channel)
{
	Mode=GPT_MODE_NORMAL;
	if(GenratationMode==Normal)
	{
		if(Channel==Timer0_)
		{
			InterruptEnableNormal0();
			if(!READ_BIT(TIFR_REG,OCF0))
			{
				FlagEnableInterrupt=0;
			}
		}

		if(Channel==Timer1_)
		{
			InterruptEnableNormal1();
			if(!READ_BIT(TIFR_REG,OCF1A)&&!READ_BIT(TIFR_REG,OCF1B))
			{
				FlagEnableInterrupt=0;
			}

		}
		if(Channel==Timer2_)
		{
			InterruptEnableNormal2();
			if(!READ_BIT(TIFR_REG,OCF2))
			{
				FlagEnableInterrupt=1;
			}
		}
	}

	else if(GenratationMode==CTC)
	{
		if(Channel==Timer0_)
		{
			InterruptEnableCTC0();
			if(!READ_BIT(TIFR_REG,TOV0))
			{
				FlagEnableInterrupt=0;
			}
		}

		if(Channel==Timer1_)
		{
			InterruptEnableCTC1();
			if(!READ_BIT(TIFR_REG,TOV1))
			{
				FlagEnableInterrupt=0;
			}
		}
		if(Channel==Timer2_)
		{
			InterruptEnableCTC2();
			if(!READ_BIT(TIFR_REG,TOV2))
			{
				FlagEnableInterrupt=0;
			}
		}
	}
#if (GptDevErrorDetect==E_OK)
	if(Channel>Timer2_ )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_DisableNotification_API,GPT_E_PARAM_CHANNEL);
	}
	if(GenrateError==Gpt_Uninitialized )
	{
		Det_ReportError(GPT_Driver,Instance,Gpt_DisableNotification_API,GPT_E_UNINIT);
	}
#endif
}
#endif

void Gpt_EnableWakeup(Gpt_ChannelType Channel)
{

}
#if(GptReportWakeupSource==E_OK)
void Gpt_SetMode(Gpt_ModeType Mode)
{
	if(Mode==GPT_MODE_NORMAL)
	{
		Gpt_EnableNotification(Channel);
	}
	else if(Mode==GPT_MODE_SLEEP)
	{
	     Gpt_EnableWakeup(Channel);
	}
}
#endif
