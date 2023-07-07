#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

int UID[4], dem1=0, dem2=0;

int ID1[4] = {99, 251, 171, 252}; //Thẻ mở đèn
int ID2[4] = {185, 219, 971, 162}; //Thẻ tắt đèn

int led = 8;
 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{
    Serial.begin(9600);   

    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);

    Serial.print("UID của thẻ: ");
    
    SPI.begin();    
    mfrc522.PCD_Init();

}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return; 
  }

  
  if ( ! mfrc522.PICC_ReadCardSerial()) {  
    return;  
  }   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) { 
//    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
  }

  Serial.println("   ");
  for(int i=0;i<4;i++){
    if (UID[i] == ID1[i]){
      dem1++;
    }
  }
  for(int i=0;i<4;i++){
    if (UID[i] == ID2[i]){
      dem2++;
    }
  }
  
  if(dem1==4 || dem2==4){
    digitalWrite(led, HIGH);
    Serial.println("Bật đèn");
    dem1=0;
    dem2=0;    
  }
  else{
    digitalWrite(led, LOW);
    Serial.println("Sai the!"); 
  }

  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();

}
