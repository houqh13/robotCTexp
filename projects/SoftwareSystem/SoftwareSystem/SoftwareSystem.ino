/*
 Name:		SoftwareSystem.ino
 Created:	2017/5/10 20:38:29
 Author:	houqh13
*/

#include <Arm7Bot.h>

Arm7Bot Arm;
//double offset[SERVO_NUM] = {-4.375, 1.000, 0.125, 3.125, -3.000, 0, 0};			// north
double offset[SERVO_NUM] = {-7.125, -0.500, 4.375, -3.875, -1.000, 2.000, 0};		// south

// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(BAUD_RATE);
	Arm.setOffsets(offset);
	Arm.initialMove();
	for (int i = 0; i < SERVO_NUM; i++)
	{
		Arm.maxSpeed[i] = 60;
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.additionCom();
}
