#include "slowservo.c"
#include "basic.c"

#define SERV_SORT 1
#define MOT_SORT 3
#define SERV_COMPRESS 0
void compress_down()
{
	set_servo_position(SERV_COMPRESS,200);
}
void compress_grab()
{
	set_servo_position(SERV_COMPRESS,0);
}
void compress_up()
{
	set_servo_position(SERV_COMPRESS,1700);
}
void sort_center()
{
	set_servo_position(SERV_SORT,400);
}
void sort_left()
{
	//servo_set(SERV_SORT,1100,.13);
	//msleep(150);
	set_servo_position(SERV_SORT,900);
	msleep(250);
}
void sort_right()
{
	//servo_set(SERV_SORT,0,.13);
	//msleep(150);
	set_servo_position(SERV_SORT,0);
	msleep(250);
	
}
void sort_away()
{
	set_servo_position(SERV_SORT,1650);
	msleep(150);
}
int side = 1;
int track_size_above(int col, int y)
{
	int i = 0;
	while(track_y(col,i) > y) i++;
	return (track_size(col,i));
}
void bright()
{
	system("echo 7500 > /sys/class/video4linux/video0/brightness");
	system("echo 6375 > /sys/class/video4linux/video0/contrast");
	system("echo 500 > /sys/class/video4linux/video0/exposure");
}
void dark()
{
	
	system("echo 4000 > /sys/class/video4linux/video0/brightness");
	system("echo 4000 > /sys/class/video4linux/video0/contrast");
	system("echo 100 > /sys/class/video4linux/video0/exposure");
}
int complete = 0;
int sum_size(int col)
{
	int i,n,size;
	n = track_count(col);
	size = 0;
	for(i=0;i<n;i++){
		size += track_size(col,i);
	}
	return (size);
}
#ifndef MAIN_
int main()
#else
void sort_set_side(int WhichSide)
{
	side = WhichSide;
}
void sort()
#endif
{
	int countL = 0,countR = 0;
	int spd = 375;
	int switched = 1;
	float st = seconds();
	int col;
	bright();
	sort_away();
	compress_grab();
	WaitFor(Lsen || Rsen || (seconds()-st > 10));
	complete = 1;
	compress_up();
	sleep(.8);
	sort_center();
	mav(MOT_SORT,spd*switched);
	while(!black_button())
	{
		update_wait();
		printf("%d,%d\n",track_size(0,0) , track_size(2,0));
		if (track_size(0,0) > 750 || track_size(2,0) > 700)
		{
			mrp(MOT_SORT,1000,-switched*200);
			spd *= 1.04;
			if (spd > 600) spd = 600;
			col = (track_size(0,0) < track_size(2,0))*2;
			if ((track_size(0,0) < track_size(2,0)) ^ (side))//XOR with the side, figure out which way to put it
			{sort_left(); countL++;}
			else
			{sort_right();countR++;}
			if(countL > 10 || countR > 10)
			{
				if (countL > 9)
				{countL = 9;}
				if (countR > 9)
				{countR = 9;}
				sort_away();
				compress_down();
				sleep(.65);
				compress_up();
				sleep(.55);
			}
			else
			{
				track_update();
				update_wait();
			}
			sort_center();
			update_wait();
			mav(MOT_SORT,spd*switched);
			update_wait();
			st = seconds();
		}
		if (seconds()-st > 8)
		{
			switched *= -1;
			mav(MOT_SORT,spd*switched);
			st = seconds();
		}
	}
	printf("\n%f",seconds()-st);
	sort_away();
	compress_down();
	sleep(5);
}