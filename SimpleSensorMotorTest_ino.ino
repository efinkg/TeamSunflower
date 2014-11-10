/*
 5/22/2012
  Timothy Holmberg
  SparkFun Electronics
  
  This code includes the ddition of fade in and out PWM. Also a stop feature. And the addition of individual functions for motor control 
  
  This was a revision of the example sketch that originated from Pete Dokter's code for Arduino that shows very basically how to control an Ardumoto 
  motor driver shield with a 5V Arduino controller board. http://www.sparkfun.com/datasheets/DevTools/Arduino/Ardumoto_test_3.pde
  
  This also includes parts of the Fading Example,  Created 1 Nov 2008 By David A. Mellis, modified 30 Aug 2011 By Tom Igoe http://arduino.cc/en/Tutorial/Fading
 
*/

int pwm_a = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13
int val = 0;     //value for fade
int LDR_Pin0 = A0; //analog pin 0
int LDR_Pin1 = A1; //analog pin 1
int LDR_Pin2 = A2; //analog pin 2
int LDR_Pin3 = A3; //analog pin 3

void setup()
{  
  Serial.begin(9600);
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(dir_a, OUTPUT);
  pinMode(pwm_b, OUTPUT);  //Set control pins to be outputs
  pinMode(dir_b, OUTPUT);  
}

void loop()
{ 
  forwA();
  forwB();
  int sensor0 = analogRead(LDR_Pin0);
  int sensor1 = analogRead(LDR_Pin1);
  int sensor2 = analogRead(LDR_Pin2);
  int sensor3 = analogRead(LDR_Pin3);
  Serial.print("Sensor 0: ");
  Serial.print(sensor0);
  Serial.print(" Sensor 1: "); 
  Serial.print(sensor1);
  Serial.print(" Sensor 2: "); 
  Serial.print(sensor2);
  Serial.print(" Sensor : "); 
  Serial.print(sensor3);
  Serial.println();

  while((sensor0-sensor1)>100){
    sensor0 = analogRead(LDR_Pin0);
    sensor1 = analogRead(LDR_Pin1);
    backwardA();
    Serial.println("Motor A Backward");
  }
  while((sensor1-sensor0)>100){
    sensor0 = analogRead(LDR_Pin0);
    sensor1 = analogRead(LDR_Pin1);
    forwardA();
    Serial.println("Motor A Backward");
  }
  
 while((sensor2-sensor3)>100){
    sensor2 = analogRead(LDR_Pin2);
    sensor3 = analogRead(LDR_Pin3);
    forwardB();
    Serial.println("Motor B Forward");
  }
  while((sensor3-sensor2)>100){
    sensor2 = analogRead(LDR_Pin2);
    //Serial.println(sensor2);
    sensor3 = analogRead(LDR_Pin3);
    backwardB();
    Serial.println(sensor3);
    Serial.println("Motor B Backward");
  }
  
  stopped();      // stop for 2 seconds
  
}


/* Let's take a moment to talk about these functions. The forw and back functions are simply designating the direction the motors will turn once they are fed a PWM signal.
If you only call the forw, or back functions, you will not see the motors turn. On a similar note the fade in and out functions will only change PWM, so you need to consider
the direction you were last set to. In the code above, you might have noticed that I called forw and fade in the same grouping. You will want to call a new direction, and then
declare your pwm fade. There is also a stop function. 
*/

void forwA() // no pwm defined
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
}

void forwB() // no pwm defined
{ 
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
}

void backA() // no pwm defined
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
}

void backB() // no pwm defined
{
  digitalWrite(dir_b, LOW);  //Set motor direction, 1 low, 2 high
}

void forwardA() //full speed forward
{ 
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  analogWrite(pwm_a, 200);    //set both motors to run at (100/255 = 39)% duty cycle
}

void backwardA() //full speed backward
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  analogWrite(pwm_a, 200);   //set both motors to run at 100% duty cycle (fast)
}
void forwardB() //full speed forward
{ 
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwm_b, 200);
}

void backwardB() //full speed backward
{
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  analogWrite(pwm_b, 200);
}

void stopped() //stop
{ 
  digitalWrite(dir_a, LOW); //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW); //Set motor direction, 3 high, 4 low
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 0); 
}

void fadeinA()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);   
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeoutA()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(pwm_a, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void fadeinB()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(pwm_b, fadeValue);   
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeoutB()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(pwm_b, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void astop()                   //stop motor A
{
  analogWrite(pwm_a, 0);    //set both motors to run at 100% duty cycle (fast)
}

void bstop()                   //stop motor B
{ 
  analogWrite(pwm_b, 0);    //set both motors to run at 100% duty cycle (fast)
}
