/*
 * Gpt_MemMap.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: inter
 */

#ifndef GPT_MEMMAP_H_
#define GPT_MEMMAP_H_

/********************************Timer0**********************************/

#define TCCR0_REG             *((volatile u8*)0x53)
#define FOC0   7
#define WGM00  6
#define COM01  5
#define COM00  4
#define WGM01  3
#define CS02   2
#define CS01   1
#define CS00   0

#define TCNT0_REG             *((volatile u8*)0x52)

#define OCR0_REG              *((volatile u8*)0x5C)

#define TIMSK_REG             *((volatile u8*)0x59)
#define OCIE0   1
#define TOIE0   0

#define TIFR_REG              *((volatile u8*)0x58)
#define OCF0    1
#define TOV0    0

/********************************Timer1**********************************/
#define TCCR1A_REG           *((volatile u8*)0x4F)
#define COM1A1   7
#define COM1A0   6
#define COM1B1   5
#define COM1B0   4
#define FOC1A    3
#define FOC1B    2
#define WGM11    1
#define WGM10    0

#define TCCR1B_REG           *((volatile u8*)0x4E)
#define ICNC1    7
#define ICES1    6
#define WGM13    4
#define WGM12    3
#define CS12     2
#define CS11     1
#define CS10     0

#define TCNT1H_REG           *((volatile u8*)0x4D)

#define TCNT1L_REG           *((volatile u8*)0x4C)

#define TCNT1_REG            *((volatile u16*)0x4C)

#define OCR1AH_REG           *((volatile u8*)0x4B)

#define OCR1AL_REG           *((volatile u8*)0x4A)

#define OCR1A_REG            *((volatile u16*)0x4A)

#define OCR1BH_REG           *((volatile u8*)0x49)

#define OCR1BL_REG           *((volatile u8*)0x48)

#define OCR1B_REG            *((volatile u16*)0x48)

#define ICR1H_REG            *((volatile u8*)0x47)

#define ICR1L_REG            *((volatile u8*)0x46)

#define ICR1_REG             *((volatile u16*)0x46)

#define TIMSK_REG             *((volatile u8*)0x59)
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2

#define TIFR_REG              *((volatile u8*)0x58)
#define ICF1     5
#define OCF1A    4
#define OCF1B    3
#define TOV1     2

/********************************Timer2**********************************/
#define TCCR2_REG            *((volatile u8*)0x45)
#define FOC2     7
#define WGM20    6
#define COM21    5
#define COM20    4
#define WGM21    3
#define CS22     2
#define CS21     1
#define CS20     0

#define TCNT2_REG            *((volatile u8*)0x44)

#define OCR2_REG             *((volatile u8*)0x43)

#define ASSR_REG             *((volatile u8*)0x42)
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

#define TIMSK_REG            *((volatile u8*)0x59)
#define OCIE2   7
#define TOIE2   6

#define TIFR_REG              *((volatile u8*)0x58)
#define OCF2    7
#define TOV2    6



#define READ_BIT(PORT,BIT)    ((PORT>>BIT)&1)
#define SET_BIT(PORT,BIT)    (PORT=PORT|(1<<BIT))
#define CLEAR_BIT(PORT,BIT)  (PORT&=~(1<<BIT))
#define TOGGLE_BIT(PORT,BIT) (PORT^=(1<<BIT))

#endif /* GPT_MEMMAP_H_ */
