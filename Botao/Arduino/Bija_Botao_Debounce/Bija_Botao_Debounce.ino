/*
TrinketKeyboard example
For Trinket by Adafruit Industries
*/
 
#include <TrinketKeyboard.h>
 
#define BUT_PIN 2
#define LED_PIN 0
 
void setup()
{
  // input, pull up
  pinMode(BUT_PIN, INPUT);
  digitalWrite(BUT_PIN, HIGH);

  pinMode(LED_PIN, OUTPUT);
  // start USB stuff
  TrinketKeyboard.begin();
}


bool butPress = false;
bool lastButState = true;

bool currPress = false;

unsigned long lastButPressTime = 0;


unsigned long lastWaitTime = 0;
int wait = 0;

void loop()
{
  // the poll function must be called at least once every 10 ms
  // or cause a keystroke
  // if it is not, then the computer may think that the device
  // has stopped working, and give errors
  TrinketKeyboard.poll();

  
 if(!digitalRead(2)){ //or if(analogRead(_) < X)
    butPress = true;
    }
  else if(digitalRead(2)){ //or if(analogRead(_) > Y)
    butPress = false;
    }


  if(butPress != lastButState && butPress == true && currPress == false){
    currPress = true;
    TrinketKeyboard.typeChar(32);
    lastButPressTime = millis();
    digitalWrite(LED_PIN, HIGH);
    }
  
  if(long(millis() - lastButPressTime) > 50){
    digitalWrite(LED_PIN, LOW);
    }

  if(long(millis() - lastWaitTime) > 200 && currPress){
    lastWaitTime = millis();
    if ( (wait % 2) == 0) {
      digitalWrite(LED_PIN, HIGH); 
      }
      else{
        digitalWrite(LED_PIN, LOW); 
        }
    wait--;
    }
    
  if(wait < 0){
    wait = 25;
    currPress = false;
  }
  
  lastButState = butPress;  

}


