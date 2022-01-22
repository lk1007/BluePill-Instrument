/*
 * songs.c
 *
 *  Created on: Jan 13, 2022
 *      Author: Liam Kain
 */
#include "func.h"

void InstNote(int* a,int* b,int *c){
	uint16_t center = 440; //root note frequency
	uint32_t value = readPin()/500;
	*c = readPin();
	*b = value;
	double ratio = pow(sqrt(2),value/12.0);
	int notePeriod = ratio*(8000000/center);
	TIM2->ARR = (notePeriod);
	*a = notePeriod;
	HAL_Delay(100);
}


