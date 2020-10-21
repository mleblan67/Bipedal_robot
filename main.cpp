/*
main.cpp - main code for Bearr(Bipedal Electronic Autonomous Radical Robot) the Biped
by mostly Max Leblang & ocassionally Elijah tolten
*/
#include <Arduino.h>
#include <Servo.h>
#include <smoothServo.h>//custom servo library (BROKEN)
 
#define SMOOTH_DELAY 25
#define MOVES 11
#define STEP_AMOUNT 40
 
//pins
const int buzzerPin = 9;
const int servoPinArr[6] = {3,5,6,9,10,11};
const int powerLed = 8;
 
//declaring all objects
//servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servoArr[] = {servo1, servo2, servo3, servo4, servo5, servo6};//array to manage all servos
//buzzer
//songs mainBuzzer(buzzerPin);
//arrays for servo positions
float servoCalibArr[6] = {90, 120, 90, 80, 100, 90};//array to calibrate all servos in setup
//the bread and the butter of the project
float servoPosArr[6][MOVES] = {//specific, tested values for a nice, balanced step
    //green leg
    {90,90,50,50,50, 90,90,90,155,155,90},//servo1-hip
    {120,120,140,140,140, 120,120,120,90,90,120},//servo2-knee
    {90,20,90,90,93, 90,170,170,170,90,90},//servo3-ankle
    //black leg
    {80,80,80,65,65, 80,80,110,110,110,80},//servo4-hip
    {100,100,100,130,130, 100,100,60,60,60,100},//servo5-knee
    {90,0,0,0,90, 90,160,90,90,87,90}//servo6-ankle
 
};
 
float atPos;
float goToPos;
float servoAdd[6];
float servoWrite[6];
 
//C functions
int arr_length(float array[]){//function to get length of float array
    int length = sizeof(array)/sizeof(float);
    return length;
}
 
 
//all functions for servos
void test_servos(int low_val, int high_val, int delay_val){//function to make sure all servos work
    for(int i = 0; i<6; i++){
        servoArr[i].write(low_val);//moving all servos to low_val
        delay(delay_val);
        servoArr[i].write(high_val);//moving all servos to high_val
        delay(delay_val);
    }
}
 
//Main walking function
void plug_walk(){
    for(int m = 0; m < MOVES-1; m++){//looping through all servo positions
        for(int i = 0; i < 6; i++){
            servoWrite[i] = servoPosArr[i][m];//resetting servoWrite to each servoPos based on m
        }
        for(int i = 0; i < STEP_AMOUNT; i++){
            for(int s = 0; s < 6; s++){//writing to each servo
                atPos = servoPosArr[s][m];//the angle we're at
                goToPos = servoPosArr[s][m+1];//the angle we want the servo to go to
                servoAdd[s] = (goToPos - atPos)/STEP_AMOUNT;//direction (+ or -) and amount (STEP_AMOUNT)
                servoWrite[s] += servoAdd[s];
                servoArr[s].write(servoWrite[s]);
            }
            delay(SMOOTH_DELAY);//delaying for smoothness
        }
    }
 
}
 
void setup()
{
    pinMode(powerLed, OUTPUT);//setting up power LED
    //attaching and calibrating all servo objects
    for(int i = 0; i<6; i++){
        servoArr[i].attach(servoPinArr[i]);//attaching
        servoArr[i].write(servoCalibArr[i]);//calibrating
    }
 
 
    Serial.begin(9600);
    delay(4000);
}
 
void loop()
{
    digitalWrite(powerLed, HIGH);//showing power is on
    Serial.println("I am Bearr! Fear me!!");//necessary declaration of power
    delay(100);
    plug_walk();//PLUUUUGG!!
}
