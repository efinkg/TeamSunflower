int LDR_Pin0 = A0; //analog pin 0
int LDR_Pin1 = A1; //analog pin 1
int LDR_Pin2 = A2; //analog pin 2
int LDR_Pin3 = A3; //analog pin 3
int LDR_Pin4 = A4; //analog pin 4
int LDR_Pin5 = A5; //analog pin 5

void setup(){
  Serial.begin(9600);
}

void loop(){
  int LDRReading0 = analogRead(LDR_Pin0);
  int LDRReading1 = analogRead(LDR_Pin1);
  int LDRReading2 = analogRead(LDR_Pin2);
  int LDRReading3 = analogRead(LDR_Pin3);
  int LDRReading4 = analogRead(LDR_Pin4);
  int LDRReading5 = analogRead(LDR_Pin5);
  
  Serial.print("Sensor 0: ");
  Serial.print(LDRReading0);
  Serial.print(" Sensor 1: "); 
  Serial.print(LDRReading1);
  Serial.print(" Sensor 2: "); 
  Serial.print(LDRReading2);
  Serial.print(" Sensor : "); 
  Serial.print(LDRReading3);
  Serial.print(" Sensor 5: "); 
  Serial.print(LDRReading4);
  Serial.print(" Sensor 6: ");
  Serial.print(LDRReading5);
  Serial.println();
  delay(250); //just here to slow down the output for easier reading
}
