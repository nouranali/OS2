#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
// vcc=5, gnd=gnd, SDA=A4, SCL=A5

#define m1f 2 //  The Left Front motor Forword
#define m1r 4 //  The Left Front motor Backword
#define m2f 5 // The Right Front motor Forword 
#define m2r 7 // The Right Front motor Backword
#define m1pwm 3 // The Left Front motor PWM
#define m2pwm 6 // The Right Front motor PWM

char state;
int flag = 0;
int speed_c = 160;
int op = 12;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.clear();
  lcd.print("Welcome!");
  lcd.setCursor(2, 1);
  lcd.print("to out project");
  pinMode(m1f, OUTPUT);
  pinMode(m1r, OUTPUT);
  pinMode(m2r, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m1pwm, OUTPUT);
  pinMode(m2pwm, OUTPUT);
  pinMode(op, OUTPUT);
  Serial.begin(9600);

}
void loop() {

  flag = 0;
  state = Serial.read();

  if (state == '0') {
    off(0);
    if (flag == 0) {
      Serial.println("Robot: off");
      flag = 1;
    }
  }
  else if (state == '1') { //LEFT
    left(speed_c);
    if (flag == 0) {
      Serial.println("Robot: LEFT");
      flag = 1;

    }
  }
  else if (state == '2') { //RIGHt
    right(speed_c);
    if (flag == 0) {
      Serial.println("Robot: RIGHT");
      flag = 1;

    }
  }
  else if (state == '3') { //Forward

    forward(speed_c);
    if (flag == 0) {
      Serial.println("Robot: Forward");
      flag = 1;
      digitalWrite(op, HIGH);
      delay(500);
      digitalWrite(op, LOW);


    }
  }
  else if (state == '4') { //BACKWARD
    backward(speed_c);
    if (flag == 0) {
      Serial.println("Robot: LEFT");
      flag = 1;

    }
  }
}

void forward(int speed_c) {
  digitalWrite(m1r, HIGH);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, HIGH);
  digitalWrite(m2r, LOW);
  analogWrite(m1pwm, speed_c);
  analogWrite(m2pwm, speed_c);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Moving Forward");



}
void backward(int speed_c) {
  digitalWrite(m1r, LOW);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, LOW);
  digitalWrite(m2r, HIGH);
  analogWrite(m1pwm, speed_c);
  analogWrite(m2pwm, speed_c);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Moving Backward");



}
void right(int speed_c) {
  digitalWrite(m1r, HIGH);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, HIGH);
  digitalWrite(m2r, LOW);
  analogWrite(m1pwm, speed_c);
  analogWrite(m2pwm, speed_c - 60);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("To the Right");


}
void left(int speed_c) {
  digitalWrite(m1r, HIGH);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, HIGH);
  digitalWrite(m2r, LOW);
  analogWrite(m1pwm, speed_c - 60);
  analogWrite(m2pwm, speed_c);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("To the Left");
}
void off(int speed_c) {
  digitalWrite(m1r, LOW);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, LOW);
  digitalWrite(m2r, LOW);
  analogWrite(m1pwm, speed_c);
  analogWrite(m2pwm, speed_c);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Stopped");


}
