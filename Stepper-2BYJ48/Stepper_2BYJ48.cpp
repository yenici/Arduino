#include "Arduino.h"
#include "Stepper_2BYJ48.h"

Stepper_2BYJ48::Stepper_2BYJ48(int motorPin1, int motorPin2, int motorPin3, int motorPin4, int revolutionsPerMinute) {
	stepperInit(motorPin1, motorPin2, motorPin3, motorPin4, revolutionsPerMinute);
}

Stepper_2BYJ48::Stepper_2BYJ48(int motorPin1, int motorPin2, int motorPin3, int motorPin4) {
	stepperInit(motorPin1, motorPin2, motorPin3, motorPin4, 5);
}

Stepper_2BYJ48::~Stepper_2BYJ48(){
}

void Stepper_2BYJ48::stepperInit(int motorPin1, int motorPin2, int motorPin3, int motorPin4, int revolutionsPerMinute){
	this->pin1 = motorPin1;
	this->pin2 = motorPin2;
	this->pin3 = motorPin3;
	this->pin4 = motorPin4;
  	
	//declare the motor pins as outputs
	pinMode(this->pin1, OUTPUT);
	pinMode(this->pin2, OUTPUT);
	pinMode(this->pin3, OUTPUT);
	pinMode(this->pin4, OUTPUT);

	setRPM(revolutionsPerMinute);
	
	this->lookup[0] = B01000;
	this->lookup[1] = B01100;
	this->lookup[2] = B00100;
	this->lookup[3] = B00110;
	this->lookup[4] = B00010;
	this->lookup[5] = B00011;
	this->lookup[6] = B00001;
	this->lookup[7] = B01001;
}

void Stepper_2BYJ48::setOutput(int out){
	digitalWrite(this->pin1, bitRead(this->lookup[out], 0));
	digitalWrite(this->pin2, bitRead(this->lookup[out], 1));
	digitalWrite(this->pin3, bitRead(this->lookup[out], 2));
	digitalWrite(this->pin4, bitRead(this->lookup[out], 3));
	delayMicroseconds(this->delayTime);
}

void Stepper_2BYJ48::setRPM(int revolutionsPerMinute){
	this->delayTime = 14648UL / revolutionsPerMinute;  // 60 000 000 / (512 * 8 * revolutionsPerMinute)
}

void Stepper_2BYJ48::doStep(int steps){
	int n = 8 * abs(steps);
	for(int i = 0; i < n; i++){
		if(steps < 0)
			setOutput(i % 8);
		else
			setOutput(7 - i % 8);
	}
	digitalWrite(this->pin1, 0);
	digitalWrite(this->pin4, 0);
}

void Stepper_2BYJ48::rotateOnAngle(double angle){
	int steps = int(angle / (0.703125)); // 0.703125 = 360 / 512
	doStep(steps);
}

void Stepper_2BYJ48::makeRevolutions(int revs){
	int n = abs(revs);
	int m;
	if(revs > 0)
		m = 512;
	else
		m = -512;
	for(int i = 0; i < n; i++)	
		doStep(m);
}