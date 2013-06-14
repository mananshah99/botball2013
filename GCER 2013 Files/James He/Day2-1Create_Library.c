// Created on Sat March 9 2013
#include "./createDrive.h"
int main()
#define RIGHT 90
{
	create_connect();
	create_forward(200,200);
	create_backward(350,250);
	create_forward(200,200);
	create_right(RIGHT,1,100);
	//create_right(RIGHT,1,100);
	//create_left(RIGHT,1,100);
	/*while(!c_button())
	{
		while(a_button())
		{
			create_forward(10,200);
		}
		while(b_button())
		{
			create_backward(10,250);
		}
	}*/
	create_stop();
	create_disconnect();
}

