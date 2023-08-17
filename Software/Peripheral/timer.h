/*
 * timer.h
 *
 *  Created on: Aug 17, 2023
 *      Author: BRG
 */

#ifndef PERIPHERAL_TIMER_H_
#define PERIPHERAL_TIMER_H_
#include "stm32f4xx_hal.h"
static uint32_t startTime = HAL_GetTick();

inline void Timer_Reset_Start(){
	startTime = HAL_GetTick();
}

inline uint32_t Timer_Get_Now_Time(){
	return HAL_GetTick() - startTime;
}

inline uint32_t Timer_Set_Clock(uint32_t time) {
	return Timer_Get_Now_Time() + time;
}

inline int64_t Timer_Get_Remain_Time(uint32_t clock) {
	int64_t time = clock;
	time = time - Timer_Get_Now_Time();
	return time;
}

inline bool Timer_Has_Passed(uint32_t clock){
	return Timer_Get_Remain_Time(clock) <= 0;
}

#endif /* PERIPHERAL_TIMER_H_ */
