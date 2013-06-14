/* create (158) input number
create drive forward
create (158) -input number */
#include "createDrive.h"
int main()
{
	create_connect();
	/*create_write_byte(147); //sends output
	create_write_byte(4);
	create_write_byte(158); //waits for button
	create_write_byte(18);
	create_write_byte(145); //movement
	create_write_byte(0);
	create_write_byte(50);
	create_write_byte(0);
	create_write_byte(50);
	create_write_byte(158); //waits for button to stop
	create_write_byte(238);
	create_disconnect();*/
	output_sen_0();
	create_wait_event(18);
	create_drive_direct(50,50);
	create_wait_event(238);
	create_disconnect();
}
