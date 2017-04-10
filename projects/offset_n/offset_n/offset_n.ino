/*
 Name:		offset_n.ino
 Created:	2017/3/29 14:08:41
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_n[5] = {-4.526, 0.99, -6.134, 3.421, 1.08};


// the setup function runs once when you press reset or power the board
void setup() {
	Arm.initialMove();
	delay(2000);
	for (int i = 0; i < 5; i++)
	{
		Arm.offset[i] = offset_n[i];
	}
	Arm.moveIK5(PVector(0, 165, 200), PVector(0, 1, 0));
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.receiveCom();
}
