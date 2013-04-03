// Created on Sat March 30 2013
#define aligndist 150
#include "createDrive.c"

int main()
{
	create_special_connect(); // because create_connect didn't want to work
	create_drive_direct_dist(350,350,90); // drive out of the starting position
	create_drive_direct_right(300,500,20); // first turn right
	create_drive_direct_right(100,500,80); // complete the turn right and end up near the first tribble box that matters
	create_block();
	msleep(2000); // simulates the create picking up the tribbles
	create_drive_direct_left(100,2,55); // move to the next pile
	create_block();
	create_backward(20,200); // goes to the next pile of tribbles
	msleep(2000); //waits, simulating the create picking up tribbles
	
	/*
	create_drive_direct(500,500); // for right now, this is the create driving on the main road
	
	create_wait_event(LEFT_BUMP); // this is aligning and turning into the base on the other side. 
	create_backward(aligndist,500);
	create_drive_direct_left(100,500,81);
	*/
	create_disconnect();
	
}


//by Manan :)
