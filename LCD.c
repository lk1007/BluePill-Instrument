/*
 * LCD.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Liam Kain
 */

#include <func.h>
#include <string.h>
#include <stdlib.h>
void writePin(int n, int state){
		if(n == 0)
				HAL_GPIO_WritePin(GPIOB, D0_Pin, state);
		if(n == 1)
				HAL_GPIO_WritePin(GPIOB, D1_Pin, state);
		if(n == 2)
				HAL_GPIO_WritePin(GPIOB, D2_Pin, state);
		if(n == 3)
				HAL_GPIO_WritePin(GPIOB, D3_Pin, state);
		if(n == 4)
				HAL_GPIO_WritePin(GPIOB, D4_Pin, state);
		if(n == 5)
				HAL_GPIO_WritePin(GPIOB, D5_Pin, state);
		if(n == 6)
				HAL_GPIO_WritePin(GPIOB, D6_Pin, state);
		if(n == 7)
				HAL_GPIO_WritePin(GPIOB, D7_Pin, state);
		if(n == 8)
				HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,state);
		if(n == 9)
				HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,state);
		if(n == 10)
				HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,state);
	}
void pinSet(int first, int last, int state){
	for(int i = first; i <=last; i++){
	        writePin(i,state);
	    }
}
void home(){
	pinSet(2,10,0);
	writePin(1,1);
	enable();
}
void enable(){
	writePin(10,1);
	HAL_Delay(100);
	writePin(10,0);
}
void functionSet(int DL,int N,int F){
    pinSet(8,11,0);
    writePin(7,1);
    writePin(4,DL);
    writePin(3,N);
    writePin(2,F);
    enable();
}

void writeByte(uint8_t data){
	for(int i = 0; i <=7; i++){
	        int c = data % 2;
	        data = data >> 1;
	        writePin(i,c);
	    }
	    enable();
}
void showCursor(int disp, int curs, int blink){
    writePin(8,0);
    writePin(9,0);
    pinSet(4,7,0);
    writePin(3,1);
    writePin(2,disp);
    writePin(1,curs);
    writePin(0,blink);
    enable();
}
//if curseDir == 1, cursor moves right, if 0, cursor moves left
//if disMove == 1, display moves according to curseDir, if 0, display doesn't move
void setDir(int curseDir, int disMove){
    writePin(8,0);
    writePin(9,0);
    pinSet(3,7,0);
    writePin(2,1);
    writePin(1,curseDir);
    writePin(0,disMove);
    enable();
}
void shiftCursor(int isRight){
    pinSet(5,9,0);
    writePin(4,1);
    writePin(3,0);
    writePin(2,isRight);
    enable();
}
//if DL is 1, 8-bit mode. 0 is 4-bit mode
//if N is 1, 2-line mode. 0 is 1-line mode
//if F is 1, 5x11 dots, 0 is 5x8 dots mode

void clearDisp(){
    writePin(8,0);
    writePin(9,0);
    pinSet(1,9
    		,0);
    writePin(0,1);
    enable();
}
void setChar(char c){
    writePin(8,1);
    writePin(9,0);
    writeByte(c);
}

void writeString(const char* s){
    int length = strlen(s);
    for(int i = 0; i < length; i++){
       setChar(s[i]);
    }
}
void writeNum(int n){
	char out[100];
	int length;
	int i = 0;
	if(n < 0){
		out[0] = '-';
		i = 1;
	}
	while(n > 0){
		out[i] = (char)(n%10) + '0';
		n /= 10;
		i++;
		length = i;
	}
	char out2[100];
	for(int i = 0;i < length;i++ ){
		out2[i] = out[length - i - 1];
	}
	out2[length] = '\0';
	writeString(out2);
}

#include <string.h>


