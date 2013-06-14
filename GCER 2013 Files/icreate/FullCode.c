// Created on Fri April 5 2013
#define MAIN
#include "./generic.h"
#include "./createDrive.h"
#include "./sorting.h"
//sorting now also includes claw


#define s_SEEDSTART  0
#define s_TOFIRST    1
#define s_TOSECOND   2 
#define s_TOTHIRD    3
#define s_TOFOURTH   4
#define s_RETURN     5
#define s_DUMPORANGE 6   
#define s_TOFIFTH    7
#define s_TOSIXTH    8 
#define s_TOSEVEN    9
#define s_TOEIGHT    10
#define s_FINAL      11
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
	Get_Mode();
	start();
	if (currstate != s_SEEDSTART){
		thread_start(t_sort);
	}
	while(currstate != s_END){
		state(s_SEEDSTART){
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
			msleep(5000);
			next(s_TOTHIRD);
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
				/*create_block();
				tetris();
				play();
				wait_till(75);*/
			create_right(-96,250,-200);
			create_backward(230,200);
			create_send();
			create_right(-95,100,-100);
			create_backward(200,100);
			create_stop();
			
			create_recieve();
			GO = 0; msleep(200);//stop sorting for now
			create_block();
			
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green(3);
			t_sort = thread_create(sort);
			thread_start(t_sort);
			GO = 1;
			next(s_DUMPORANGE);
		}
		state(s_DUMPORANGE){
			create_left(89,100,300);
			create_forward(350,300);
			create_right(89,0,300);
			create_backward(170,300);
			create_block();
			dump_orange();
			
			next(s_TOFIFTH);
		}
		state(s_TOFIFTH){ 
			claw_open();
			create_left(89,310,300);
			create_forward(215,300);
			create_left(45,0,300);
			create_forward(75,150);
			create_right(10,600,150);
			create_right(45,170,150);
			//create_forward(50,300);
			create_right(-87,80,-300);
			create_backward(140,250);
			create_stop();
			servo_set(SERV_WRIST,830,.4);
			create_block();
			
			create_drive_direct(-35,-35);
			msleep(1700);
			claw_down();
			create_stop();
			
			create_right(7,50,250);
			create_forward(115,200);
			create_left(21,350,250);
			create_forward(200,200);
			create_block();
			claw_up();
			next(s_TOSIXTH);
		}
		state(s_TOSIXTH){
			create_backward(105,200);
			create_block();
			claw_down();
			create_right(28,0,200);
			//create_left(5,200,200);
			create_forward(135,200);
			create_block();
			claw_up();
			msleep(5000);
			next(s_TOSEVEN);
		}
		state(s_TOSEVEN){
			servo_set(SERV_WRIST,1400,.6);//claw closed, semidown
			claw_close();
			create_forward(60,200);
			create_left(24,700,200);
			create_left(50,0,200);//knock the botguy/cube out of the way
			create_right(42,0,200);//then go back on track
			create_send();
			create_forward(145,200);
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
			next(s_FINAL);
		}
		state(s_FINAL){
			create_right(-5,250,-300);
			create_backward(500,300);
				/*create_block();
				tetris();
				play();
				wait_till(75);*/
			create_left(-96,250,-300);
			create_backward(300,300);
			create_left(-90,100,-300);
			create_block();
			
			//wait_till(100);
			dump_orange();
			
			create_forward(50,300);
			create_right(89,100,300);
			create_forward(375,300);
			create_left(89,0,300);
			create_backward(30,300);
			create_left(50,0,300);
			create_send();
			create_backward(60,100);
			create_stop();
			
			create_recieve();
			GO = 0; msleep(200);//stop sorting for now
			thread_destroy(t_sort);off(MOT_SORT);//make sure it's really stopped
			dump_green(5);
			printf("COMPLETE");
			next(s_END);
		}
		state(s_TESTING){
			/*set_servo_position(SERV_WRIST,400);
			claw_down();
			msleep(500);
			claw_up();*/
			thread_start(t_sort);
			//msleep(120000);
			//create_right(-45,750,-100);
			//create_block();
			WAIT(c_button());
			next(s_END);
		}
	}
	thread_destroy(t_sort);
	ao();
	create_disconnect();
	
	return 0;
}
