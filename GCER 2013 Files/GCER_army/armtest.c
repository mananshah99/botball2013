// Created on Thu June 6 2013
#include "generic.h"
#include "createDrive.h"

#define SERV_CLAW 1
void claw_close(){
	set_servo_position(SERV_CLAW,2040);
}
void claw_open(){
	set_servo_position(SERV_CLAW,646);
}

#define MOT_ARM  3//the mot_arm that isn't the create
//#define MOT_ARM2 2//the mot_arm that isn't the create

#define SEN_ARM() (digital(15))
int main()
{
	create_connect();
	enable_servo(SERV_CLAW);
	//clear_motor_position_counter(MOT_ARM);
	beep();
	claw_close();
	sleep(1);
	fd(MOT_ARM);//fd(MOT_ARM2);
	create_motors(4);
	WAIT(SEN_ARM());
	create_motors(0);
	//off(MOT_ARM);off(MOT_ARM2);
	freeze(MOT_ARM);//freeze(MOT_ARM2);
	
	sleep(1);
	bk(MOT_ARM);//bk(MOT_ARM2);
	msleep(400);
	ao();
	//mtp(MOT_ARM,0,1000);
	//bmd(MOT_ARM);
	claw_open();
	sleep(1);
	
	return 0;
}
