// Created on Sat June 1 2013

#include "createDrive.h"
#include "generic.h"
//pin 24 low side driver, pin 10
int main()
{
	create_connect();
	beep();
	sleep(.5);
	create_write_byte(138);create_write_byte(7);
	//fd(0);
	//fd(1);
	//wait_for(a_button());
	sleep(10);
	create_crash();
	
	return 0;
}
