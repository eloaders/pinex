/*
* Install wiringPi first: https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/
*Simple command line command to stop motors driven from the L298N Quadruple H-bridge 
* Compile with: cc -o stop -I/usr/local/include stop.c -L/usr/local/lib -lwiringPi
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

    //1
    pinMode (IN1, OUTPUT);
    digitalWrite (IN1, HIGH);
    pinMode(IN2, OUTPUT);
    digitalWrite(IN2, HIGH);
    pinMode(IN3, OUTPUT);
    digitalWrite(IN3, HIGH);
    pinMode (IN4, OUTPUT);
    digitalWrite (IN4, HIGH);
    
    printf("Stopping motors...\n");

  return 0 ;
}