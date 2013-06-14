#include "./generic.h"
#include "./createDrive.h"

int main()
{
	create_connect();
	create_full();
	create_forward(100,500);
	create_stop();
	create_wait_time(10);
	create_backward(100,500);
	create_block();
	create_disconnect();
	return 0;
}
