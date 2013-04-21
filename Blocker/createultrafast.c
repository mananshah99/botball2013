// Created on Fri Apr 5 2013

#include <stdio.h>
#include "createDrive.c"

int main() 
{
	printf("press A to charge forward, or press B to charge backward!");
	create_special_connect();
	while(!(a_button()||b_button()))
		msleep(10);
		
	if(a_button())
	{
		create_forward(750,500);
	}
	if(b_button())
	{
		create_backward(750,500);
	}
	create_stop();
	create_disconnect();
}
