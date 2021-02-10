/*
 * Gpt.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef GPT_H_
#define GPT_H_

#include "EcuM_Cbk.h"
#include "Gpt_Cfg.h"
#include "Std_Types.h"

typedef enum
{
	Timer0_=0,
	Timer1_,
	Timer2_

}Gpt_ChannelType;

typedef enum
{
	Timer0_CTC=0,
	Timer1A_CTC,
	Timer1B_CTC,
	Timer2_CTC

}Gpt_CTCChannelType;

typedef u32 Gpt_ValueType;

typedef enum
{
	GPT_MODE_NORMAL=0,
	GPT_MODE_SLEEP=1
}Gpt_ModeType;

typedef enum
{
	GPT_PREDEF_TIMER_1US_16BIT=0x00,
	GPT_PREDEF_TIMER_1US_24BIT=0x01,
	GPT_PREDEF_TIMER_1US_32BIT=0x02,
	GPT_PREDEF_TIMER_100US_32BIT=0x03

}Gpt_PredefTimerType;

typedef enum
{
	Normal_No_Compare_Match=0,
	Toggle_Compare_Match,
	Clear_Compare_Match,
	Set_Compare_Match
}Gpt_NonPwmModeType;
typedef enum
{
	No_clock_source,
	No_prescaling,
	Prescaler8,
	Prescaler32,
	Prescaler64,
	Prescaler128,
	Prescaler256,
	Prescaler1024,
	ExternalRisingEdge,
	ExternalFallingEdge

}Gpt_PrescalerValue;

typedef enum
{
	GPT_CH_MODE_CONTINUOUS=0,
	GPT_CH_MODE_ONESHOT,
}Gpt_ChannelMode;

typedef u32 GptChannelTickFrequency;

typedef u32 GptChannelTickValueMax;


typedef enum
{
	Normal=0,
	CTC,


}Gpt_GenratationMode;

typedef struct
{
	Gpt_ChannelType Channel;
	Gpt_GenratationMode GenratationMode;
	Gpt_PrescalerValue Prescaler;


}Gpt_ConfigType;

typedef enum
{
	Gpt_Uninitialized =0,
	Gpt_AlreadyInitillized,
	Gpt_Busy,
	Gpt_Expird
}Gpt_GenrateError;

void InterruptEnableNormal0(void);

void InterruptDisableNormal0(void);

void InterruptEnableCTC0(void);

void InterruptDisableCTC0(void);

void InterruptEnableNormal1(void);

void InterruptDisableNormal1(void);

void InterruptEnableCTC1(void);

void InterruptDisableCTC1(void);

void InterruptEnableNormal2(void);

void InterruptDisableNormal2(void);

void InterruptEnableCTC2(void);

void InterruptDisableCTC2(void);

void Gpt_SetCallBackNormal(void(*CallBack)(void),Gpt_ChannelType Channel);

void Gpt_SetCallBackCTC(void(*CallBack)(void),Gpt_ChannelType Channel);

void Gpt_Init(const Gpt_ConfigType* ConfigPtr);

void Gpt_DeInit(void);

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value);

void Gpt_StopTimer(Gpt_ChannelType Channel);

void Gpt_EnableNotification(Gpt_ChannelType Channel);

void  Gpt_DisableNotification(Gpt_ChannelType Channel);

void Gpt_EnableWakeup(Gpt_ChannelType Channel);

//void Gpt_SetMode(Gpt_ModeType Mode);

#define Gpt_Init_API      0x01

#define Gpt_DeInit_API   0x02

#define Gpt_GetTimeElapsed_API    0x03

#define Gpt_GetTimeRemaining_API    0x04

#define Gpt_StartTimer_API    0x05

#define Gpt_StopTimer_API    0x06

#define Gpt_EnableNotification_API    0x07

#define Gpt_DisableNotification_API    0x08

#define Gpt_SetMode_API    0x09

#define Gpt_DisableWakeup_API    0x0a

#define Gpt_EnableWakeup_API    0x0b

#define Gpt_CheckWakeup_API    0x0c

#define Gpt_GetPredefTimerValue_API    0x0d

#define  GPT_E_UNINIT  0x0a

#define GPT_E_ALREADY_INITIALIZED  0x0D

#define GPT_E_INIT_FAILED 0x0E

#define GPT_E_PARAM_CHANNEL 0x14

#define GPT_E_PARAM_VALUE 0x15

#define GPT_E_PARAM_POINTER 0x16

#define GPT_E_PARAM_PREDEF_TIMER 0x17

#define GPT_E_PARAM_MODE 0x1F

#define GPT_E_BUSY 0x2F

#define GPT_Driver                        100

#define Instance                          0

#endif /* GPT_H_ */
