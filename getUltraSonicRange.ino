#define TRIG_PIN 2
#define ECHO_PIN 3

// Hàm lấy khoảng cách đo được của cảm biến siêu âm
int sensorDetectionRange(int TRIG, int ECHO){  
  sendSensorSignal(TRIG);
  
  int cm = receivedSensorSignal(ECHO);
  
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();
  return cm;
}

// Hàm phát tín hiệu của cảm biến
// nhận 1 params là số PORT phát/nhận tín hiệu
void sendSensorSignal(int portNumber){
  pinMode(portNumber, OUTPUT);
  
  digitalWrite(portNumber, LOW);
  delayMicroseconds(2);
  digitalWrite(portNumber, HIGH);
  delayMicroseconds(5);
  digitalWrite(portNumber, LOW);
}

// Hàm nhận tín hiệu của cảm biến, trả về 1 con số theo cm ở kiểu long
// nhận 1 params là số PORT phát/nhận tín hiệu
long receivedSensorSignal(int portNumber){
  long duration, cm;
  pinMode(portNumber, INPUT);
  
  duration = pulseIn(portNumber, HIGH);
  cm = microSecToCenti(duration);
  
  return cm;
}

// Hàm chuyển đổi tín hiệu nhận được của cảm biến thành cm, 
// nhận 1 param là thời gian ở micro, 
// trả về 1 con số theo cm ở kiểu long
long microSecToCenti(long duration){
  return duration / 29 / 2;
}
