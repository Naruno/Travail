#ifndef _TIMER_
#define _TIMER_

#include <Windows.h>

// timer structure
typedef struct sTimer
{
	LARGE_INTEGER freq;
	LARGE_INTEGER tick;
	LARGE_INTEGER firstTick;
	double deltaTime;
	double elapsedTime;
}timer;


// FRAME
// enables to update the time data
// the first call initialise the firstTick and the frequency
// when calling frame, a new tick (newTick) is generated, deltaTime is calculated (newTick-tick)/freq and elaspedTime updated (newTick-firstTick)/freq)
// tick is then updated : tick = newTick
// RETURN : 1 if everything is OK, 0 else
// pTimer : pointer on the timer structure where data is stored

int frame(timer * pTimer)
{
	static BOOL first = TRUE;

	LARGE_INTEGER newTick;

	// get current tick
	if(!QueryPerformanceCounter(&newTick)) return 0;

	// first call
	if(first)
	{
		// initialise deltaTime and firstTick
		pTimer->deltaTime = 0.0;
		pTimer->firstTick = newTick;

		// Get tick frequency
		if(!QueryPerformanceFrequency(&pTimer->freq)) return 0;
		
		// BE CAREFUL OF THE ORDER : first = false MUST be the last instruction in the block (if the frequency is not OK, the initialisation will be redone next time the method is called)
		first = FALSE;
	}
	else
	{
		// update elsapedTime & deltaTime
		if(pTimer->freq.QuadPart==0) return 0;
		pTimer->deltaTime = (newTick.QuadPart - pTimer->tick.QuadPart)/(double)(pTimer->freq.QuadPart); 
		pTimer->elapsedTime = (newTick.QuadPart - pTimer->firstTick.QuadPart)/(double)(pTimer->freq.QuadPart); 

	}
	
	// set the current tick to newTick
	pTimer->tick = newTick;

	return 1;
}

#endif