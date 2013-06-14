#include "./generic.h"
#define SERV_CLAW 1
#define SERV_WRIST 0
void claw_close(){
	set_servo_position(SERV_CLAW,1450);
}
void claw_open(){
	set_servo_position(SERV_CLAW,950);
}
void claw_down(){//claw down and open
	claw_open();
	servo_set(SERV_WRIST,1650,.7);
}
void claw_up(){//close claw, then raise claw and open it
	//void servo_set(int port,int end,float time)
	servo_set(SERV_CLAW,1500,.22);
	//servo_set(SERV_WRIST,700,.4);
	servo_set(SERV_WRIST,550,.5);
	set_servo_position(SERV_CLAW,1200);
	servo_set(SERV_WRIST,350,.2);
	msleep(300);
	set_servo_position(SERV_WRIST,550);
}
void claw_init(){
	set_servo_position(SERV_WRIST,300);
	set_servo_position(SERV_CLAW,805);
	enable_servo(SERV_WRIST);
	enable_servo(SERV_CLAW);
}

int main(){
	claw_init();
	while(1){
		WAIT(a_button());
		msleep(300);
		WAIT(!a_button());
		claw_down();
		msleep(300);
		claw_up();
	}
}
