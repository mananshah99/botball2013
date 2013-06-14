#include "./createDrive.h" 
void forward_bump()
{
	while(create_wait_event(LEFT_BUMP) == 0)
		{
			create_drive_direct(300,300);
		}
}
int main()
{
	create_connect();
	forward_bump();
	create_drive_direct_dist(-300,-300,97);
	create_drive_direct_right(200,300,90);
	forward_bump();
	create_drive_direct_dist(-300,-300,97);
	create_drive_direct_right(200,300,90);
	create_disconnect();
}
