//#define led 4
#define touch 7

#define IN1 2
#define IN2 4
#define enA 3

int trangthaiDau = LOW;

void setup() {
//  pinMode(led,OUTPUT);
  pinMode(touch,INPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(enA, OUTPUT);
  Serial.begin(9600);
}

void motor1_Tien(){
  analogWrite(enA, 80);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motor1_Dung(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor1_Lui(){
  analogWrite(enA, 80);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {

  int dem=1;
  int trangThaiMotor=0;

  while(1){
    int trangthaiHienTai = digitalRead(touch);
    if(trangthaiHienTai == HIGH && trangthaiDau == LOW){
      dem++;
    }
    trangthaiDau = trangthaiHienTai;
    if(dem%2==0 && trangThaiMotor == 0){
      motor1_Tien();
      delay(1000);
      trangThaiMotor = 1;
      motor1_Dung();
    }
    else if(dem%2 != 0 && trangThaiMotor == 1){
      motor1_Lui();
      delay(1000);
      trangThaiMotor = 0;
      motor1_Dung();
    }
  }
}
