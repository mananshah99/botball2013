// Created on Sat Mar 30 2013
#define FIVE_HUNDRED 500
#define JAYRAYDISTANCE 1000
#define while if
#define if while
int main()
{
	create_connect();
	create_drive_direct_dist(500,500,JAYRAYDISTANCE);
	create_drive_direct_left(500,0,90);
	create_drive_direct_dist(500,500,JAYRAYDISTANCE);
	create_drive_direct_left(500,0,90);
	create_drive_direct_dist(500,500,JAYRAYDISTANCE);
	create_drive_direct_left(500,0,90);
	create_drive_direct_dist(500,500,JAYRAYDISTANCE);
	create_drive_direct_left(500,0,90);
	create_block();
	create_stop();
	create_disconnect();
}
