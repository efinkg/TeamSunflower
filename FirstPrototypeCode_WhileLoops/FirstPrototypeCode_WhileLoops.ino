//PWM Pins
const int pwn_rot = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
const int pwn_elev = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
const int dir_rot = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
const int dir_elev = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

//Sensor Pins
const int west_sensor_pin = A3; //analog pin 0
const int east_sensor_pin = A4; //analog pin 1
const int top_sensor_pin = A2; //analog pin 2
const int down_sensor_pin = A1; //analog pin 3
const int back_sensor_pin = A0; //analog pin 4

//Battery Input Directly to show if we're charging or not
const int battery_pin = A5; //Battery input

//End Stop Pins
const int eastbutton_pin = 6;     // The number of the east endstop pin
const int westbutton_pin = 7;     // The number of the west endstop pin
const int topbutton_pin = 4;     // The number of the top endstop pin
const int bottombutton_pin = 5;     // The number of the bottom endstop pin

//Instatiate sensor values
int west_sensor_value = analogRead(west_sensor_pin);
int east_sensor_value = analogRead(east_sensor_pin);
int top_sensor_value = analogRead(top_sensor_pin);
int down_sensor_value = analogRead(down_sensor_pin);
int back_sensor_value = analogRead(back_sensor_pin);
int battery_sensor_value = analogRead(battery_pin);

int difference_threshold = 5;
int is_bright = 40;

//Initialize states
int eastbutton_state = 0;         //east button initialization 
int westbutton_state = 0;         //west button initialization
int topbutton_state = 0;         //top button initialization 
int bottombutton_state = 0;         //bottom button initialization
int val = 0;     //value for fade

void setup()
{  
  Serial.begin(9600);
  pinMode(pwn_rot, OUTPUT);  //Set control pins to be outputs
  pinMode(dir_rot, OUTPUT);
  pinMode(pwn_elev, OUTPUT);  //Set control pins to be outputs
  pinMode(dir_elev, OUTPUT);  
  
  pinMode(eastbutton_pin, INPUT);
  pinMode(westbutton_pin, INPUT);
  pinMode(topbutton_pin, INPUT);
  pinMode(bottombutton_pin, INPUT);
}

void loop()
{ 
  go_west();
  go_up();
  
  update_sensors();
  float voltage = battery_sensor_value*(5.0/1023.0);
  
  Serial.print("BatterySensor: ");
  Serial.print(voltage);
  
  Serial.print(" West Sensor : ");
  Serial.print(west_sensor_value);
  Serial.print(" East Sensor: "); 
  Serial.print(east_sensor_value);
  Serial.print(" Top Sensor: "); 
  Serial.print(top_sensor_value);
  Serial.print(" Down sensor: "); 
  Serial.print(down_sensor_value);
  Serial.println();
  
  if (eastbutton_state == HIGH) {      
    Serial.println("East EndStop is pressed!");
  } 
  if (westbutton_state == HIGH) {     
    Serial.println("West EndStop is pressed!");
  } 
  if (topbutton_state == HIGH) {      
    Serial.println("Top EndStop is pressed!");
  } 
  if (bottombutton_state == HIGH) {     
    Serial.println("Bottom EndStop is pressed!");
  } 
  
  
  if((back_sensor_value-average_value())>difference_threshold && eastbutton_state==LOW){
    while(east_sensor_value<is_bright && eastbutton_state==LOW){
      update_sensors();
      Serial.println(east_sensor_value);
      rotate_east();
    }
    Serial.println("Go east to catch the sunrise.");
  }

  while((west_sensor_value-east_sensor_value)>difference_threshold && westbutton_state==LOW){
    update_sensors();
    rotate_west();
    Serial.println("Go west.");
  }
  while((east_sensor_value-west_sensor_value)>difference_threshold  && eastbutton_state==LOW){
    update_sensors();
    rotate_east();
    Serial.println("Go east.");
  }
  
 while((top_sensor_value-down_sensor_value)>difference_threshold && topbutton_state==LOW){
    update_sensors();
    elev_up();
    Serial.println("Elevate up");
  }
  while((down_sensor_value-top_sensor_value)>difference_threshold && bottombutton_state==LOW){
    update_sensors();
    elev_down();
    Serial.println("Elevate Down");
  }
  

  stopped();      // stop for 2 seconds
}

