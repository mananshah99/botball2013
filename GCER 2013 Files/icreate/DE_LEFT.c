// Created on Fri April 5 2013
#define MAIN
#include "./generic.h"
#include "./createDrive.h"
#include "./sortingDE.h"
#include "./singing.h"
//sorting now also includes claw


#define s_START  0
#define s_TOFIRST    1
#define s_TOSECOND   2 
#define s_TOTHIRD    3
#define s_TOFOURTH   4
#define s_RETURN     5
#define s_DUMPORANGE 6   
#define s_CUTSHORT   7
#define s_TESTING   742

#define s_END 666

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
	
	printf("\nA fast, B wait, C sings\n");
	int wait = getabcbutton();
	
	printf("\nA far, B close\n");
	int close = getabbutton();
	
	next(s_START);
	start();
	if (currstate != s_START){
		thread_start(t_sort);
	}
	while(currstate != s_END){
		state(s_START){
			light_start(0);
			next(s_TOFIRST);
		}
		
		state(s_TOFIRST){
			shut_down_in(120.);
			start();
			set_servo_position(SERV_WRIST,700);
			msleep(200);
			set_servo_position(SERV_CLAW,1050);
			msleep(100);
			create_left(87,100,350);
			create_forward(130,350);
			create_right(78,275,350);
			//create_right(5,0,300);
			create_block();
			claw_down();
			thread_start(t_sort);
			create_forward(140,250);
			create_block();
			claw_up();
			next(s_TOSECOND);
		}
		state(s_TOSECOND){
			create_backward(113,200);
			create_right(35,0,200);
			create_block();
			claw_down();
			//create_forward(70,200);
			create_left(10,600,200);
			create_forward(30,200);
			create_block();
			claw_up();
			if (close){
				next(s_CUTSHORT)
			}else{
				next(s_TOTHIRD);
			}
		}
		state(s_TOTHIRD){
			servo_set(SERV_WRIST,1400,.6);//claw closed, semidown
			claw_close();
			create_forward(100,200);
			create_left(10,700,200);
			create_left(45,0,200);//knock the botguy/cube out of the way
			create_right(43,0,200);//then go back on track
			create_send();
			create_forward(60,200);
			create_left(8,300,200);
			create_forward(60,200);
			create_stop();
			create_send();
			
			create_recieve();
			claw_open();
			create_recieve();
			set_servo_position(SERV_WRIST,1550);//all the way down
			create_forward(125,200);
			create_block();
			claw_up();
			next(s_TOFOURTH);
		}
		state(s_TOFOURTH){
			create_backward(30,200);
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
			create_backward(500,200);
			create_right(-96,250,-200);
			create_backward(200,200);
			if (wait != 0)create_block();
			switch(wait){
				case 2:
					undersea();
					play();
				case 1:
					msleep(45000);
					break;
			}
			
			GO = 0; msleep(200);//stop sorting for now
			
			create_right(-95,100,-100);
			create_backward(200,100);
			create_block();
			
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green(4);
			t_sort = thread_create(sort);
			thread_start(t_sort);
			GO = 1;
			next(s_DUMPORANGE);
		}
		
		
		state(s_CUTSHORT){
			create_backward(160,200);
			create_right(-96,150,-200);
			create_backward(270,200);
			if (wait != 0)create_block();
			switch(wait){
				case 2:
					tetris();
					play();
				case 1:
					msleep(45000);
					break;
			}
			
			create_block();
			GO = 0; msleep(200);//stop sorting for now
			
			create_right(-95,100,-100);
			create_backward(200,100);
			
			create_block();
			
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green(4);
			t_sort = thread_create(sort);
			thread_start(t_sort);
			GO = 1;
			next(s_DUMPORANGE);
		}
		state(s_DUMPORANGE){
			create_left(89,100,300);
			create_forward(350,300);
			create_right(89,0,300);
			create_backward(160,300);
			create_block();
			dump_orange();
			if (wait != 0) msleep(30000);
			create_right(-120,100,-300);
			create_block();
			
			dump_green(4);
			t_sort = thread_create(sort);
			thread_start(t_sort);
			
			
			next(s_END);
		}
		
	}
	thread_destroy(t_sort);
	ao();
	create_disconnect();
	
	return 0;
}
