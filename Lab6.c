// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Ben Avner & Josh 
// Date Created: 3/6/17 
// Last Modified: 3/6/17 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "dac.h"
#include "SysTick.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// PE=Switch controls (input), PB=DAC output
int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
	

	/*unsigned long Data; // 0 to 15 DAC output
	//PLL_Init(); // like Program 4.6 in the book, 80 MHz
	DAC_Init();
	for(;;) {
		DAC_Out(Data);
		Data = 0x0F&(Data+1); // 0,1,2...,14,15,0,1,2,...
	}*/

	Piano_Init();
	EnableInterrupts();
	Sound_Init(0);
  // other initialization

	Sound_Play(0);
	while(1){}
}


