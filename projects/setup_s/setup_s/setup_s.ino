/*
 Name:		setup_s.ino
 Created:	2017/4/20 15:10:35
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_s[SERVO_NUM] = {-7.824, 8.874, -5.83, -5.331, 6.563, 0, 0};


// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(BAUD_RATE);
	Arm.setOffsets(offset_s);
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