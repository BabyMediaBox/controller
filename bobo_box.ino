    // color swirl! connect an RGB LED to the PWM pins as indicated
    // in the #defines
    // public domain, enjoy!

#include <SoftwareSerial.h>
     
#define REDPIN 5
#define GREENPIN 4
#define BLUEPIN 3
   
#define FADESPEED 5     // make this higher to slow down

String serialResponse = "";
char sz[] = "255,255,255";

void setup() {
  Serial.begin(9600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

int r = 0;
int g = 0;
int b = 0;

void fadeToBlack()
{
    for (int i = 255; i > 0; i--) 
    { 
      if( r > 0 )
      {
        r -= 1;
        analogWrite(REDPIN, r);
      }

      if( g > 0 )
      {
        g -= 1;
        analogWrite(GREENPIN, g);
      }

      if( b > 0 )
      {
        b -= 1;
        analogWrite(BLUEPIN, b);
      }
      delay(FADESPEED);
    }
}

void transitionToColor( int toRed, int toGreen, int toBlue)
{
  for (int i = 0; i < 256; i++)
  {
     if( toRed > r )
     {
        r += 1;
        
     } 
     else 
     {
        r = toRed;
     }

     

     if( toGreen > g )
     {
        g += 1;   
     }
     else
     {
        g = toGreen;
     }

     if( toBlue > b )
     {
        b += 1;
     }
     else
     {
        b = toBlue;
     }

     
     analogWrite(REDPIN, r);
     analogWrite(GREENPIN, g);
     analogWrite(BLUEPIN, b);
     delay(FADESPEED);
  }
}

void loop() {
    

    if ( Serial.available()) 
    {
      serialResponse = Serial.readStringUntil("\r\n"); // \r\n
      // Convert from String Object to String.
      char buf[sizeof(sz)];
      serialResponse.toCharArray(buf, sizeof(buf));
      char *p = buf;
      char *str;
      int matchTimes = 0;
      r = 0;
      g = 0;
      b = 0;
      while ((str = strtok_r(p, ",", &p)) != NULL)
      {        
        if( matchTimes == 0 )
        { //r 
          r = atoi(str);
        }
        else if( matchTimes == 1 )
        { // g
          g = atoi(str);
        }
        else if( matchTimes == 2 )
        { // b
          b = atoi(str);
        }
        
        matchTimes+=1;
      }
      analogWrite(REDPIN, r);
      analogWrite(GREENPIN, g);
      analogWrite(BLUEPIN, b);
  }
}
