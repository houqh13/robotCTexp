/*
 Name:		offset_s.ino
 Created:	2017/4/2 16:05:23
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;
double offset_n[5] = {-7.364, 4.921, -4.972, -4.765, 6.628};

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

