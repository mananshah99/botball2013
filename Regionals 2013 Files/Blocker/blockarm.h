// Created on Sat April 13 2013

#ifndef _BLOCKARM_
#define _BLOCKARM_

#define SERV_BLOCK 1
void block_up(){
	set_servo_position(SERV_BLOCK,1550);
}
void block_init(){
	enable_servo(SERV_BLOCK);
	block_up();
}
void block_down(){
	set_servo_position(SERV_BLOCK,1100);
}

#endif
