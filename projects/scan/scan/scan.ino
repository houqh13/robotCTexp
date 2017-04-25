/*
 Name:		scan.ino
 Created:	2017/4/10 15:35:51
 Author:	houqh13
*/
#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_n[5] = {-7.824, 8.874, -5.83, -5.331, 6.563};

// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(BAUD_RATE);
	for (int i = 0; i < 5; i++)
	{
		Arm.offset[i] = offset_n[i];
	}
	lowSpeed();
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.additionCom();
	if (Arm.allConverge())
	{
		Arm.sendToPC(1);
	}
}

// Make the end of 7Bot revolve around a point on a horizontal plane
// x, y, z: coordinate of the center of the trajectory
// r: radius of the trajectory
// angle: radian of the trajectory
// delta: motion step
void circlePoses(double x, double y, double z, double r, double angle, double delta) {
	double mx, my, mz = z;
	double vx, vy, vz = 0;
	for (double theta = 0; theta <= angle; theta = theta + delta) {
		ARMPORT.print("theta= ");
		ARMPORT.println(theta);
		mx = x + r * sin(theta / 180 * PI);
		my = y - r * cos(theta / 180 * PI);
		vx = 0 - sin(theta / 180 * PI);
		vy = cos(theta / 180 * PI);
		ARMPORT.print("mx= ");
		ARMPORT.print(mx);
		ARMPORT.print(" my= ");
		ARMPORT.print(my);
		ARMPORT.print(" vx= ");
		ARMPORT.print(vx);
		ARMPORT.print(" vy= ");
		ARMPORT.println(vy);
		Arm.moveIK5(PVector(mx, my, mz), PVector(vx, vy, vz));
		delay(100);
		Arm.getPosD();
		ARMPORT.println();
		delay(1000);
	}
}

void lowSpeed() {
	Arm.maxSpeed[0] = 30;
	Arm.maxSpeed[1] = 40;
	Arm.maxSpeed[2] = 40;
	Arm.maxSpeed[3] = 50;
	Arm.maxSpeed[4] = 60;
	Arm.maxSpeed[5] = 60;
	Arm.maxSpeed[6] = 60;
}