#define ledGarage         3
#define PIRGarage         2

#define ledStair          5
#define PIRStair          4

#define ledBedRoom        6
#define butLedBedRoom     7

#define butFanBedRoom     8

#define IN1               10
#define IN2               9
#define enA               11

int giaTriPIRGarage, giaTriPIRStair;

int trangthaiLedDau_BedRoom = LOW;
int demLed_BedRoom = 1;

int trangthaiFanDau_BedRoom = LOW;
int demFan_BedRoom = 1;

void setup(){
  pinMode(ledGarage, OUTPUT);
  pinMode(PIRGarage, INPUT);

  pinMode(ledStair, OUTPUT);
  pinMode(PIRStair, INPUT);

  pinMode(ledBedRoom, OUTPUT);
  pinMode(butLedBedRoom, INPUT);

  pinMode(butFanBedRoom, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(enA, OUTPUT);
    
  Serial.begin(9600);
}

void motorFan_Tien(){
  analogWrite(enA, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorFan_Dung(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop(){
  while(1){
//    Bật tắt bóng đèn Bed Room
    int trangthaiLedHienTai_BedRoom = digitalRead(butLedBedRoom);
    if(trangthaiLedHienTai_BedRoom == HIGH && trangthaiLedDau_BedRoom == LOW){
      demLed_BedRoom++;
    }
    trangthaiLedDau_BedRoom = trangthaiLedHienTai_BedRoom;
    if(demLed_BedRoom%2==0){
      digitalWrite(ledBedRoom,HIGH);
    }
    else{
      digitalWrite(ledBedRoom,LOW);
    }
    
//    Bật tắt quạt Bed Room
    int trangthaiFanHienTai_BedRoom = digitalRead(butFanBedRoom);
    Serial.println(trangthaiFanHienTai_BedRoom);
    if(trangthaiFanHienTai_BedRoom == HIGH && trangthaiFanDau_BedRoom == LOW){
      demFan_BedRoom++;
    }
    trangthaiFanDau_BedRoom = trangthaiFanHienTai_BedRoom;
    if(demFan_BedRoom%2==0){
      motorFan_Tien();
    }
    else{
      motorFan_Dung();
    }
  
    giaTriPIRGarage = digitalRead(PIRGarage);
    giaTriPIRStair = digitalRead(PIRStair);
    
//    Cảm biến chuyển động nhà kho
    if(giaTriPIRGarage == 1){
      digitalWrite(ledGarage, HIGH);
    }
    else{
      digitalWrite(ledGarage, LOW);
    }
//   Cảm biến chuyển động cầu thang
    if(giaTriPIRStair == 1){
      digitalWrite(ledStair, HIGH);
    }
    else{
      digitalWrite(ledStair, LOW);
    }
  }
}
