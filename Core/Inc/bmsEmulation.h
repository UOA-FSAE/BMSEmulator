/*
 * bmsEmulation.h
 *
 *  Created on: Sep 1, 2023
 *      Author: GGPC
 */

#ifndef INC_BMSEMULATION_H_
#define INC_BMSEMULATION_H_

#include <stm32f0xx_hal_tim.h>

void SendCanFrames(HAL_TIM_ActiveChannel timChannel);

#endif /* INC_BMSEMULATION_H_ */
