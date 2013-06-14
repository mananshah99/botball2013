// Created on Fri April 12 2013

//wheel specs : d = 5.5
//				r = 2.25

//#define LATCH_MOTOR 2
#define D_TIME 30000 //seconds
 
#define s_MESS_IN_BASE 11
#define CLAW 3

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

void freezeall(int m1, int m2)
	{
		freeze(m1);
		freeze(m2);
	}

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
			right(100,ks/2);
			block_down();
			forward(67);
			//right(24,0);
			//forward(8);
			//left(39,ks*1.81);
			//right(17,0);
			right(5,0);
			if (submode==s_BLOCKMID)
				next(s_BLOCKMID);
			else
				next(s_MESS_IN_BASE);
		}
		state(s_BLOCKMID){
			//block_down();
			left(6,0);
			freezeall(0,1);
			msleep(D_TIME);
			next(s_END);
		}
		state(s_MESS_IN_BASE)
		{
			
			left(20,0);
			right(20,0);
			forward(30);
			
			//left(2,0);
			right(6,0);
			forward(6);
			//right(5,0);
			//forward(3);
			//right(5,0);
			forward(51);
			right(88,ks/2);
			forward(16);
			freezeall(0,1);
			msleep(D_TIME);
			//right(50,ks);
			//forward(58);
			next(s_END);
		}
		state(s_BLOCKSTART)
		{
			forward(68); //give some leeway for overshoot
			right(89,ks/2);
			forward(20);
			freezeall(0,1);
			msleep(D_TIME);
			//block_down();
			next(s_END);
		}
	}
	ao();
	return 0;
}
