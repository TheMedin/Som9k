#include <Servo.h>

// Constants
const int powerUpPin = 5;

const int buttonCalibratePin = 9;
const int buttonPin = 8;

const int servoPin = 7;

const int redLedPin = 12;
const int yellowLedPin = 11;
const int greenLedPin = 10;

int buttonState1 = 0;
int buttonState2 = 0;
int ledState = 0;

const int countdown_max = 1000;
int countdown = 1000;
const int open_angle = 70;
const int closed_angle = 10;

Servo myServo;
int value;
int threshold = 200;
int dose = 100;
int zeroLevel = 0;
double angle;

void water(int d)
{
  myServo.write(open_angle);
  delay(d);
  myServo.write(closed_angle);
}

void setup()
{
  analogReference(DEFAULT);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  pinMode(powerUpPin, OUTPUT);

  digitalWrite(redLedPin, HIGH);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonCalibratePin, INPUT);
  
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(closed_angle); 
}

void loop()
{
  buttonState1 = digitalRead(buttonPin);
  if (buttonState1 == HIGH) {
    switch(ledState) {
      case 0:
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, HIGH);
        dose = 1000;
        ledState = 1;
        break;

      case 1:
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        dose = 2000;
        ledState = 2;
        break;

      case 2:
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH);
        dose = 3000;
        ledState = 0;
        break;
    }
      while (digitalRead(buttonPin) == HIGH){
        delay(1);
    }
  }
  
  if (digitalRead(buttonCalibratePin) == HIGH) {
    water(dose);
  }

  
  digitalWrite(powerUpPin, HIGH);
  int sensor = analogRead(A0);
  if (buttonState2 == HIGH) {
    zeroLevel = sensor;
    Serial.print("New zero: ");
    Serial.println(zeroLevel);
  }
  digitalWrite(powerUpPin, LOW);
  if (sensor > threshold+zeroLevel) {
    value = 200;
    Serial.print("Potentiometer: ");
    Serial.println(sensor);
  } else {
    value = 0;
  }
  //Serial.println(angle);
}
