#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600

#define MAX_SERVO_NUM 16
#define MAX_SERVO_ANGLE 180

struct MotorState
{
  int motorNumber;
  int angle;
};

String _receive();

MotorState tokenizeReceived(String msg);
int _find(String msg, char wanted);
int getDigit(String msg, int index);
void writeToMotors(MotorState m);

void setup()
{
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);
  //yield();
}

void loop()
{
  String msg = _receive();
  if (msg != "")
    Serial.println(msg);
  MotorState m = tokenizeReceived(msg);
  writeToMotors(m);

  /*
  // debug stuff
  if (msg != ""){
    Serial.println(m.motorNumber);
    Serial.println(m.angle);
  }
  */
  delay(100);
}

String _receive()
{
  String msg = "";
  if (Serial.available())
  {
    while (Serial.available())
    {
      char _char = Serial.read();
      msg += _char;
    }
    // if (msg != "") Serial.println(msg);
    return msg;
  }
  return "";
}

MotorState tokenizeReceived(String msg)
{
  if (msg[0] != 'm')
    return {-1, -1};

  int motorNum = getDigit(msg, 1);
  int angle = getDigit(msg, _find(msg, '.') + 1);

  if (motorNum == -1 || motorNum >= MAX_SERVO_NUM || angle == -1 || angle > MAX_SERVO_ANGLE)
    return {-1, -1};

  return {motorNum, angle};
}

int _find(String msg, char wanted)
{
  for (int i = 0; i < msg.length(); i++)
  {
    if (msg[i] == wanted)
      return i;
  }
  return -1;
}

int getDigit(String msg, int index)
{
  String result = "";
  while (isDigit(msg[index]))
  {
    result += msg[index];
    index++;
  }
  return result.toInt();
}

void writeToMotors(MotorState m)
{
  if (m.angle != -1 && m.motorNumber != -1)
  {
    int pulse = map(m.angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(m.motorNumber, 0, pulse);
  }
}
