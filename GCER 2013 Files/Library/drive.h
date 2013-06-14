
#ifndef _DRIVE_H_
#define _DRIVE_H_

//primary driving code
#define MOT_LEFT 0//Polyp edition!
#define MOT_RIGHT 1
#define PI 3.14159265358979
#define SPD 1000
#define SPDl 1000.
#define SPDr 1000.
#define rdistmult (SPDr/SPDl)
#define TRUE 1
#define FALSE 0

#define ks 16//distance from one wheel to another in cm
#define wheeldiameter 5.3

#define CMtoBEMF (1010/wheeldiameter/PI)
#define LBUMP digital(14)
#define RBUMP digital(15) //left/right back bump sensors (used for square_back())


#define drive_off() off(MOT_RIGHT) ;off(MOT_LEFT)
#define drive(mL,mR) mav(MOT_LEFT,mL);mav(MOT_RIGHT,mR)
#define gmpc(mot) get_motor_position_counter(mot)
void square_back()
{
	int leftPressed = FALSE,rightPressed = FALSE;
	float time = seconds();//used for timeout
	bk(MOT_LEFT);
	bk(MOT_RIGHT);
	while((leftPressed == FALSE || rightPressed == FALSE) && (seconds()-time < 10))//while the bump sensors are false & it has been less than 10 seconds
	// move backwards, if the bot is bumped, turn the motor off, and break out of the loop
	{
		if (LBUMP){//if the left sensor is pressed
			motor(MOT_LEFT,40);//turn towards wall
			leftPressed = TRUE;
			} else {
			bk(MOT_LEFT);//otherwise, approach the wall more
			leftPressed = FALSE;
		}
		
		if (RBUMP){//if the right sensor is pressed
			 motor(MOT_RIGHT,40);//turn towards wall
			rightPressed = TRUE;
			} else {
			bk(MOT_RIGHT);//otherwise, approach the wall more
			rightPressed = FALSE;
		}
		msleep(1);//give other processes time to do things
	}
	drive_off();//turn both motors off at end
}


void right(float degrees, float radius){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void left(float degrees, float radius){//turn left a number of degrees with a certain radius
	int turnlspeed;
	long turnl=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnr == 0l) return;
	turnlspeed = round((float)turnl/(float)turnr*SPD);
	mrp(MOT_RIGHT, SPD,turnr);
	if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnlspeed < 50){
		turnlspeed = 0;
		turnl=0l;
		off(MOT_LEFT);
		}else{
		mrp(MOT_LEFT,turnlspeed,turnl);
	}
	bmd(MOT_LEFT);
	bmd(MOT_RIGHT);
}
void forward(float distance){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	mrp(MOT_RIGHT,SPDr,newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
void backward(float distance){//go backward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;
	mrp(MOT_RIGHT,SPDr,-newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,-newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}
#endif
