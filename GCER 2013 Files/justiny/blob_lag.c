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

int main()
{
	camera_open(LOW_RES);
	while(1)
	{
		msleep(10)
		camera_update();
		if(get_object_count(0)>1)
		{
			
		}
	}
}
