#define led 4
#define touch 7

int trangthaiDau = LOW;
void setup() {
  pinMode(led,OUTPUT);
  pinMode(touch,INPUT);
  Serial.begin(9600);
  Serial.print("Gia tri Touch: ");
}

void loop() {

  int dem=1;
//  Serial.print(i);

  while(1){
    int trangthaiHienTai = digitalRead(touch);
    if(trangthaiHienTai == HIGH && trangthaiDau == LOW){
      dem++;
    }
    trangthaiDau = trangthaiHienTai;
    if(dem%2==0){
      digitalWrite(led,HIGH);
      delay(10);
    }
    else{
      digitalWrite(led,LOW);
      delay(10);
    }
  }
}
