// Created on Fri April 19 2013 DE_left flipped around :)
//by Manan

/* 

**WHEEL SPECS** 
// d = 5.5
// r = 2.25

*/

#define D_TIME 12300 //seconds

#define s_MESS_IN_BASE 11

#define s_TOMID 0
#define s_TOTHEIRS 1
#define s_BLOCKMID 2
#define s_BLOCKSTART 3
#define s_MIDBASE 4
#define s_ENDBASE 5


#define s_END 1337

#include "./generic.h"
#include "./drive.h"
#include "./blockarmspecforrightnew.h"

#define MENUSIZE 5
#include "./menu.h"
struct menuitem menu[] = {
	{s_TOTHEIRS,"DE_RIGHT -- beginning of base!"},
	{s_MIDBASE, "DE_RIGHT -- middle of base!"},
	{s_ENDBASE, "DE_RIGHT -- end of base!"},
	{s_BLOCKMID,"DE_RIGHT -- middle of the side path"},
	{s_BLOCKSTART,"DE_RIGHT -- forward, turn then stop"}
	};

int main()
{
	//next(s_INTRO);
	printf("this goes right");
	block_down();
	Get_Mode();
	int submode = currstate;
	if (currstate==s_TOTHEIRS || currstate==s_MIDBASE || currstate==s_ENDBASE)
		next(s_TOMID);
	light_start(0);

	while(currstate != s_END)
	{
		state(s_MESS_IN_BASE)
		{
			if (submode==s_TOTHEIRS)
			{
				next(s_END);
			}
			else if (submode == s_MIDBASE)
			{	
				forward(42); // figure this out for the correct value
				//left(90,ks);
				next(s_END);
			}
			else if (submode == s_ENDBASE)
			{
				forward(90); // figure this out for the correct value
				next(s_END);
			}
			else
			{
				next(s_END);
			}
		}
		
		state(s_TOMID)
		{ 
			forward(38);   
			left(40,ks/2);
			forward(15);
			left(43,0);	
			forward(147); 
			left(80,ks);
			//forward(20);
			//left(90,ks);
			if (submode==s_BLOCKMID)
				next(s_END);
			else
				next(s_MESS_IN_BASE);
		}
		
		state(s_BLOCKMID)
		{
			forward(38);   
			left(40,ks/2);
			forward(15);
			left(48,0);	
			forward(20);
			//block_down();
		}
		
		state(s_BLOCKSTART)
		{
			forward(47);
			left(80,0);
 			next(s_END);
		}
	}
	ao();
	return 0;
}