void update_sensors(){
  //Look at all photosensors
  west_sensor_value = analogRead(west_sensor_pin);
  east_sensor_value = analogRead(east_sensor_pin);
  top_sensor_value = analogRead(top_sensor_pin);
  down_sensor_value = analogRead(down_sensor_pin);
  back_sensor_value = analogRead(back_sensor_pin);
  
  average_value();

  //Check the battery voltage
  battery_sensor_value = analogRead(battery_pin);

  //Look at endstops
  westbutton_state = digitalRead(westbutton_pin);
  eastbutton_state = digitalRead(eastbutton_pin);
  topbutton_state = digitalRead(topbutton_pin);
  bottombutton_state = digitalRead(bottombutton_pin);
}

int average_value(){
     int averagevalue = (west_sensor_value+east_sensor_value+top_sensor_value+down_sensor_value)/4;
     //Serial.println(averagevalue);
     return averagevalue;
}

/* Let's take a moment to talk about these functions. The forw and back functions are simply designating the direction the motors will turn once they are fed a PWM signal.
If you only call the forw, or back functions, you will not see the motors turn. On a similar note the fade in and out functions will only change PWM, so you need to consider
the direction you were last set to. In the code above, you might have noticed that I called forw and fade in the same grouping. You will want to call a new direction, and then
declare your pwm fade. There is also a stop function. 
*/


void go_west() // no pwm defined
{ 
  digitalWrite(dir_rot, LOW);  //Reverse motor direction, 1 high, 2 low
}

void go_up() // no pwm defined
{ 
  digitalWrite(dir_elev, HIGH);  //Reverse motor direction, 3 low, 4 high  
}

void go_east() // no pwm defined
{
  digitalWrite(dir_rot, HIGH);  //Set motor direction, 1 low, 2 high
}

void go_down() // no pwm defined
{
  digitalWrite(dir_elev, LOW);  //Set motor direction, 1 low, 2 high
}

void rotate_east() //full speed go_westrd
{ 
  digitalWrite(dir_rot, LOW);  //Reverse motor direction, 1 high, 2 low
  analogWrite(pwn_rot, 200);    //set both motors to run at (100/255 = 39)% duty cycle
}

void rotate_west() //full speed backward
{
  digitalWrite(dir_rot, HIGH);  //Set motor direction, 1 low, 2 high
  analogWrite(pwn_rot, 200);   //set both motors to run at 100% duty cycle (fast)
}
void elev_up() //full speed go_westrd
{ 
  digitalWrite(dir_elev, HIGH);  //Reverse motor direction, 3 low, 4 high  
  analogWrite(pwn_elev, 200);
}

void elev_down() //full speed backward
{
  digitalWrite(dir_elev, LOW);  //Set motor direction, 3 high, 4 low
  analogWrite(pwn_elev, 200);
}

void stopped() //stop
{ 
  digitalWrite(dir_rot, LOW); //Set motor direction, 1 low, 2 high
  digitalWrite(dir_elev, LOW); //Set motor direction, 3 high, 4 low
  analogWrite(pwn_rot, 0);    //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwn_elev, 0); 
}

void fadein_rot()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(pwn_rot, fadeValue);   
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeout_rot()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(pwn_rot, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void fadein_elev()
{ 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) 
  { 
     // sets the value (range from 0 to 255):
    analogWrite(pwn_elev, fadeValue);   
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

void fadeout_elev()
{ 
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) 
  { 
    // sets the value (range from 0 to 255):
    analogWrite(pwn_elev, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);  
}
}

void stop_rot()                   //stop motor A
{
  analogWrite(pwn_rot, 0);
}

void stop_elev()                   //stop motor B
{ 
  analogWrite(pwn_elev, 0);
}
