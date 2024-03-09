/*
 * timeManagger.h
 *}
 *  Created on: Mar 7, 2024
 *      Author: operador
 */

#ifndef TIMEMANAGGER_H_
#define TIMEMANAGGER_H_

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

typedef uint32_t tick_t;
typedef bool bool_t;


typedef struct{

   tick_t startTime;
   tick_t duration;
   bool_t running;

} delay_t;

void TM_delayInit( delay_t * delay, tick_t duration );

bool_t TM_delayRead( delay_t * delay );

void TM_delayWrite( delay_t * delay, tick_t duration );


#endif /* TIMEMANAGGER_H_ */
