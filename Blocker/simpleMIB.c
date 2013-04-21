// Created on Fri April 19 2013

#include "./generic.h"
#include "./drive.h"
#include "./blockarm.h"


int main()
{
	while(!a_button())
	{}
	block_init();
	forward(50);
	right(87,ks/2);
	forward(110);
	right(87,ks/2);
	forward(40);
	ao();
	return 0;
}
