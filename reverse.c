/*
* Simple command line command to reverse motors driven from the L298N Quadruple H-bridge
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
    digitalWrite(IN2, LOW);
    pinMode(IN3, OUTPUT);
    digitalWrite(IN3, HIGH);
    pinMode (IN4, OUTPUT);
    digitalWrite (IN4, LOW);

  return 0 ;
}
