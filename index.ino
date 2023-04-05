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

#define MAX_FORWARD_SPEED 250
#define MAX_REVERSE_SPEED 10

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
  moveReverse();
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
    digitalWrite(MOTOR_DIRECTION_3, MOVE_FORWARD);
    digitalWrite(MOTOR_DIRECTION_4, MOVE_FORWARD);
    return;
  }
  // PORT ở mức thấp (0V/LOW) thì bánh xe sẽ được thiết lập tiến về trước

  digitalWrite(MOTOR_DIRECTION_1, MOVE_REVERSE);
  digitalWrite(MOTOR_DIRECTION_2, MOVE_REVERSE);
  digitalWrite(MOTOR_DIRECTION_3, MOVE_REVERSE);
  digitalWrite(MOTOR_DIRECTION_4, MOVE_REVERSE);
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
  motorDirectionConfig(MOVE_FORWARD);
  delay(100);
  
  digitalWrite(MOTOR_DRIVE_1, MAX_FORWARD_SPEED);
  digitalWrite(MOTOR_DRIVE_2, MAX_FORWARD_SPEED);
  digitalWrite(MOTOR_DRIVE_3, MAX_FORWARD_SPEED);
  digitalWrite(MOTOR_DRIVE_4, MAX_FORWARD_SPEED);
}

// Hàm di chuyển về phía sau 
// hàm phụ
void moveReverse(){
  motorDirectionConfig(MOVE_REVERSE);
  delay(100);
  
  analogWrite(MOTOR_DRIVE_1, MAX_REVERSE_SPEED);
  analogWrite(MOTOR_DRIVE_2, MAX_REVERSE_SPEED);
  analogWrite(MOTOR_DRIVE_3, MAX_REVERSE_SPEED);
  analogWrite(MOTOR_DRIVE_4, MAX_REVERSE_SPEED);
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
