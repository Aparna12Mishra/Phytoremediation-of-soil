
/*
 
 All the resources for this project:
 http://randomnerdtutorials.com/
 
*/

#include <LiquidCrystal.h>         

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Digital pins to which you connect the LCD
const int tempPin = A0;                   // A0 is where you connect the sensor
int rainPin = A1;
int sensorPin = A2; 
int greenLED = 6;
int redLED = 7;
// you can adjust the threshold value
int thresholdValue = 650;

bool moisture = false;

void setup(){
  lcd.begin(16,2);
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600);
}

void loop() {
  int blue_potmeter = analogRead(sensorPin);
  int temp_value = analogRead(tempPin); // read the value from the sensor
  float millivolts = (temp_value / 1024.0) * 5000; 
  float celsius = millivolts / 12;
  Serial.println();
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" °C or ");
  Serial.print((celsius * 9)/5 + 32);
  Serial.println(" °F");
  Serial.println("__________________________________");
  Serial.println();
  delay(1500);  
  
  
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  
  if (moisture == false){
    sensorValue = blue_potmeter; 
  }
  
  //Serial.println("Moisture sensor value: ");
  //Serial.println(sensorValue);
  if(sensorValue > thresholdValue){
    Serial.print("No lead found");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("No lead found          ");
  }
   if(sensorValue < thresholdValue){
    Serial.print("Lead found");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Lead found           ");
  }
  Serial.print(" (");
  Serial.print(sensorValue);
  Serial.println(")");
  Serial.println("__________________________________");
  delay(1500);
}

