// Created on Fri March 8 2013

#define YOLO 500
#define YOLOLOL 5000
#include <stdio.h>
int main()
{
	create_connect();
	create_drive_direct(0,YOLO);
	msleep(YOLOLOL);
	create_stop();
	create_disconnect();
}
