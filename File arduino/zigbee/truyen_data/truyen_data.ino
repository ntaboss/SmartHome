

/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 18 (connect to TX of other device)
 * TX is digital pin 19 (connect to RX of other device)

 */
#include <SoftwareSerial.h>


SoftwareSerial ZigbeeSerial(18, 19); // RX, TX

#define sensor 4

void setup(){
  Serial.begin(115200);
  ZigbeeSerial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop() {
    // Nhận dữ liệu từ CC2530
  if (ZigbeeSerial.available()) {
    String receivedData = ZigbeeSerial.readString();
//    Serial.print("Received from CC2530: ");
//    Serial.println(receivedData);
  }
  
  // Gửi dữ liệu từ ESP32 đến CC2530
  if(digitalRead(sensor) == 1){
    ZigbeeSerial.println("BatDen-");
  }
  else{
    ZigbeeSerial.println("TatDen-");
  }
  delay(1000);
}
