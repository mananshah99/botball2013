// Created on Fri April 5 2013
#define MAIN
#include "./generic.h"
#include "./createDrive.h"
#include "./sorting.h"
//sorting now also includes claw


#define s_SEEDSTART  0
#define s_TOFIRST    1
#define s_TOSECOND   2 
#define s_MIDTHING   3
#define s_TOTHIRD    4
#define s_TOFOURTH   5
#define s_RETURN     6
#define s_DUMPORANGE 7   
#define s_TOFIFTH    8
#define s_FINAL      9
#define s_TESTING   742

#define s_END 666

//currstate defined in generic
#define MENUSIZE 6
#include "./menu.h"
struct menuitem menu[] = {
	{s_SEEDSTART,"seed"},
	{s_TOFIRST,"first"},
	{s_RETURN,"return"},
	{s_DUMPORANGE,"dump orange"},
	{s_TOFIFTH,"to fifth"},
	{s_TESTING,"testing"}};



int main()
{
	int submode = 0;
	printf("Connecting...\n");
	create_connect();
	camera_open(LOW_RES);
	printf("Complete!\n");
	
	claw_init();
	sort_center();
	reset_orange();
	
	thread t_sort = thread_create(sort);
	//next(s_SEEDSTART);
	Get_Mode();
	start();
	if (currstate != s_SEEDSTART) thread_start(t_sort);
	while(currstate != s_END){
		state(s_SEEDSTART){
			light_start(0);
			next(s_TOFIRST);
		}
		state(s_TOFIRST){
			start();
			set_servo_position(SERV_WRIST,700);
			msleep(200);
			set_servo_position(SERV_CLAW,1050);
			msleep(100);
			create_left(87,0,350);
			create_forward(185,350);
			create_right(85,305,350);
			create_block();
			claw_down();
			thread_start(t_sort);
			create_forward(195,250);
			create_block();
			claw_up();
			next(s_TOSECOND);
		}
		state(s_TOSECOND){
			create_backward(105,200);
			create_right(25,0,200);
			create_block();
			claw_down();
			create_forward(130,200);
			create_block();
			claw_up();
			msleep(5000);
			next(s_TOTHIRD);
		}
		state(s_TOTHIRD){
			servo_set(SERV_WRIST,1400,.6);//claw closed, semidown
			claw_close();
			create_forward(65,200);
			create_left(20,700,200);
			create_left(40,0,200);//knock the botguy/cube out of the way
			create_right(45,0,200);//then go back on track
			create_send();
			create_forward(100,200);
			create_left(8,300,200);
			create_stop();
			create_send();
			
			create_recieve();
			claw_open();
			create_recieve();
			set_servo_position(SERV_WRIST,1550);//all the way down
			create_forward(95,200);
			create_block();
			claw_up();
			next(s_TOFOURTH);
		}
		state(s_TOFOURTH){
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
			if (submode == 0){
				next(s_RETURN);
			}else{
				next(s_FINAL);
			}
		}
		state(s_RETURN){
			create_backward(500,200);
				/*create_block();
				tetris();
				play();
				wait_till(75);*/
			create_right(-96,250,-200);
			create_backward(200,200);
			create_right(-95,100,-100);
			create_block();
			GO = 0; msleep(200);//stop sorting for now
			
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green();
			t_sort = thread_create(sort);
			thread_start(t_sort);
			GO = 1;
			next(s_DUMPORANGE);
		}
		state(s_DUMPORANGE){
			create_left(89,100,300);
			create_forward(375,300);
			create_right(89,0,300);
			create_backward(200,300);
			create_block();
			dump_orange();
			
			next(s_TOFIFTH);
		}
		state(s_TOFIFTH){
			claw_open();
			create_forward(50,300);
			create_left(89,235,300);
			create_forward(270,300);
			create_left(45,0,300);
			create_forward(75,300);
			create_right(8,600,300);
			create_right(50,150,300);
			create_forward(50,300);
			create_right(-90,100,-300);
			create_backward(50,250);
			create_stop();
			servo_set(SERV_WRIST,830,.4);
			create_block();
			create_drive_direct(-50,-50);
			msleep(1500);
			create_stop();
			
			claw_down();
			
			create_right(15,50,250);
			create_forward(200,200);
			create_left(25,350,250);
			create_forward(200,200);
			create_block();
			claw_up();
			submode = 1;
			next(s_TOSECOND);
		}
		state(s_FINAL){
			create_right(-5,250,-200);
			create_backward(500,200);
				/*create_block();
				tetris();
				play();
				wait_till(75);*/
			create_left(-96,250,-200);
			create_backward(300,200);
			create_left(-90,100,-100);
			create_block();
			
			//wait_till(100);
			dump_orange();
			
			create_right(89,100,300);
			create_forward(375,300);
			create_left(89,0,300);
			create_backward(200,300);
			create_block();
			
			GO = 0; msleep(200);//stop sorting for now
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green();
			t_sort = thread_create(sort);
			thread_start(t_sort);
			GO = 1;
			printf("COMPLETE");
			next(s_END);
		}
		state(s_TESTING){
			/*set_servo_position(SERV_WRIST,400);
			claw_down();
			msleep(500);
			claw_up();*/
			//thread_start(t_sort);
			//msleep(120000);
			create_right(-45,750,-100);
			create_block();
			//WAIT(c_button());
			next(s_END);
		}
	}
	thread_destroy(t_sort);
	ao();
	create_disconnect();
	
	return 0;
}
