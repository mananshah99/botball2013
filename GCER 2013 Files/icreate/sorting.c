//defines
#include "./generic.h"
#define C_ORANGE 1
#define C_GREEN 0
#define MOT_SORT 0
#define MOT_BAR 2
#define MOT_WHEEL 1
#define SERV_SORT 2



void sort_center()
{
	set_servo_position(SERV_SORT,500);
	msleep(250);
}
void sort_left()//orange
{
	servo_set(SERV_SORT,1000,.25);
	msleep(250);
	set_servo_position(SERV_SORT,500);
	msleep(100);
}
void sort_right()//green
{
	set_servo_position(SERV_SORT,100);
	msleep(350);
	servo_set(SERV_SORT,500,.3);
}
void dump_green(int max){
	int i;
	for(i=0;i<max;i++){
		servo_set(SERV_SORT,1600,.5);
		msleep(500);
		sort_center();
	}
}
#define SERV_ORANGEDUMP 3
void reset_orange(){
	enable_servo(SERV_ORANGEDUMP);
	set_servo_position(SERV_ORANGEDUMP,540);
	msleep(500);
	disable_servo(SERV_ORANGEDUMP);
}
void dump_orange(){
	enable_servo(SERV_ORANGEDUMP);
	int i;
	for(i=0;i<2;i++){
		set_servo_position(SERV_ORANGEDUMP,1450);
		msleep(1000);
		set_servo_position(SERV_ORANGEDUMP,540);
		msleep(500);
	}
	disable_servo(SERV_ORANGEDUMP);
}

//ORANGE: hue 2-40, sat 85-255, val 150-255
//GREEN:  hue 80-150, sat 50-255, val 70-255
int GO = 1;//global var to stop while lifting
int sortsneeded = 5;
void sort()
{
	set_pid_gains(MOT_SORT,4,3,5,10,10,10);
	set_pid_gains(MOT_BAR,4,3,5,10,10,10);
	set_pid_gains(MOT_WHEEL,4,3,5,10,10,10);
	mav(MOT_BAR,100);
	int spd = 350;
	int switched = 1;
	int count = 0;
	float st = seconds();
	enable_servo(SERV_SORT);
	sort_center();
	mav(MOT_SORT,spd*switched);
	long last = gmpc(MOT_SORT);
	int stuckt = 0;
	while(1)
	{
		if (!GO){
			off(MOT_SORT);
			st = seconds();
			stuckt=0;
			msleep(20);
		} else mav(MOT_SORT,spd*switched);
		update_wait();
		//printf("%d  %ld\n",stuckt,(gmpc(MOT_SORT)-last)*switched);
		if ((gmpc(MOT_SORT)-last)*switched < 10){
			if(stuckt++>5){
				st = seconds()-7;//use later switching code
				stuckt = 0;
			}
		} else if (stuckt > 0) stuckt--;
		last = gmpc(MOT_SORT);
		
		//printf("%d,%d\n",cam_area(C_ORANGE) , cam_area(C_GREEN));
		if (cam_area(C_ORANGE) > 3500 || cam_area(C_GREEN) > 3500)
		{
			count++;
			mrp(MOT_SORT,1000,-switched*100);
			mav(MOT_WHEEL,600);
			if (cam_area(C_ORANGE) > 2500)//if double sort, throw them both to orange
				{sort_left(); }
			else
				{sort_right();}
			
			update_wait();//wait for new frame before staring again
			
			mav(MOT_SORT,spd*switched);
			stuckt = 0;
			st = seconds();
			off(MOT_WHEEL);
		}
		if (seconds()-st > 6.5)
		{
			mrp(MOT_SORT,1000,-switched*100);bmd(MOT_SORT);
			switched *= -1;
			mav(MOT_SORT,spd*switched);
			st = seconds();
			printf("SWITCH to %d\n", spd*switched);
		}
	}
}

#define SERV_CLAW 1
#define SERV_WRIST 0
void claw_close(){
	servo_set(SERV_CLAW,1500,.22);
}
void claw_open(){
	set_servo_position(SERV_CLAW,950);
}
void claw_down(){//claw down and open
	claw_open();
	servo_set(SERV_WRIST,1550,.7);
}
void claw_up(){//close claw, then raise claw and open it
	//void servo_set(int port,int end,float time)
	if (get_servo_position(SERV_CLAW) < 1400)
		servo_set(SERV_CLAW,1500,.22);
	//servo_set(SERV_WRIST,700,.4);
	GO = 0;
	servo_set(SERV_WRIST,500,.45);
	set_servo_position(SERV_CLAW,1200);
	servo_set(SERV_WRIST,350,.1);
	GO = 1;
	msleep(300);
	set_servo_position(SERV_WRIST,550);
	msleep(200);
	
	msleep(2000);
}
void claw_init(){
	set_servo_position(SERV_WRIST,300);
	set_servo_position(SERV_CLAW,805);
	enable_servo(SERV_WRIST);
	enable_servo(SERV_CLAW);
}


int main(){
	printf("\nA to grab\nC to end\n");
	camera_open(LOW_RES);
	thread t_sort = thread_create(sort);
    claw_init();
	
    msleep(300);
    claw_down();
    msleep(400);
    claw_up();
	
	thread_start(t_sort);
    while(!c_button())
    {
        if (a_button()){
            claw_down();
            msleep(500);
            claw_up();
        }
        msleep(100);
    }
	thread_destroy(t_sort);
	ao();
    dump_green(3);
    dump_orange();
}
