#include <Arm7Bot.h>
Arm7Bot Arm;

void setup() {
	ARMPORT.begin(115200, SERIAL_8N1);
	Arm.initialMove();
	delay(500);
	// (0, 207.5, -29) is the preset position
	Arm.moveIK5(PVector(0, 207.5, -29), PVector(0, 0, -1));
	Arm.initialMove();
	Arm.forcelessMode();
}

void loop() {
	// move 7Bot to the preset position
	// input 254(0xFE), 253(0xFD), 1 in the serial monitor in order
	// suggest repeating several times
	Arm.receiveCom();
}