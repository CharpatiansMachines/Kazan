/*
 * timer.h
 *
 *  Created on: Aug 17, 2023
 *      Author: BRG
 */

#ifndef PERIPHERAL_TIMER_H_
#define PERIPHERAL_TIMER_H_
#include "stm32f4xx_hal.h"

using Clock = uint32_t;
using Time = int64_t; /// Time can be negative

static Clock startClock = HAL_GetTick();

inline void Timer_Reset_Time(){
	startClock = HAL_GetTick();
}

inline Clock Timer_Get_Now_Clock(){
	return HAL_GetTick() - startClock;
}

inline Clock Timer_Set_Clock(uint32_t clock) {
	return Timer_Get_Now_Clock() + clock;
}

inline Time Timer_Get_Remain_Time(Clock clock) {
	Time time = clock;
	time = time - Timer_Get_Now_Clock();
	return time;
}
inline Time Timer_Get_Time_Passed_From(Clock clock) {
	Time time = clock;
	time = Timer_Get_Now_Clock() - time;
	return time;
}

inline bool Timer_Has_Passed(Clock clock){
	return Timer_Get_Remain_Time(clock) <= 0;
}

#endif /* PERIPHERAL_TIMER_H_ */
