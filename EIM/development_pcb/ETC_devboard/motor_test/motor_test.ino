#include <PID_v1.h>

int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;
int currentSensePin = A0;
int angleSensePin = A3;


bool directionState;
int current;
double setpoint;
double speed;
double angle;
const int deadband = 50;
const int maxpower = 200;

double Kp=5, Ki=2, Kd=0.35;
PID myPID(&angle, &speed, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  TCCR3B = TCCR3B & B11111000 | B00000001;    // set timer 3 divisor to     1 for PWM frequency of 31372.55 Hz
  Serial.begin(9600);
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(currentSensePin, INPUT);
  pinMode(angleSensePin, INPUT);
  directionState = false;
  spinAtSpeed(0);
  setpoint = 50;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-1*maxpower, maxpower);
}

void loop() {
  current = measureCurrent();
  angle = measureAngle();
  myPID.Compute();
  //plot();
  sweep();
  //take_input();
}

void spinAtSpeed(int spd) {
  if(spd >= 0){
    digitalWrite(directionPin, HIGH);
  }
  else{
    digitalWrite(directionPin, LOW);
  }
  if (spd == 0) {
    digitalWrite(brakePin, HIGH);
  }
  else {
    digitalWrite(brakePin, LOW);
    analogWrite(pwmPin, abs(spd) + deadband);
  }
}

int measureCurrent() {
  int adc = analogRead(currentSensePin);
  return map(adc, 0, 1023, 0, 2000);
}

int measureAngle() {
  int adc = analogRead(angleSensePin);
  return map(adc, 0, 1023, 0, 100);
}

void plot() {
  static long last_plot = millis();
  if ((millis() - last_plot) > 1000) {
    spinAtSpeed(speed);
    Serial.print("angle:");
    Serial.println(angle);
    Serial.print("current:");
    Serial.println(current);
    Serial.print("speed:");
    Serial.println(speed);
    Serial.print("setpoint:");
    Serial.println(setpoint);
  }
}

void sweep() {
  static long last_step = millis();
  static int dir = 1;
  if ((millis() - last_step) > 1000) {
    setpoint = setpoint + 15 * dir;
    Serial.print("setpoint:");
    Serial.println(setpoint);
    last_step = millis();
  }
  if (setpoint > 90) {
    dir = -1;
  }
  else if (setpoint < 10) {
    dir = 1;
  }
}

void take_input() {
  setpoint = Serial.parseInt();
}
