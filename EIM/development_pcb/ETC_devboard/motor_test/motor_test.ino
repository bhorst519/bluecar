#include <PID_v1.h>

int directionPin = 5;
int pwmPin = 6;
int angleSensePin = A3;


double setpoint;
double speed;
double angle;
const int deadband = 10;
const int maxpower = 200;

double Kp=3, Ki=0.5, Kd=0;
PID myPID(&angle, &speed, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(angleSensePin, INPUT);
  spinAtSpeed(0);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-1*maxpower, maxpower);
  setpoint = 60.0;
}

void loop() {
  angle = measureAngle();
  myPID.Compute();
  spinAtSpeed(speed);
  plot();
  sweep();
  // //take_input();
}

void spinAtSpeed(int spd) {
  if(spd >= 0){
    digitalWrite(directionPin, HIGH);
  }
  else{
    digitalWrite(directionPin, LOW);
  }
  if(spd < 2) {
    digitalWrite(pwmPin, LOW);
  }
  else {
    analogWrite(pwmPin, abs(spd) + deadband);
  }
}

double measureAngle() {
  int adc = analogRead(angleSensePin);
  return (double)(adc - 0.0f) * 100.0f / (4095.0f);
}

void plot() {
  static long last_plot = millis();
  if ((millis() - last_plot) > 1000) {
    Serial.print("angle:");
    Serial.println(angle);
    Serial.print("speed:");
    Serial.println(speed);
    Serial.print("setpoint:");
    Serial.println(setpoint);
  }
}

void sweep() {
  static long last_step = millis();
  static int dir = 1;
  if ((millis() - last_step) > 3000) {
    setpoint = setpoint + 15 * dir;
    last_step = millis();
  }
  if (setpoint > 80) {
    dir = -1;
  }
  else if (setpoint < 20) {
    dir = 1;
  }
}

void take_input() {
  setpoint = Serial.parseInt();
}
