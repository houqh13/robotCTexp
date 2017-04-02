/*
 Name:		calibration.ino
 Created:	2017/3/29 16:04:27
 Author:	houqh13
*/

#include <Arm7Bot.h>
Arm7Bot Arm;


// the setup function runs once when you press reset or power the board
void setup() {
	ARMPORT.begin(115200, SERIAL_8N1);
	Arm.initialMove();
	lowSpeed();

	// set the preset position
	Arm.moveIK5(PVector(125, 177.5, -29), PVector(0, 0, -1));

	// receive current detected position
	// input 254(0xFE), 253(0xFD), 1 in the serial monitor in order
	// WARNING: DO NOT input other characters & numbers!!!
	for (int i = 0; i < 3; i++)
	{
		while (!ARMPORT.available())
		{
			delay(10);
		}
		Arm.receiveCom();
	}

	Arm.initialMove();
	Arm.forcelessMode();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// move 7Bot to the preset position manually
	// input 254(0xFE), 253(0xFD), 1 in the serial monitor in order
	// repeat several times to get a better result
	Arm.receiveCom();
}

void lowSpeed() {
	Arm.maxSpeed[0] = 15;
	Arm.maxSpeed[1] = 20;
	Arm.maxSpeed[2] = 20;
	Arm.maxSpeed[3] = 30;
	Arm.maxSpeed[4] = 30;
	Arm.maxSpeed[5] = 30;
	Arm.maxSpeed[6] = 30;
}