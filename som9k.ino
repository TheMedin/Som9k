  #include <Servo.h>

// Constants
const int buttonCalibratePin = 9;
const int buttonPin = 8;

const int servoPin = 7;

const int lowLEDPin = 12;
const int midLEDPin = 11;
const int hiLEDPin = 10;

const int sensorPowerPin = 6;
  
int buttonState1 = 0;
int buttonState2 = 0;
int ledState = 0;

int dryPoint = 300;

const int countdownMax = 100;
int countdown = 100;
const int openAngle = 70;
const int closedAngle = 10;

Servo myServo;
int value;
int threshold = 200;
int dose = 1000;
int zeroLevel = 0;
double angle;

int measure() 
{
  digitalWrite(sensorPowerPin, HIGH);
  int reading = analogRead(A5); 
  Serial.print("Potentiometer: ");
  Serial.println(reading);
  Serial.print("dryPoint: ");
  Serial.println(dryPoint);
  return reading;
}

void water(int d)
{
  showLED();
  Serial.println("watering");
  myServo.write(openAngle);
  delay(d);
  myServo.write(closedAngle);
  countdown = countdownMax;
}

void info() 
{
  Serial.print("dryPoint: ");
  Serial.println(dryPoint);
  Serial.print("sensor: ");
  Serial.println(analogRead(A5));
  toggle();toggle();toggle();
}

void setup()
{
  analogReference(DEFAULT);
  
  pinMode(lowLEDPin, OUTPUT);
  pinMode(midLEDPin, OUTPUT);
  pinMode(hiLEDPin, OUTPUT);

  digitalWrite(lowLEDPin, HIGH);
  
  pinMode(buttonPin, INPUT);
  pinMode(buttonCalibratePin, INPUT);

  pinMode(sensorPowerPin, OUTPUT);
  pinMode(A5, INPUT);
    
  Serial.begin(9600);
  Serial.print("hello");
  myServo.attach(servoPin);
  myServo.write(closedAngle);
  toggle(); toggle(); toggle();
}

void showLED() {
      switch(ledState) {
      case 0:
        digitalWrite(lowLEDPin, HIGH);
        digitalWrite(midLEDPin, LOW);
        digitalWrite(hiLEDPin, LOW);
        break;
      case 1:
        digitalWrite(lowLEDPin, LOW);
        digitalWrite(midLEDPin, HIGH);
        digitalWrite(hiLEDPin, LOW);
        break;
      case 2:
        digitalWrite(lowLEDPin, LOW);
        digitalWrite(midLEDPin, LOW);
        digitalWrite(hiLEDPin, HIGH);
        break;
    }    
  }

void blink() {
  for (int i = 0; i < 10; i++) {
        digitalWrite(lowLEDPin, HIGH);
        digitalWrite(midLEDPin, HIGH);
        digitalWrite(hiLEDPin, HIGH);
        delay(100);
        digitalWrite(lowLEDPin, LOW);
        digitalWrite(midLEDPin, LOW);
        digitalWrite(hiLEDPin, LOW);
        delay(100);
  }
  showLED();
  Serial.println("blinking!");
}

void toggle() {
      switch(ledState) {
      case 0:
        dose = 2000;
        ledState = 1;
        Serial.println("set dose to medium");
        break;

      case 1:
        dose = 3000;
        ledState = 2;
        Serial.println("set dose to high");
        break;

      case 2:
        dose = 1000;
        ledState = 0;
        Serial.println("set dose to low");
        break;
    }
      showLED();
      while (digitalRead(buttonPin) == HIGH){
        delay(1);
    }
}

void loop()
{
  if (countdown > 0) {
    countdown--;
  } else {
    digitalWrite(lowLEDPin, LOW);
    digitalWrite(midLEDPin, LOW);
    digitalWrite(hiLEDPin, LOW);
  }
  delay(1);

  buttonState1 = digitalRead(buttonPin);
  if (buttonState1 == HIGH) {
    toggle();
  }
  
  if (digitalRead(buttonCalibratePin) == HIGH) {
    dryPoint = measure();
    Serial.print("New dryPoint: ");
    Serial.println(dryPoint);
    blink();
  }
  
  Serial.print("countdown: ");
  Serial.println(countdown);
  if (measure() < dryPoint && countdown == 0) 
  {
    water(dose);
  }
}
