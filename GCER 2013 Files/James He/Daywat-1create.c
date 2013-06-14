// Created on Fri March 29 2013
#define JAYRAYDISTANCE DISTANCE
#define DISTANCE 1000
int main()
{
	create_connect();
	create_drive_direct_dist(100,100,JAYRAYDISTANCE);
	create_drive_direct_left(100,0,90);
	create_drive_direct_dist(100,100,JAYRAYDISTANCE);
	create_drive_direct_left(100,0,90);
	create_drive_direct_dist(100,100,JAYRAYDISTANCE);
	create_drive_direct_left(100,0,90);
	create_drive_direct_dist(100,100,JAYRAYDISTANCE);
	create_drive_direct_left(100,0,90);
	create_block();
	create_stop();
	create_disconnect();
}
