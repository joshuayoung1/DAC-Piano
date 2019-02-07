// Sound.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Ben Avner & Josh 
// Date Created: 3/6/17 
// Last Modified: 3/6/17 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

//===============Headers===============
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"
#include "piano.h"
#include "SysTick.h"
//================Global Vars==========

uint32_t wave[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7}; //from the power point
unsigned long wave_index;
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
//================Sound init===========
void Sound_Init(uint32_t period){
	DAC_Init();
	wave_index=0;
	SysTick_Init();
	SysTick_Wait10ms(1);
}
// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none

//================Sound Play, 4fs 4 SWS===========
//We use 4 cases options.
//to calculate K=80MHz/(nsamples*freq)
//             k=80Mhz/(32*1000Hz)=2500		
//						SysTick_Wait(K)
//  -pCM4 -dLaunchPadDLL
//  -pCM4 -dedXLab13
void Sound_Play(uint32_t period){
//
	
	switch(Piano_In())
	{
		case 1:
				SysTick_Wait(2500);
				DAC_Out(wave[wave_index]);
				break;
		case 2:
				SysTick_Wait(1250);
				DAC_Out(wave[wave_index]);				
				break;
		case 4:
				SysTick_Wait(833);	
				DAC_Out(wave[wave_index]);				
				break;
		case 8:
				SysTick_Wait(625);
				DAC_Out(wave[wave_index]);				
				break;
  } 
	SysTick_Wait(2);
}

void SysTick_Handler(){
		GPIO_PORTB_DATA_R |= 0x10;
		if(wave_index <31){ 
			wave_index++;
		}
		else wave_index = 0;
		GPIO_PORTB_DATA_R &= ~0x10;
		Sound_Play(0);
		//SysTick_Wait(4780);
}
