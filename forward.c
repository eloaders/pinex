/*
*Install wiringPi first: https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/
*Simple command line command to drive motors forward with the L298N Quadruple H-bridge 
* Compile with: cc -o forward -I/usr/local/include forward.c -L/usr/local/lib -lwiringPi
* Works with a Raspberry Pi 2
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//pin numbers for wiringPi pin scheme
const int IN1 = 15;  // gpio/bcm 17
const int IN2 = 16;  // gpio/bcm 18
const int IN3 = 4;  // gpio/bcm 27
const int IN4 = 5;  // gpio/bcm 22

int main (void)
{

  if (wiringPiSetup () == -1)
    exit (1) ;

    pinMode (IN1, OUTPUT);
    digitalWrite (IN1, LOW);
    pinMode(IN2, OUTPUT);
    digitalWrite(IN2, HIGH);
    pinMode(IN3, OUTPUT);
    digitalWrite(IN3, LOW);
    pinMode (IN4, OUTPUT);
    digitalWrite (IN4, HIGH);

  return 0 ;
}