#define MAX_SERVO_NUM   16
#define MAX_SERVO_ANGLE 180

struct MotorState{
  int motorNumber;
  int angle;
};

MotorState tokenizeReceived(String msg){
    if(msg[0] != 'm')
      return {-1, -1};
    
    int motorNum = getDigit(msg, 1);
    int angle = getDigit(msg, _find(msg, '.')+1);    
    
    if (motorNum == -1 || motorNum >= MAX_SERVO_NUM || angle == -1 || angle > MAX_SERVO_ANGLE)
      return {-1, -1};  
    
    return {motorNum, angle};
}

int _find(String msg, char wanted){
  for(int i = 0; i < msg.length(); i++){
      if (msg[i] == wanted)
        return i;
  }
  return -1;
}

int getDigit(String msg, int index){
  String result = "";
  while(isDigit(msg[index])){
    result += msg[index];
    index++;
  }
  return result.toInt();
}

void setup() {
  Serial.begin(9600);
  MotorState m = tokenizeReceived("m0.180");
  Serial.println(m.motorNumber);
  Serial.println(m.angle);
}

void loop() {}
