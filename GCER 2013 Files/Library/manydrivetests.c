//primary driving code
#include "./generic.h"
#define MOT_LEFT 1//Polyp edition!
#define MOT_RIGHT 3
#define PI 3.14159265358979
#define SPD 1000
#define SPDl 1000.
#define SPDr 1000.
#define rdistmult (SPDr/SPDl)

#define ks 16//distance from one wheel to another in cm
#define wheeldiameter 5.3

#define CMtoBEMF (1010/wheeldiameter/PI)
#define LBUMP digital(14)
#define RBUMP digital(15) //left/right back bump sensors (used for square_back())


#define drive_off() off(MOT_RIGHT) ;off(MOT_LEFT)
#define drive(mL,mR) mav(MOT_LEFT,mL);mav(MOT_RIGHT,mR)
#define gmpc(mot) get_motor_position_counter(mot)

#define WAITPASS(thing,position); if((thing)>(position)){WAIT((thing)<=(position));}else{WAIT((thing)>=(position));}
void right(float degrees, float radius, int mode){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=(long)round((((2*radius+ks)*CMtoBEMF)*PI)*degrees/360.);
	long turnr=(long)round((((2*radius-ks)*CMtoBEMF)*PI)*degrees/360.);
	if(turnl == 0) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	if (mode < 2){
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
		if (mode == 1)
			drive_off();
	} else {
		long endpos = gmpc(MOT_LEFT)+turnl;
		mav(MOT_RIGHT,turnrspeed);
		mav(MOT_LEFT,SPD);
		WAITPASS(gmpc(MOT_LEFT),endpos);
		if (mode==2)drive_off();
		if (mode==3){freeze(MOT_LEFT);freeze(MOT_RIGHT);}
		return;
	}
}
void forward(float distance, int mode){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	if (mode>=2){
		long endpos = gmpc(MOT_RIGHT)+newdist;
		mav(MOT_RIGHT,SPDr);
		mav(MOT_LEFT,SPDl);
		WAITPASS(gmpc(MOT_RIGHT),endpos);
		if (mode==2)drive_off();
		if (mode==3){freeze(MOT_LEFT);freeze(MOT_RIGHT);}
		return;
	}
	mrp(MOT_RIGHT,SPDr,newdist*rdistmult);
	mrp(MOT_LEFT,SPDl,newdist);
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
	if (mode == 1)
		drive_off();
}

int getmode(){
	printf("a b c");
	while(1){
		msleep(10);
		if(a_button())
			return 0;
		if (b_button())
			return 1;
		if (c_button())
			//return 2;
		//if (side_button())
			return 3;
	}
}
int main(){
	while(1){
		int a = getmode();
		forward(10,a);
		msleep(400);
		right(90,ks/2,a);
		forward(10,a);
		right(90,ks/2,a);
		forward(10,a);
		right(90,ks/2,a);
		forward(10,a);
		right(90,ks/2,a);
	}
	return 0;
}
