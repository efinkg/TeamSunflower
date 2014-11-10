/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:\
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int eastbutton_pin = 4;     // The number of the east endstop pin
const int westbutton_pin = 5;     // The number of the west endstop pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int eastbutton_state = 0;         // variable for reading the pushbutton status
int westbutton_state = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(eastbutton_pin, INPUT);
  pinMode(westbutton_pin, INPUT);  
  Serial.begin(9600);
}

void loop(){
  // read the state of the pushbutton value:
  eastbutton_state = digitalRead(eastbutton_pin);
  westbutton_state = digitalRead(westbutton_pin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (eastbutton_state == HIGH) {      
    Serial.println("East EndStop is pressed!");
  } 
  if (westbutton_state == HIGH) {     
    Serial.println("West EndStop is pressed!");
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
