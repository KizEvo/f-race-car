#define inA1 6       // Định nghĩa chân in1 của động cơ A
#define inA2 7       // Định nghĩa chân in2 của động cơ A
#define inB1 8       // Định nghĩa chân in1 của động cơ B
#define inB2 9       // Định nghĩa chân in2 của động cơ B
#define linesens1 A0 // Định nghĩa chân cảm biến line 1
#define linesens2 A1 // Định nghĩa chân cảm biến line 2
#define linesens3 A2 // Định nghĩa chân cảm biến line 3
#define linesens4 A3 // Định nghĩa chân cảm biến line 4
#define linesens5 A4 // Định nghĩa chân cảm biến line 5
#define linesens6 A5 // Định nghĩa chân cảm biến line 6

#define MOTOR_FORWARD_SPEED 255
#define MOTOR_BACKWARD_SPEED 180

const int ECHO = 2;
const int TRIG = 4;
const int motorAspeed = 5;
const int motorBspeed = 3;

void setup()
{
  pinMode(inA1, OUTPUT);     // Set chân in1 của dc A là output
  pinMode(inA2, OUTPUT);     // Set chân in2 của dc A là output
  pinMode(inB1, OUTPUT);     // Set chân in1 của dc B là output
  pinMode(inB2, OUTPUT);     // Set chân in2 của dc B là output
  pinMode(linesens1, INPUT); // Set chân cảm biến 1 là input
  pinMode(linesens2, INPUT); // Set chân cảm biến 2 là input
  pinMode(linesens3, INPUT); // Set chân cảm biến 3 là input
  pinMode(linesens4, INPUT); // Set chân cảm biến 4 là input
  pinMode(linesens5, INPUT); // Set chân cảm biến 5 là input
  pinMode(linesens6, INPUT); // Set chân cảm biến 6 là input
  pinMode(motorAspeed, OUTPUT);
  pinMode(motorBspeed, OUTPUT);
}

// Hàm loop chính cho xe dò line
void loop()
{
  robotControl(inA1, inA2, inB1, inB2, linesens1, linesens2, linesens3, linesens4, linesens5, linesens6);
}

// robotControl()
// Hàm điều khiển hành động của robot.
// Nhận tham số là các chân OUTPUT của cảm biến hồng ngoại, động cơ trái và phải.
void robotControl(byte inR1, byte inR2, byte inL1, byte inL2, byte sen1, byte sen2, byte sen3, byte sen4, byte sen5, byte sen6)
{
  switch (sensorsControl(sen1, sen2, sen3, sen4, sen5, sen6))
  {
    case -1:
    case -2:
    case -3:
      motorsDirectionControl(inR1, inR2, inL1, inL2, 6); // rẽ trái
      setMotorSpeed(MOTOR_BACKWARD_SPEED);
      break;
    case 1:
    case 2:
    case 3:
      motorsDirectionControl(inR1, inR2, inL1, inL2, 5); // rẽ phải
      setMotorSpeed(MOTOR_BACKWARD_SPEED);
      break;
    case 0:
      motorsDirectionControl(inR1, inR2, inL1, inL2, 1); // tiến thẳng
      setMotorSpeed(MOTOR_FORWARD_SPEED);
      break;
    case 4:
      setMotorSpeed(MOTOR_BACKWARD_SPEED);
      for (int i = 0 ; i <= 20; i++)
      {
        delay(10);
        if (getIFSensorValue(sen1) != 0 || getIFSensorValue(sen2) != 0 || getIFSensorValue(sen3) != 0 || getIFSensorValue(sen4) != 0 || getIFSensorValue(sen5) != 0 || getIFSensorValue(sen6) != 0 )
        {
          break;
        }
      }
      while (getIFSensorValue(sen1) == 0 && getIFSensorValue(sen2) == 0 && getIFSensorValue(sen3) == 0 && getIFSensorValue(sen4) == 0 && getIFSensorValue(sen5) == 0 && getIFSensorValue(sen6) == 0)
      {
        motorsDirectionControl(inR1, inR2, inL1, inL2, 2); // lệch vạch thì lùi
      }
      break;
    case 5:
      motorsDirectionControl(inR1, inR2, inL1, inL2, 0); // đứng yên
      break;
  }
}

// setMotorSpeed()
// Hàm ghi tốc độ của động cơ
// Nhận tham số là giá trị tốc độ động cơ
void setMotorSpeed(byte motorSpeed)
{
  analogWrite(motorBspeed, motorSpeed);
  analogWrite(motorAspeed, motorSpeed);
}

