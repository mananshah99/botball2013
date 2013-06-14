// Created on Fri March 22 2013

void backward_time(int m1, int m2, int speed, int mseconds)
  {
      motor(m1,-speed);
      motor(m2,-speed);
      msleep(mseconds);
  }
  
int main()
{
	while(!a_button())
	{
		backward_time(0,3,200,300);
	}
	
}
