//defines
#define C_ORANGE 1
#define C_GREEN 0
#define MOT_SORT 0
#define SERV_SORT 2

#include "./generic.h"

void sort_center()
{
	set_servo_position(SERV_SORT,500);
	msleep(250);//don't need to typecast to Long, c handles that automatically
}
void sort_left()//orange
{
	servo_set(SERV_SORT,900,.35);//defined in generic.h library as servo, position, (float)time
	msleep(100);
	set_servo_position(SERV_SORT,500);//whack back fast to knock the orange off the platform
}
void sort_right()//green
{
	servo_set(SERV_SORT,100,.1);
	msleep(100);
	servo_set(SERV_SORT,500,.3);//come back slowly since we don't want to knock the greens off
	
}

//ORANGE: hue 2-40, sat 85-255, val 150-255
//GREEN:  hue 100-150, sat 100-255, val 150-255
void sort()
{
	int spd = 250;//we may want to add some speed adjustment code later on
	int switched = 1;
	int count = 0;
	float st = seconds();
	enable_servo(SERV_SORT);
	sort_center();
	mav(MOT_SORT,spd*switched);
	while(!side_button())//sort until the process for sorting is terminated or the panic button is pressed
	{
		update_wait();//updates the camera frame, blocking
		printf("%d,%d\n",cam_area(C_ORANGE) , cam_area(C_GREEN));
		if (cam_area(C_ORANGE) > 3500 || cam_area(C_GREEN) > 3500)
		{//cam_area is defined in generic to safely find the largest blob's size without printing errors
			count++;
			mrp(MOT_SORT,1000,-switched*100);
			
			if (cam_area(C_GREEN) < cam_area(C_ORANGE))
				{sort_left(); }
			else
				{sort_right();}
			
			update_wait();
			update_wait();//wait for new frame before staring again
			
			mav(MOT_SORT,spd*switched);
			st = seconds();
		}
		if (seconds()-st > 6)//if no tribbles have appeared for too long, assume a jam and reverse directions
		{
			switched *= -1;
			mav(MOT_SORT,spd*switched);
			st = seconds();
		}
	}
}
int main()
{
	set_pid_gains(MOT_SORT,4,3,5,10,10,10);//set pid settings to optimize for our low-speed individualizer motor
	camera_open(LOW_RES);
    sort();
    camera_close();
}
