// Created on Fri April 12 2013

//wheel specs : d = 5.5
//				r = 2.25

//#define LATCH_MOTOR 2
#define D_TIME 12300 //seconds
 
#define s_MESS_IN_BASE 11

#define s_TOMID 0
#define s_TOTHEIRS 1
#define s_BLOCKMID 3
#define s_BLOCKSTART 4

#define s_END 1337

#include "./generic.h"
#include "./drive.h"
#include "./blockarm.h"

#define MENUSIZE 3
#include "./menu.h"
struct menuitem menu[] = {
	{s_TOTHEIRS,"DE_LEFT -- To theirs"},
	{s_BLOCKMID,"DE_LEFT -- Block mid"},
	{s_BLOCKSTART,"DE_LEFT -- Block start"}};


int main()
{
	//next(s_INTRO);
	block_init();
	Get_Mode();
	int submode = currstate;
	if (currstate==s_TOTHEIRS || currstate==s_BLOCKMID)
		next(s_TOMID);
	light_start(0);
	while(currstate != s_END)
	{
		state(s_TOMID)
		{
			forward(68); //give some leeway for overshoot
			right(87,ks/2);
			forward(55);
			right(33,0);
			forward(10);
			left(45,ks*1.85);
			block_down();
			right(7,0);
			if (submode==s_BLOCKMID)
				next(s_BLOCKMID);
			else
				next(s_MESS_IN_BASE);
		}
		state(s_BLOCKMID){
			//block_down();
			left(6,0);
			next(s_END);
		}
		state(s_MESS_IN_BASE)
		{
			forward(35);
			left(6,0);
			forward(27);
			right(86,ks/2);
			forward(16);
			//right(50,ks);
			//forward(58);
			next(s_END);
		}
		state(s_BLOCKSTART)
		{
			forward(68); //give some leeway for overshoot
			right(89,ks/2);
			forward(20);
			//block_down();
			next(s_END);
		}
	}
	ao();
	return 0;
}
