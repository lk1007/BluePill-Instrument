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
	dispNote(value);
	double ratio = pow(sqrt(2),value/12.0);
	int notePeriod = ratio*(8000000/center);
	TIM2->ARR = (notePeriod);
	*a = notePeriod;
	HAL_Delay(100);
}
//implement array of strings
int prevSteps;
void dispNote(int steps)
{
	if(prevSteps != steps && (prevSteps == 1 || prevSteps == 4 || prevSteps == 6))
		clearDisp();
	if(steps == 0)
		writeString("A");
	if(steps == 1)
		writeString("B-flat");
	if(steps == 2)
		writeString("B");
	if(steps == 3)
		writeString("C");
	if(steps == 4)
		writeString("D-flat");
	if(steps == 5)
		writeString("D");
	if(steps == 6)
		writeString("E-flat");
	if(steps == 7)
		writeString("E");
	home();
	prevSteps = steps;
}



