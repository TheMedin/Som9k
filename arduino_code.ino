#include <Servo.h>

// Constants
const int powerUpPin = 5;

const int buttonCalibratePin = 6;
const int buttonPin = 8;

const int servoPin = 9;

const int openLedPin = 7;
const int redLedPin = 12;
const int yellowLedPin = 11;
const int greenLedPin = 10;

int buttonState1 = 0;
int buttonState2 = 0;
int ledState = 0;

Servo myServo;
int value;
int threshold = 200;
int zeroLevel = 0;
double angle;

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
  
}

void loop()
{
  buttonState1 = digitalRead(buttonPin);
  if (buttonState1 == HIGH) {
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
  
  buttonState2 = digitalRead(buttonCalibratePin);
  
  digitalWrite(powerUpPin, HIGH);
  delay(100);
  int sensor = analogRead(A0);
  if (buttonState2 == HIGH) {
    zeroLevel = sensor;
    Serial.print("New zero: ");
    Serial.println(zeroLevel);
  }
  digitalWrite(powerUpPin, LOW);
  if (sensor > threshold+zeroLevel) {
    value = 200;
    digitalWrite(openLedPin, HIGH);
    Serial.print("Potentiometer: ");
    Serial.println(sensor);
  } else {
    value = 0;
    digitalWrite(openLedPin, LOW);
  }
  angle = map(value, 0, 1023, 0, 180);
  //Serial.println(angle);
  myServo.write(angle);
  delay(500);
}
