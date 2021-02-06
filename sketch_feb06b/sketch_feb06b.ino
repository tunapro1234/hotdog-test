void setup() {
  Serial.begin(9600); // set the baud rate
  // Serial.println("Ready"); // print "Ready" once
  pinMode(2, OUTPUT);
}


void loop() {  
  String msg = _receive();
  
  if (msg != "") Serial.println(msg);
  
  if (msg == "on")        digitalWrite(2, LOW );
  else if (msg == "off")  digitalWrite(2, HIGH);
  
  delay(100);
}

String _receive(){
  String msg = "";
  if (Serial.available()){
    while(Serial.available()){
      char _char = Serial.read();
      msg += _char;
    }
    return msg;
  }
  return "";
}
