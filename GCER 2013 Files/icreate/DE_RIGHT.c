// Created on Fri April 5 2013
#define MAIN
#include "./generic.h"
#include "./createDrive.h"
#include "./sortingDE.h"
#include "./singing.h"
//sorting now also includes claw


#define s_START      0
#define s_TOFOURTH   1
#define s_TOFIFTH    7
#define s_TOSIXTH    8 
#define s_TOSEVEN    9
#define s_TOEIGHT    10
#define s_RETURN     11
#define s_CUTSHORT   12
#define s_FINAL      13


#define s_TESTING   742

#define s_END 666


//currstate defined in generic



int main()
{
	printf("Connecting...\n");
	create_connect();
	create_full();
	camera_open(LOW_RES);
	printf("Complete!\n");
	
	claw_init();
	sort_center();
	reset_orange();
	
	thread t_sort = thread_create(sort);
	//next(s_SEEDSTART);
	
	printf("\nA fast, B wait, C sings\n");
	int wait = getabcbutton();
	
	printf("\nA far, B close\n");
	int close = getabbutton();
	
	
	start();
	next(s_START);
	while(currstate != s_END){
		state(s_START){
			light_start(0);
			next(s_TOFOURTH);
		}
		state(s_TOFOURTH){
			shut_down_in(120.);
			start();
			thread_start(t_sort);
			set_servo_position(SERV_WRIST,700);
			msleep(200);
			claw_open();msleep(100);
			create_right(85,100,350);
			create_forward(140,300);
			create_left(50,0,300);
			create_forward(90,300);
			create_right(10,600,150);
			create_right(45,170,150);
			create_forward(75,150);
			create_right(-90,100,-300);
			create_stop();
			
			set_servo_position(SERV_WRIST,420);
			set_servo_position(SERV_CLAW,1500);
			
			create_block();
			
			claw_down();
			
			create_left(15,350,250);
			create_forward(120,200);
			create_block();
			claw_up();
			next(s_TOSIXTH);
		}
		state(s_TOSIXTH){
			create_backward(105,200);
			create_block();
			claw_down();
			create_right(35,0,200);
			create_forward(135,200);
			create_block();
			claw_up();
			if (close){
				next(s_CUTSHORT);
			}else{
				next(s_TOSEVEN);
			}
		}
		state(s_TOSEVEN){
			servo_set(SERV_WRIST,1400,.6);//claw closed, semidown
			claw_close();
			create_forward(60,200);
			create_left(24,700,200);
			create_left(50,0,200);//knock the botguy/cube out of the way
			create_right(42,0,200);//then go back on track
			create_send();
			create_forward(135,200);
			create_stop();
			create_send();
			
			create_recieve();
			claw_open();
			create_recieve();
			set_servo_position(SERV_WRIST,1550);//all the way down
			create_forward(95,200);
			create_block();
			claw_up();
			next(s_TOEIGHT);
		}
		state(s_TOEIGHT){
			create_left(40,0,200);
			create_block();
			claw_down();
			create_right(10,225,200);
			create_forward(60,200);
			create_block();
			claw_close();
			create_backward(20,200);
			create_left(-40,200,-200);
			create_block();
			claw_up();
			next(s_RETURN);
		}
		state(s_RETURN){
			create_right(-5,250,-300);
			create_backward(500,300);
			create_left(-96,250,-300);
			create_backward(240,300);
			create_left(-90,100,-300);
			create_left(30,0,300);
			create_block();
			next(s_FINAL);
		}
		state(s_CUTSHORT){
			create_right(-10,250,-300);
			create_backward(100,300);
			create_left(-96,250,-300);
			create_backward(240,300);
			create_left(-90,100,-300);
			create_backward(50,300);
			create_left(30,0,300);
			create_block();
			next(s_FINAL);
		}
		state(s_FINAL){
			switch(wait){
				case 0:break;
				case 2:
					undersea();
					play();
				case 1:
					msleep(45000);
					break;
			}
			
			GO = 0; msleep(200);//stop sorting for now
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green(3);
			
			//wait_till(100);
			
			create_right(30,0,300);
			create_right(89,100,300);
			create_forward(375,300);
			create_left(89,0,300);
			create_backward(50,300);
			create_block();
			
			dump_orange();
			
			printf("COMPLETE");
			next(s_END);
		}
	}
	thread_destroy(t_sort);
	ao();
	create_disconnect();
	
	return 0;
}
