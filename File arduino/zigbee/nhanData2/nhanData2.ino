
/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
 */
 
#include <SoftwareSerial.h>
#include <String.h>

#define led 4

int trangThai;
SoftwareSerial ZigbeeSerial(2, 3);  // RX: D2, TX: D3

void setup() {
  Serial.begin(115200);            // UART cho Serial Monitor
  ZigbeeSerial.begin(9600);      // Baud rate cho CC2530
  pinMode(led, OUTPUT);
}

void loop() {
  // Nhận dữ liệu từ CC2530
  if (ZigbeeSerial.available()) {
    String receivedData = ZigbeeSerial.readStringUntil('-');
    receivedData.trim();
//    Serial.print("Received from CC2530: ");
    Serial.println(receivedData);
    
    if(receivedData == "BatDen"){
      trangThai = 1;
      digitalWrite(led, HIGH);
    }
    else if(receivedData == "TatDen"){
      trangThai = 0;
      digitalWrite(led, LOW);
    }
    Serial.println(trangThai);
    delay(1000);
  }
}
