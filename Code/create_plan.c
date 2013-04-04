// Created on Sat March 30 2013
#define aligndist 150
#include "createDrive.c"

void drive_out()
{
	create_drive_direct_dist(350,350,90); // drive out of the starting position
	create_drive_direct_right(300,500,20); // first turn right
	create_drive_direct_right(100,500,80); // complete the turn right and end up near the first tribble box that matters	
}

int main()
{
	create_special_connect(); // because create_connect didn't want to work
	drive_out();
	create_block();
	msleep(2000); // simulates the create picking up the tribbles
	create_drive_direct_left(100,2,55); // move to the next pile
	create_block();
	create_backward(20,200); // backs up so the claw can fit properly
	msleep(2000); //waits, simulating the create picking up tribbles
	
	
	
	/*
	create_drive_direct(500,500); // for right now, this is the create driving on the main road
	
	create_wait_event(LEFT_BUMP); // this is aligning and turning into the base on the other side. 
	create_backward(aligndist,500);
	create_drive_direct_left(100,500,81);
	*/
	create_disconnect();
	
}

//all the cde does so far is picks up the first two piles of tribbles. I need to replicate the code to pick up the other 2 piles. 
