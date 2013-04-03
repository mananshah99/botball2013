//defines
#define C_ORANGE 1
#define C_GREEN 0
#define MOT_SORT 0
#define SERV_SORT 2

#include "./generic.h"

void sort_center()
{
	set_servo_position(SERV_SORT,500);
	msleep(250);
}
void sort_left()//orange
{
	servo_set(SERV_SORT,900,.35);
	msleep(100);
	set_servo_position(SERV_SORT,500);
}
void sort_right()//green
{
	servo_set(SERV_SORT,100,.1);
	msleep(100);
	servo_set(SERV_SORT,500,.3);
	
}

//ORANGE: hue 2-40, sat 85-255, val 150-255
//GREEN:  hue 100-150, sat 100-255, val 150-255
int sortsneeded = 5;
void sort()
{
	int spd = 250;
	int switched = 1;
	int count = 0;
	while(!black_button()){
		float st = seconds();
		enable_servo(SERV_SORT);
		sort_center();
		mav(MOT_SORT,spd*switched);
		while(1)//count < sortsneeded)
		{
			update_wait();
			printf("%d,%d\n",cam_area(C_ORANGE) , cam_area(C_GREEN));
			if (cam_area(C_ORANGE) > 3500 || cam_area(C_GREEN) > 3500)
			{
				count++;
				mrp(MOT_SORT,1000,-switched*100);
				/*spd *= 1.04;
				if (spd > 600)
					spd = 600;*/
					
				if (cam_area(C_GREEN) < cam_area(C_ORANGE))
					{sort_left(); }
				else
					{sort_right();}
				
				update_wait();
				update_wait();//wait for new frame before staring again
				
				mav(MOT_SORT,spd*switched);
				st = seconds();
			}
			if (seconds()-st > 6)
			{
				switched *= -1;
				mav(MOT_SORT,spd*switched);
				st = seconds();
			}
		}
		while(count >= sortsneeded){
			off(MOT_SORT);
			disable_servo(SERV_SORT);
			msleep(100);
			if (a_button())
				sortsneeded+=5;
		}
	}
}
int main()
{
	set_pid_gains(MOT_SORT,4,3,5,10,10,10);
	camera_open(LOW_RES);
    sort();
    camera_close();
}
