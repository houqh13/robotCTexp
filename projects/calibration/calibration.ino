#include <Arm7Bot.h>
Arm7Bot Arm;

//double offsetValues[SERVO_NUM] = {20, 0, 0, 0, 0, 0, -50};

void setup() {

//	// Set offset values
//	for(int i=0; i<SERVO_NUM; i++)
//	  Arm.offset[i] = offsetValues[i];

	/* Test */
	// initial 7Bot Arm to check the offset values are work
	Arm.initialMove();
	delay(500);
	for (int i = 0; i > -40; i -= 2)
	{
		Arm.moveIK5(PVector(0, 207.5, i), PVector(0, 0, -1));
		delay(1000);
	}
	//Arm.moveIK5(PVector(0, 207.5, 49), PVector(0, 0, -1));
}

void loop() {

}