#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10
#define IN1             2
#define IN2             4
#define enA             3

#define led             5
#define touch           7

int UID[4], demID=0, demDongMo=1, trangThaiDongCo=0;
int trangthaiLedDau = LOW;
int demTouch=1;

int ID1[4] = {99, 251, 171, 252}; //Thẻ mở đèn
int ID2[4] = {185, 219, 971, 162}; //Thẻ tắt đèn

 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup(){
    Serial.begin(9600);   
    pinMode(led, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(led,OUTPUT);
    pinMode(touch,INPUT);
    Serial.print("UID của thẻ: ");
    SPI.begin();    
    mfrc522.PCD_Init();
}

void motor1_Tien(){
  analogWrite(enA, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motor1_Dung(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor1_Lui(){
  analogWrite(enA, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop(){
  if(!mfrc522.PICC_IsNewCardPresent()){ 
    return; 
  }
  if(!mfrc522.PICC_ReadCardSerial()){  
    return;  
  }   
//  Đọc thông tin của thẻ
  for (byte i = 0; i < mfrc522.uid.size; i++) { 
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
  }
//  So sánh giá trị thẻ đọc vào với thẻ cài đặt trước đó
  Serial.println("   ");
  for(int i=0;i<4;i++){
    if (UID[i] == ID1[i]){
      demID++;
    }
  }
//  Nếu 4 giá trị đều đúng thì tăng biến đóng mở lên 1
  if(demID==4){
    demDongMo++;
    demID=0;    
  }
  else{
    Serial.println("Sai the!"); 
  }

//  Thực hiện đóng mở cổng
  if(demDongMo%2 == 0 && trangThaiDongCo == 0){
    Serial.println("Mở cổng");
    motor1_Tien();
    delay(1000);
    trangThaiDongCo = 1;
    motor1_Dung();
    Serial.println("Done");
  }
  else if(demDongMo%2 != 0 && trangThaiDongCo == 1){
    Serial.println("Đóng cổng");
    motor1_Lui();
    delay(1000);
    trangThaiDongCo = 0;
    motor1_Dung();
    Serial.println("Done");
  }

  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();

}
