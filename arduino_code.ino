#include <Servo.h>

// Constants
const int buttonPin = 8;
const int redLedPin = 12;
const int yellowLedPin = 11;
const int greenLedPin = 10;
const int openLedPin = 13;

int buttonState = 0;
int ledState = 0;

Servo myServo;
int value;
int threshold;
double angle;

void setup()
{
  analogReference(DEFAULT);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  
  digitalWrite(redLedPin, HIGH);
  
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600); // ?
  myServo.attach(9);
  
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    switch(ledState) {
      case 0:
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, HIGH);
		threshold = 400;
        ledState = 1;
        break;

      case 1:
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
		threshold = 650;
        ledState = 2;
        break;

      case 2:
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH);
		threshold = 200;
        ledState = 0;
        break;
    }
  }

  int sensor = analogRead(A0);
  Serial.println(sensor);
  if (sensor > threshold) {
    value = 100;
    digitalWrite(openLedPin, HIGH);
  } else {
    value = 0;
    digitalWrite(openLedPin, LOW);
  }
  angle = map(value, 0, 1023, 0, 180);
  //Serial.println(angle);
  myServo.write(angle);
  delay(500);
}