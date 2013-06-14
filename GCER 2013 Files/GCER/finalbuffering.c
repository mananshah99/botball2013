#ifndef _FINALCREATEBUFFERING
#define _FINALCREATEBUFFERING
#include "finalcreate.c"
//to separate files




//this is for 255 buffer scripting or just good old plain scripting
void create_wait_time(int time)//time is in deciseconds
{
    create_write_byte(155);
    create_write_byte(time);
}
void create_special_connect(){
	serial_init();
	create_write_byte(128);
	create_write_byte(132);
	create_power_led(250,254);
	atexit(create_disconnect);
}
void create_wait_dist(int dist)//dist is in mm
{
    create_write_byte(156);
    create_write_int(dist);
}
void create_wait_angle(int angle)//degrees, negative = right
{
    create_write_byte(157);
    create_write_int(angle);
}
void create_wait_event(int event)//see #defines for possible answers.  Use 255-event for the inverse
{
    create_write_byte(158);
    create_write_byte(event);
}

void create_drive_direct_dist(int r_speed, int l_speed, int dist)
{
    create_write_byte(145);
    create_write_int(r_speed);
    create_write_int(l_speed);
    create_wait_dist(dist);
}
void create_drive_direct_left(int r_speed, int l_speed, int angle)
{
    create_write_byte(145);
    create_write_int(r_speed);
    create_write_int(l_speed);
    create_wait_angle(angle);
}
void create_drive_direct_right(int r_speed, int l_speed, int angle)
{
    create_write_byte(145);
    create_write_int(r_speed);
    create_write_int(l_speed);
    create_wait_angle(-angle);
}
void create_turn_right(int angle, int radius, int speed)
{
    create_write_byte(137);
    create_write_int(speed);
    create_write_int(-radius);
    create_wait_angle(-angle);
}
void create_turn_left(int angle, int radius, int speed)
{
    create_write_byte(137);
    create_write_int(speed);
    create_write_int(radius);
    create_wait_angle(angle);
}
void create_forward(int dist, int speed)
{
    create_write_byte(145);
    create_write_int(speed);
    create_write_int(speed);
    create_wait_dist(dist);
}
void create_backward(int dist, int speed)
{
    create_write_byte(145);
    create_write_int(-speed);
    create_write_int(-speed);
    create_wait_dist(-dist);
}
void create_crash()
{
	create_write_byte(7);
}

void output_sen_0()
{
	create_write_byte(147);
	create_write_byte((0*1)+(0*2)+(1*4));
}

void stop_output()
{
	create_write_byte(147);
	create_write_byte(0);
}


#endif
