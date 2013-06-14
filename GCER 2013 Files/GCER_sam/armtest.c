// Created on Wed June 12 2013
#define SERV_ARM 1
void grab(){
	set_servo_position(SERV_ARM,650);
	msleep(1500);
	set_servo_position(SERV_ARM,1700);
	msleep(1000);
}
int main()
{
	enable_servo(SERV_ARM);
	while(1){
		msleep(1000);
		grab();
	}
	printf("Hello, World!\n");
	return 0;
}
