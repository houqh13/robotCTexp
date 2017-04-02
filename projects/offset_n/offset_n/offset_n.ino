/*
 Name:		offset_n.ino
 Created:	2017/3/29 14:08:41
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_n[5] = {-3.792, 1.223, -5.861, 0.888, 1.537};

// the setup function runs once when you press reset or power the board
void setup() {
	Arm.initialMove();
	delay(2000);
	for (int i = 0; i < 5; i++)
	{
		Arm.offset[i] = offset_n[i];
	}
	double initial_pos[7] = {90, 115, 65, 90, 90, 90, 75};
	Arm.move(initial_pos);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Arm.receiveCom();
}
