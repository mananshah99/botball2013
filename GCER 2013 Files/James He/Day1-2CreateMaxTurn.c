// Created on Fri March 8 2013

int main()
{
	create_connect();
	create_drive_direct(500,0);
	sleep(5);
	create_drive_direct(0,500);
	sleep(5);
	create_stop();
	create_disconnect();
}
