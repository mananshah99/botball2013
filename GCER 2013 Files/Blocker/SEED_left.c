// Created on Fri April 12 2013

//wheel specs : d = 5.5
//				r = 2.25

//#define LATCH_MOTOR 2
#define D_TIME 12300 //seconds
 
#define CLAW 3

#define s_GETPOINTSTOSIDE 2
#define s_SQUARE_BACK 0
#define s_COLLECTTHING 1
#define s_WAIT 101

#define s_END 1337

#include "./generic.h"
#include "./drive.h"
#include "./blockarm.h"

#define MENUSIZE 3
#include "./menu.h"
struct menuitem menu[] = {
	{s_WAIT,"WAIT LONG"},
	{s_GETPOINTSTOSIDE,"SEED_LEFT -- Get points"},
	{s_COLLECTTHING,"SEED_LEFT -- Collect thing"},
	{s_SQUARE_BACK,"SEED_LEFT -- Square back"},
};

int main()
{
	//next(s_INTRO);
	block_init();
	Get_Mode();
	int submode = currstate;
	if (currstate==s_WAIT)
		next(s_GETPOINTSTOSIDE);
	light_start(0);
	shut_down_in(120.);
	while(currstate != s_END)
	{
		state(s_SQUARE_BACK)
		{
			square_back();
			next(s_END);
		}
		state(s_GETPOINTSTOSIDE)
		{
			forward(8);
			right(88,0);
			forward(45);
			if (submode==s_WAIT)
				msleep(60000);
			else
				msleep(3000);
			backward(45);
			square_back();
			left(88,0);
			forward(117);
			right(92,0);
			square_back();
			next(s_COLLECTTHING);
		}
		state(s_COLLECTTHING)
		{  
			forward(60);
			left(28,0);
			block_down(); //For the arm
			forward(28);
			mrp(CLAW,900,350); //There's something wrong with this it goes too far James has to do this.
			msleep(900);
			block_up();
			//left(29,0);
			//forward(20);
			//right(29,0);
			//forward(17); 
			//Pick the thing up 
			backward(15);
			//James add a turn right here it has to turn before it drops off the thing 
			mrp(CLAW,100,10);
			msleep(900);
			right(29,ks);
			backward(41);
			square_back(); // square up
			forward(47.8); // go forward
			right(88,ks/2); // right turn
			forward(4); // on the side of the wall
			//left(90,0);
			//backward(10);
			//right(90,0)
			//forward(10);
			mrp(CLAW,1000,-450);
			msleep(1300);
			next(s_END);
		}
	}
}
