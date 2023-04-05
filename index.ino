#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180

//Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 9;
int rightMotorPin2 = 10;

//Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 7;
int leftMotorPin2 = 8;

//Sensor3
int Backup_sensor = 4;

//Ultra sonic
int TRIG = 2;
int ECHO = 3;

void setup()
{
  //set frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  rotateMotor(0,0);   
  pinMode(Backup_sensor,INPUT);
}


void loop()
{
  delay(50);
  int distance = sensorDetectionRange(TRIG, ECHO);     // doc khoang cach
  if (distance <= 15 && distance > 0)
  {
    rotateMotor(0,0);
    delay(50);
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    delay(100);
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    delay(300);
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    delay(100);
  }

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
    rotateMotor(-240, 240); 
  }
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
    rotateMotor(240, -240); 
  } 
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH && digitalRead(Backup_sensor) == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  else
  {
    rotateMotor(0, 0);
  }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)    //ham di chuyen moto 
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    delay(200);
    if(rightMotorSpeed == 0)
    { 
      digitalWrite(rightMotorPin1,LOW);
      digitalWrite(rightMotorPin2,LOW);
    }      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, 200);
  analogWrite(enableLeftMotor, 200);    
}

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
