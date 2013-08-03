// Created on Fri March 8 2013

float _start_time;
void start()
{
	_start_time = seconds();
}
float curr_time()
{
    return seconds()-_start_time;
}
void now()
{
    printf("now %f\n",curr_time());
}

void cam_block(){//updates the camera, and waits until success
	while(!camera_update()) msleep(1);
}

int main()
{
	int x = 0;
	camera_open(LOW_RES);
	cam_block();
	cam_block();
	start();
	while(1)
	{	
		cam_block();
		x++;
		printf("\n%f",x/curr_time());
	}
}