/*
 Name:		SoftwareSystem.ino
 Created:	2017/5/10 20:38:29
 Author:	houqh13
*/

#include <Arm7Bot.h>

Arm7Bot Arm;
double offset[SERVO_NUM] = {-4.526, 0.99, -6.134, 3.421, 1.08, 0, 0};			// north
//double offset[SERVO_NUM] = {-7.824, 8.874, -5.83, -5.331, 6.563, 0, 0};		// south

// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(BAUD_RATE);
	Arm.setOffsets(offset);
	Arm.initialMove();
	for (int i = 0; i < SERVO_NUM; i++)
	{
		Arm.maxSpeed[i] = 40;
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.additionCom();
}
