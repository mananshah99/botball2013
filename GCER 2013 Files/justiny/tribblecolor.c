int main()

{ 
	printf("Initiating Tibble Color\n");
	camera_open(LOW_RES);
	
	while(!side_button())
	{
		camera_update();
		if(get_object_count(0) > 0)
		{
			printf("Orange!\n");
		}
		else{printf("No Orange Detected! Retrying.\n");}
		msleep(200);
	}
	//while(!side_button()) //orange tribble sensing
	//{
	//	camera_update();
	//	if(get_object_area(0,0) != -1)
	//	{
	//		printf("Orange!\n");  
	//	}
	//	else{printf("Retrying!\n");}
	//	msleep(200);
	//}
	
	//while(!side_button()) //green tribbles sensing
	//	{
	//		camera_update();
	//		if(get_object_area(1,0) != -1)
	//		{
	//			printf("Green!\n");  
	//		}
	//		else if(get_object_area(0,0) != -1)
	//		{
	//			printf("Orange!\n");
	//		}
	//		else{printf("Retrying!\n");}
	//		msleep(200);
	
	//extra info
	//point2 bigcenter;
	//bigcenter = get_object_center(0,0);
	//printf("The center coordinates are (%d,%d)\n", bigcenter.x, bigcenter.y);
	
	//rectangle trib1;
	//trib1 = get_object_bbox(0,2);
	//printf("x coord %d y coord %d\n", trib1.x, trib1.y

}

