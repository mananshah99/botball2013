// Created on Fri March 29 2013

#include "./createDrive.h"

/*void create_wait_dist(int dist)//dist is in mm
{
	create_write_byte(156);
	create_write_int(dist);
}

void create_drive_direct_dist(int r_speed, int l_speed, int dist)
{
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_dist(dist);*/
	
int main()
{
	create_connect();
	create_drive_direct_dist(200,200,12345);
	create_disconnect();
}
