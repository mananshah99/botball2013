// Created on Fri April 12 2013

//wheel specs : d = 5.5
//				r = 2.25

//#define LATCH_MOTOR 2
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 3
#define D_TIME 12300 //seconds
#define s_INTRO 8
#define s_TOFIRST 9
#define s_MV_OTHER 10
#define s_MESS_IN_BASE 11
#define s_END 1337

#include "./generic.h"
#include "./drive.h"

int robotState;

int main()
{
	while(currstate != s_END)
	{
	state(s_INTRO){next(s_TOFIRST);}
		state(S_TOFIRST)
		{
			forward(24); //exact length = 24.5 give some leeway for overshoot
			left(87,2);
			next(s_MV_OTHER);
		}
		state(s_MV_OTHER)
		{
			forward(148);
			left(87,2);
			forward(33); //approx.
			next(s_MESS_IN_BASE);
		}
		state(s_MESS_IN_BASE)
		{
			mav(0,200)
			msleep(D_TIME); //time driving in mseconds
			next(s_END)
		}
	}
	ao();
	return 0;
}