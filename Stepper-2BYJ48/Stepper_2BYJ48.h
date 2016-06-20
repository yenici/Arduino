/**
	Stepper_2BYJ48.h
	
	Library for bidirectional operations of a 28BYJ48 stepper motor with a 5-way connector,
	using a ULN2003 interface board to drive the stepper.
	
	The 28BYJ-48 stepper motor is a 4-phase, 8-beat motor, geared down by a factor of 64.
	One bipolar winding is on motor pins 1 & 3 and the other on motor pins 2 & 4.
	The step angle is 5.625 x 1/64.

	Original library by Dmytro Novikov (dgnovikov@gmail.com)

	Special thanks to http://4tronix.co.uk/arduino/Stepper-Motors.php

*/

#ifndef Stepper_2BYJ48_H
#define Stepper_2BYJ48_H
 
#include <WProgram.h>
 
class Stepper_2BYJ48 {
	public:
		/* Parameters:
			Blue   - 28BYJ48 pin 1
			Pink   - 28BYJ48 pin 2
			Yellow - 28BYJ48 pin 3
			Orange - 28BYJ48 pin 4
			Revolutions per minute 	/ default 5

			Note: you are free to change a default parameter!
		*/
        	Stepper_2BYJ48(int motorPin1, int motorPin2, int motorPin3, int motorPin4, int revolutionsPerMinute);
        	Stepper_2BYJ48(int motorPin1, int motorPin2, int motorPin3, int motorPin4);
        	Stepper_2BYJ48();

        	~Stepper_2BYJ48();

		void setRPM(int revolutionsPerMinute); // to set the speed of rotation (in RPM)

		void doStep(int steps);	// to rotate a rotor for a predetermined number of steps ('+' - clockwise, '-' - counterclockwise).
					// One step is about 0.703125 degrees. Full revolution is equal to  +/- 512 steps.

		void rotateOnAngle(double angle);	// to rotate a rotor on the predetermined angle in degrees ('+' - clockwise, '-' - counterclockwise)

		void makeRevolutions(int revs);	// to rotate a rotor for the predetermined number of FULL revolutions ('+' - clockwise, '-' - counterclockwise)

	private:
		int pin1;
		int pin2;
		int pin3;
		int pin4;

		unsigned long delayTime;	// Time of delay in microseconds between switching
		int lookup[8];

		void stepperInit(int motorPin1, int motorPin2, int motorPin3, int motorPin4, int revolutionsPerMinute);
		void setOutput(int out);
};
 
#endif