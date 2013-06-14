#include <stdio.h>

/******************************

TO DO LIST

1. find the number of blobs on the screen 
2. if there are no blobs, refresh camera until there are
3. find the biggest blob on screen
4. differentiate colors of the biggest blob
5. when differentiated, make the motors finish the movement

******************************/

int main()

{ 
	
	printf("Initiating Tribble Color\n");
	camera_open(LOW_RES);
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
	}
	/*printf("Initiating Tribble Color\n");
	camera_open(LOW_RES);
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
	/*	while(!side_button()) //orange tribble sensing
	{
	camera_update();
	if(get_object_area(0,0) != -1)
	{
	printf("Orange!\n");  
	}
	else{printf("Retrying!\n");}
	msleep(200);
	}
	
	while(!side_button()) //green tribbles sensing
	{
	camera_update();
	if(get_object_area(1,0) != -1)
	{
	printf("Green!\n");  
	}
	else if(get_object_area(0,0) != -1)
	{
	printf("Orange!\n");
	}
	else{printf("Retrying!\n");}
	msleep(200);
	
	*/
}
