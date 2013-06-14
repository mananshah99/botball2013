// Created on Sat March 30 2013

int main()
{
	int x = 50;
	mav(0,50);
	mav(1,50);
	printf("test");
	while(!side_button())
	{
		msleep(10);
		if(a_button())
		{
			x = x + 10;
			mav (0,x);
			mav (1,x);
			printf("test2/n");
		}
		if(b_button())
		{
			x = x - 10;
			mav (0,x);
			mav (1,x);
			printf("test3/n");
		}
		if(c_button())
		{
			x = x * -1;
			mav (0,x);
			mav (1,x);
			printf("test4/n");	
		}
	}
	off(1);
	off(2);
}
