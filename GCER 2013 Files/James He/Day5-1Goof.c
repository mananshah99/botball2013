// Created on Thu April 4 2013
#include "./drive.h"
int main()
{
	forward(100);
	left(90,0);
	forward(1000);
	while (1==1)
	{
		int x=0;
		while (x < 3)
		{
			left(90,10);
			right(90,10);
			x++;
		}
		right(270,10);
		forward(10);
		left(90,0)
	}
}
