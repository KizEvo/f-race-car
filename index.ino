// C++ code
//
//
// Please read README.txt file first
//
//
// Các CONSTANT cho các PORT
#define MOTOR_DRIVE_1 3
#define MOTOR_DIRECTION_1 2

#define MOTOR_DRIVE_2 5
#define MOTOR_DIRECTION_2 4

#define MOTOR_DRIVE_3 6
#define MOTOR_DIRECTION_3 7

#define MOTOR_DRIVE_4 9
#define MOTOR_DIRECTION_4 8

#define ULTSON_SENSOR_RIGHT 12
#define ULTSON_SENSOR_LEFT 13

#define MAX_FORWARD_SPEED 190
#define MAX_REVERSE_SPEED 150

// Các CONSTANT cho các biến khác nhau, 5 và 0 ở đây là HIGH và LOW
// MOVE_STOP = 1 chỉ để lặp điều kiện
const int ROTATE_LEFT = 5;
const int ROTATE_RIGHT = 0;

const int MOVE_REVERSE = 5;
const int MOVE_FORWARD = 0;
const int MOVE_STOP = 1;


// SETUP các chân trên Arduino
void setup()
{
  pinMode(MOTOR_DRIVE_1, OUTPUT);
  pinMode(MOTOR_DIRECTION_1, OUTPUT);
  
  pinMode(MOTOR_DRIVE_2, OUTPUT);
  pinMode(MOTOR_DIRECTION_2, OUTPUT);
  
  pinMode(MOTOR_DRIVE_3, OUTPUT);
  pinMode(MOTOR_DIRECTION_3, OUTPUT);
  
  pinMode(MOTOR_DRIVE_4, OUTPUT);
  pinMode(MOTOR_DIRECTION_4, OUTPUT);
   
  Serial.begin(9600);
}

// Hàm loop chính của chương trình, các hàm phụ sẽ được gọi ở đây.
// Không nên gọi các hàm config hoặc các hàm con của hàm phụ ở đây.
void loop()
{
  int distanceRight;
  int distanceLeft;
  
  distanceRight = sensorDetectionRange(ULTSON_SENSOR_RIGHT);
  distanceLeft = sensorDetectionRange(ULTSON_SENSOR_LEFT);

  if(distanceRight <= 25 & distanceRight < distanceLeft){
    Serial.println("rotate right");
    motorRotateRight();
    moveStop(2000);
  }
  
  if(distanceLeft <= 25 & distanceLeft < distanceRight){
    Serial.println("rotate left");
    motorRotateLeft();
    moveStop(2000);
  }
    
  //moveStop(2000);
  //moveForward();
  //moveStop(2000);
  //moveReverse();
  //moveStop(2000);
  
}

// Hàm điều chỉnh hướng di chuyển của bánh xe 
// hàm config
void motorDirectionConfig(int mode){
  if(mode == MOVE_STOP){
    digitalWrite(MOTOR_DIRECTION_1, MOVE_FORWARD);
    digitalWrite(MOTOR_DIRECTION_2, MOVE_FORWARD);
  	digitalWrite(MOTOR_DIRECTION_3, MOVE_FORWARD);
    digitalWrite(MOTOR_DIRECTION_4, MOVE_FORWARD);
    return;
  }
  if(mode == MOVE_FORWARD) {
    digitalWrite(MOTOR_DIRECTION_1, MOVE_FORWARD);
    digitalWrite(MOTOR_DIRECTION_2, MOVE_FORWARD);
    return;
  }
  // PORT ở mức thấp (0V/LOW) thì bánh xe sẽ được thiết lập tiến về trước

  digitalWrite(MOTOR_DIRECTION_1, MOVE_REVERSE);
  digitalWrite(MOTOR_DIRECTION_2, MOVE_REVERSE);
  // PORT ở mức cao (5V/HIGH) thì bánh xe sẽ được tiếp lập tiến về phía sau
}

