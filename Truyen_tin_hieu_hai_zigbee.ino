//Nhận tín hiệu

#include<SoftwareSerial.h>
SoftwareSerial mySerial(9,10);

#define led 8

void setup() {
mySerial.begin(115200);
pinMode(led, OUTPUT);
}

void loop() {
  //Đọc dữ liệu nhạn được từ chân Rx
  if(mySerial.available()){
    String RxBuffer = mySerial.readString();  
    if(RxBuffer == "ledOn"){
      digitalWrite(led, HIGH);    
    }
    else if(RxBuffer == "ledOff"){
      digitalWrite(led,LOW);
    }
  }
}
