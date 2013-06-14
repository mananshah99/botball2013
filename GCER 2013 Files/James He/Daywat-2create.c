// Created on Fri March 29 2013

int main()
{
	create_connect();
	create_drive_direct_right(0,100,45);
	create_drive_direct_dist(100,100,200);
	create_block();
	create_stop();
	create_disconnect();
}