// motorsDirectionControl()
// Hàm điều khiển hướng quay của động cơ
// Nhận tham số là các chân của động cơ
// inR1 inR2 là 2 chân tín hiệu động cơ bên phải
// inL1 inL2 là 2 chân tín hiệu động cơ bên trái
void motorsDirectionControl(byte inR1, byte inR2, byte inL1, byte inL2, byte action)
{
  switch (action)
  {
    case 0: // không di chuyển
      setMotorsDirection(inR1, inR2, 0);
      setMotorsDirection(inL1, inL2, 0);
      break;
    case 1: // đi thẳng
      setMotorsDirection(inR1, inR2, 1);
      setMotorsDirection(inL1, inL2, 1);
      break;
    case 2: // lùi lại
      setMotorsDirection(inR1, inR2, 2);
      setMotorsDirection(inL1, inL2, 2);
      break;
    case 3: // quay trái
      setMotorsDirection(inR1, inR2, 1);
      setMotorsDirection(inL1, inL2, 2);
      break;
    case 4: // quay phải
      setMotorsDirection(inR1, inR2, 2);
      setMotorsDirection(inL1, inL2, 1);
      break;
    case 5: // rẽ trái
      setMotorsDirection(inR1, inR2, 1);
      setMotorsDirection(inL1, inL2, 0);
      break;
    case 6: // rẽ phải
      setMotorsDirection(inR1, inR2, 0);
      setMotorsDirection(inL1, inL2, 1);
      break;
  }
}

// setMotorsDirection()
// Hàm ghi hướng quay của động cơ (thuận chiều kim đồng hộ, ngược chiều kim đồng hồ)
// Nhận tham số là các chân âm, dương của động cơ và cờ (action flags) xác định hướng quay
void setMotorsDirection(byte in1, byte in2, byte action)
{
  switch (action)
  {
    case 0: // Dừng không quay
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
    case 1: // Quay chiều thứ 1
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      break;
    case 2: // Quay chiều thứ 2
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      break;
  }
}

// getIFSensorValue()
// Hàm lấy giá trị cảm biến đọc được
// Trả về giá trị boolean
// Tham số là chân của cảm biến IR
boolean getIFSensorValue(byte PinNumb)
{
  if (analogRead(PinNumb) > 700)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// sensorsControl()
// Hàm điều khiển các cảm biến IR và cảm biến siêu âm
// Trả về các giá trị quyết định điều khiển cho hàm robotControl()
// Tham số là các chân cảm biến IR
int sensorsControl(int PinNumb1, int PinNumb2, int PinNumb3, int PinNumb4, int PinNumb5, int PinNumb6)
{
  int cm = getUltrasonicSensorRange(ECHO, TRIG);
  if (cm <= 20)
    return 5;

  int left = 0;  // biến kiểm tra lệch trái
  int right = 0; // biến kiểm tra lệch phải

  left = getIFSensorValue(PinNumb4) + getIFSensorValue(PinNumb5) + getIFSensorValue(PinNumb6);  // kiểm tra các cảm biến trái ở trong màu đen
  right = getIFSensorValue(PinNumb1) + getIFSensorValue(PinNumb2) + getIFSensorValue(PinNumb3); // kiểm tra các cảm biến phải ở trong màu đen

  if ((getIFSensorValue (PinNumb1) == 1) && ( getIFSensorValue (PinNumb6) == 1) && (( (getIFSensorValue (PinNumb3) + getIFSensorValue (PinNumb4)) == 0) || (getIFSensorValue (PinNumb3) == 0) || (getIFSensorValue (PinNumb4) == 0) || (getIFSensorValue (PinNumb2) == 0) || (getIFSensorValue (PinNumb5) == 0))) {
    return left - right;
  }
  else if ((left != 0) || (right != 0))
  {
    return right - left;
  }
  else
    return 4;
}

// getUltrasonicSensorRange()
// Hàm lấy giá trị của cảm biến siêu âm
// Trả về giá trị khoảng cách (cm) khi cảm biến hoạt động
// Tham số là các chân của cảm biến siêu âm
int getUltrasonicSensorRange(int ECHO, int TRIG)
{
  sendSensorSignal(TRIG);
  int cm = readSensorSignal(ECHO);
  return cm;
}

// sendSensorSignal()
// Hàm phát tín hiệu của cảm biến siêu âm
// Tham số là chân TRIG của cảm biến
void sendSensorSignal(int TRIG)
{
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);
}

// readSensorSignal()
// Hàm đọc giá trị của cảm biến siêu âm
// Tham số là chân ECHO của cảm biến
// Trả về giá trị khoảng cách ở cm
long readSensorSignal(int ECHO)
{
  long duration, cm;
  pinMode(ECHO, INPUT);
  duration = pulseIn(ECHO, HIGH);
  cm = microSecToCenti(duration);
  return cm;
}

// microSecToCenti()
// Hàm chuyển giá trị đọc được từ cảm biến sang cm
// Trả về giá trị khoảng cách ở cm
// Tham số là thời gian sóng phát tín hiệu đến khi nhận được của cảm biến
long microSecToCenti(long duration)
{
  return duration / 29 / 2;
}
