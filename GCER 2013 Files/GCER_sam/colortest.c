// Created on Thu Jun 6 2013

#define COL_GREEN 0



#define fovx 40*DEGTORAD
#define fovy 30*DEGTORAD

#define mdptx 160
#define mdpty 120
/*
case LOW_RES:
	width = 160;
	height = 120;
	break;
case MED_RES:
	width = 320;
	height = 240;
	break;
case HIGH_RES:
	width = 640;
	height = 480;
	break;
*/

#define CAMANGLE 8
#define DIFF 10
#define HEIGHT 9.7

#include "generic.h"

int main() 
{
	camera_open(MED_RES);
	while(1){
		update_wait();
		printf("\n");
		int i;
		for(i=0;i<get_object_count(COL_GREEN);i++){
			if (get_object_area(COL_GREEN,i) > 50)
				printf("%d\n",get_object_area(COL_GREEN,i));
		}
	}
}
