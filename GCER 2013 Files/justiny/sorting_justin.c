//put your sorting code here

#define SERV_SORT 0

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


int main()
{ 
  int tribcount = 0, st = seconds();
	printf("Initiating Tribble Color\n");
	camera_open(LOW_RES);
  while(tribcount <= 30 && seconds()-st < 8)
  {
    if(get_object_count(0) > 2)  //2 is the min value
  	{
			printf("Orange!\n");
      sort_left();
      
		}
		if(get_object_count(1) > 2)
		{
			printf("Green!\n");
      sort_right();
		}
    tribcount++;
  }
  
 /* }
  }
	while(!side_button())
	{
		camera_update();
		if(get_object_count(0) > 2)  //2 is the min value
		{
			printf("Orange!\n");
		}
		if(get_object_count(1) > 2)
		{
			printf("Green!\n");
		}
		else{}
		msleep(10);
	}*/
}