// Hàm điều chỉnh hướng quay của bánh xe 
// hàm config
void motorRotateConfig(int mode){
  int motor13Direction = mode == ROTATE_RIGHT ? 5 : 0;
  int motor24Direction = mode == ROTATE_LEFT ? 5 : 0;
  // nếu như so sánh ở motor13 là TRUE và motor24 là FALSE thì chế độ bánh xe đang là hướng quay phải (RIGHT)
  digitalWrite(MOTOR_DIRECTION_1, motor13Direction);
  digitalWrite(MOTOR_DIRECTION_3, motor13Direction);
  
  digitalWrite(MOTOR_DIRECTION_2, motor24Direction);
  digitalWrite(MOTOR_DIRECTION_4, motor24Direction);
}

// Hàm dừng bánh xe, nhận 1 param là khoảng thời gian chờ 
// hàm phụ
// moveStop(timeInMs), 
// EXAMPLE: moveStop(2000);
// timeInMs = 2000 milisec
void moveStop(unsigned long motorWaitTimeInMs){
  motorDirectionConfig(MOVE_STOP);
  delay(100);
  
  analogWrite(MOTOR_DRIVE_1,0);
  analogWrite(MOTOR_DRIVE_2,0);
  analogWrite(MOTOR_DRIVE_3,0);
  analogWrite(MOTOR_DRIVE_4,0);
  
  delay(motorWaitTimeInMs);
}

// Hàm di chuyển về phía trước 
// hàm phụ
void moveForward(){
  int speed;
  int distanceRight;
  int distanceLeft;
  
  motorDirectionConfig(MOVE_FORWARD);
  delay(100);
  
  for(speed = 0; speed <= MAX_FORWARD_SPEED; speed+=5){
    
    analogWrite(MOTOR_DRIVE_1, speed);
  	analogWrite(MOTOR_DRIVE_2, speed);
    delay(20);
  }
}

// Hàm di chuyển về phía sau 
// hàm phụ
void moveReverse(){
  int speed;
  
  motorDirectionConfig(MOVE_REVERSE);
  delay(100);
  
  for(speed = 250; speed > MAX_REVERSE_SPEED; speed--){
    analogWrite(MOTOR_DRIVE_1, speed);
  	analogWrite(MOTOR_DRIVE_2, speed);
    delay(20);
  }
}

// Hàm thực thi việc quay bánh xe qua phải 
// hàm phụ
void motorRotateRight(){
  int timeToRotate;
  int speedForward = 100;
  int speedReverse = 150;
  
  motorRotateConfig(ROTATE_RIGHT);
  delay(100);
  
  for(timeToRotate = 0; timeToRotate < 100; timeToRotate++){
    analogWrite(MOTOR_DRIVE_2, speedForward);
    analogWrite(MOTOR_DRIVE_4, speedForward);
    
    analogWrite(MOTOR_DRIVE_1, speedReverse);
    analogWrite(MOTOR_DRIVE_3, speedReverse);
	delay(20);
  }
}

// Hàm thực thi việc quay bánh xe qua trái 
// hàm phụ
void motorRotateLeft(){
  int timeToRotate;
  int speedForward = 100;
  int speedReverse = 150;
  
  motorRotateConfig(ROTATE_LEFT);
  delay(100);
  
  for(timeToRotate = 0; timeToRotate < 100; timeToRotate++){
    analogWrite(MOTOR_DRIVE_1, speedForward);
    analogWrite(MOTOR_DRIVE_3, speedForward);
    
    analogWrite(MOTOR_DRIVE_2, speedReverse);
    analogWrite(MOTOR_DRIVE_4, speedReverse);
    delay(20);
  }
}

// Hàm hiển thị khoảng cách cảm biến,
// nhận 1 params là số PORT phát/nhận tín hiệu
// trả về 1 con số theo cm ở kiểu int 
// hàm phụ
int sensorDetectionRange(int portNumber){  
  sendSensorSignal(portNumber);
  
  int cm = receivedSensorSignal(portNumber);
  
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
long microSecToCenti(long cm){
  return cm / 29 / 2;
}