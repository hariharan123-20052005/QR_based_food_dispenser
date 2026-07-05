/*
  QR Based Automated Food Dispenser System

  Controller : ESP32
  Features:
  - QR Authentication
  - Firebase Firestore Integration
  - HX711 Load Cell Weight Monitoring
  - Ultrasonic Object Detection
  - DC Motor Control
  - Servo Gate Mechanism
  - LCD Display

  Developed by: Hariharan K S
*/

#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Firebase Configuration
#define FIREBASE_PROJECT_ID "YOUR_PROJECT_ID"
#define FIREBASE_API_KEY "YOUR_API_KEY"

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Firebase Login
const char* firebaseEmail = "YOUR_EMAIL";
const char* firebasePassword = "YOUR_PASSWORD";

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;


// LCD
LiquidCrystal_I2C lcd(0x27,16,2);


// Motor Driver Pins
#define IN1 32
#define IN2 33
#define ENA 14

#define IN3 27
#define IN4 26
#define ENB 12


// Ultrasonic
#define TRIG_PIN 16
#define ECHO_PIN 17


// Load Cell
#define DT 4
#define SCK 5

HX711_ADC LoadCell(DT,SCK);


// Servo Motors
#define SERVO_PIN 25
#define SERVO2_PIN 23

Servo gateServo;
Servo mixingServo;


float calibrationValue = 210.99;
float weight = 0;


void setup()
{
 Serial.begin(115200);


 lcd.init();
 lcd.backlight();

 lcd.print("System Ready");


 WiFi.begin(ssid,password);

 while(WiFi.status()!=WL_CONNECTED)
 {
  delay(500);
 }


 config.api_key = FIREBASE_API_KEY;

 auth.user.email = firebaseEmail;
 auth.user.password = firebasePassword;


 Firebase.begin(&config,&auth);
 Firebase.reconnectWiFi(true);


 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(ENA,OUTPUT);

 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(ENB,OUTPUT);


 pinMode(TRIG_PIN,OUTPUT);
 pinMode(ECHO_PIN,INPUT);


 gateServo.attach(SERVO_PIN);
 mixingServo.attach(SERVO2_PIN);


 LoadCell.begin();
 LoadCell.start(1000,true);
 LoadCell.setCalFactor(calibrationValue);


 Serial.println("Food Dispenser Ready");
}



long getDistance()
{
 digitalWrite(TRIG_PIN,LOW);
 delayMicroseconds(2);

 digitalWrite(TRIG_PIN,HIGH);
 delayMicroseconds(10);

 digitalWrite(TRIG_PIN,LOW);

 long duration=pulseIn(ECHO_PIN,HIGH);

 return duration*0.034/2;
}



void startMotor()
{
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);

 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);

 analogWrite(ENA,255);
 analogWrite(ENB,255);
}



void stopMotor()
{
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);

 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);

 analogWrite(ENA,0);
 analogWrite(ENB,0);
}



void loop()
{

 long distance=getDistance();


 if(distance<=23)
 {

  LoadCell.tare();


  startMotor();

  gateServo.write(90);


  while(weight<195)
  {

   if(LoadCell.update())
   {

    weight=abs(LoadCell.getData());

    lcd.clear();
    lcd.print(weight);

   }

  }


  stopMotor();

  gateServo.write(180);


  lcd.clear();
  lcd.print("Completed");

 }

}
