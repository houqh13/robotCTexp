/*
 Name:		setup_n.ino
 Created:	2017/4/20 15:08:18
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_n[SERVO_NUM] = {-4.526, 0.99, -6.134, 3.421, 1.08, 0, 0};


// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(BAUD_RATE);
	Arm.setOffsets(offset_n);
	Arm.initialMove();
	for (int i = 0; i < SERVO_NUM; i++)
	{
		ARMPORT.print("offset[");
		ARMPORT.print(i);
		ARMPORT.print("] = ");
		ARMPORT.println(Arm.offset[i]);
	}
	Arm.moveIK5(PVector(0, 165, 200), PVector(0, 1, 0));
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.receiveCom();
}