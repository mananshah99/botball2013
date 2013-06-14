// Created on Fri March 8 2013

//defines
//#define VARIABLE DEFINITION
#define ORANGE 0

//libraries
//#include <stdio.h>
//#include "./generic.h"
//#include "./drive.h"
//#include "./createDrive.h"

//functions

void motortime(int speed, int m1, int m2, int d)
{
	motor(m1,speed);
	motor(m2,speed);
	msleep(d);
}

int main()
{
	camera_open(LOW_RES);
	while(a_button()==0)
	{
		camera_update();
		int cake=get_object_count(ORANGE); 
		printf("%d\n",cake);
		msleep(200);
		//gets # of objects
		//float x=get_object_center(ORANGE,0).x, y=get_object_center(ORANGE,0).y; //gets coordinates of largest object
		//printf("There is(are) %d object(s)\n",cake); //prints # of objects
		//printf("Largest object at (%3.2f,%3.2f)\n",x,y); //prints coordinates
		//msleep(1000); //wait a little
	}
	
	
	
}

/*int cake;
	float x, y;
	while (!b_button())
	{ 
		camera_update();
		if (get_object_count(ORANGE) > 0)
		{
			cake=get_object_count(ORANGE);
			x = get_object_center(ORANGE,0).x; y = get_object_center(ORANGE,0).y;
			printf("There are %d objects\n",cake);
			printf("Biggest blob at (%3.2f,%3.2f)\n",x,y);
		}
		else
		{
			printf("No color match in Frame\n");
		}
		msleep(500);
	}
return 0; */
