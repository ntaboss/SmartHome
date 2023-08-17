/* Nối chân
 * 4X4     Arduino Chân từ trái sang phải
 * 2  -     A0
 * 3  -     A1
 * 4  -     A2
 * 5  -     A3
 * 6  -     8
 * 7  -     7
 * 8  -     6
 * 9  -     5
 * 
 * 
 * Servo: A6,A7
 * LCD: SDA(A4), SCL(A5) 
 * Motor: IN1(D2), IN2(D4), enA(D3) 
 * RFID: RST(9), SDA(10), MOSI(11), MISO(12), SCK(13)
*/

//********************************************************************************************
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // Khai báo thư viện LCD sử dụng I2C

#define RST_PIN         9
#define SS_PIN          10
#define IN1             2
#define IN2             4
#define enA             3

//#define led             A4
//#define touch           A5

//********************************************************************************************

int UID[4], demID=0, demDongMo=1, trangThaiDongCo=0;
int trangthaiLedDau = LOW;
int demTouch=1;

int ID1[4] = {99, 251, 171, 252}; //Thẻ mở đèn
int ID2[4] = {185, 219, 971, 162}; //Thẻ tắt đèn

const byte ROWS = 4; 
const byte COLS = 4; 
char password[5];
char On_equip[]="1609"; // Mật khẩu mở cửa
char Off_equip[]="1221"; // Mật khẩu đóng cửa
int i = 0;
int demMK=0;
char MatrixKey[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3}; //connect to the column pinouts of the keypad

Servo myservo1;
Servo myservo2;
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng
Keypad Mykeys = Keypad( makeKeymap(MatrixKey), rowPins, colPins, ROWS, COLS);

//********************************************************************************************

void setup(){
    Serial.begin(9600);   
//  pinMode(led, OUTPUT);
//  pinMode(touch,INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(enA, OUTPUT);
    
    lcd.init(); // Khởi tạo màn hình Màn hình
    lcd.backlight(); // Bật đèn màn hình Màn hình
    
    myservo1.attach(A6);
    myservo2.attach(A7);

    Serial.print("UID của thẻ: ");
    SPI.begin();
    // Hiện chữ E-FIGHT
    lcd.setCursor(4, 0); // Di chuyển con trỏ đến cột 4 và hàng 0
    lcd.print("E-FIGHT");
    delay(5000);
    lcd.clear();
    lcd.print(" Enter Password");
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

//Hàm nhập mật khẩu từ keypad
void enterKey(){
  char EnterKey = Mykeys.getKey();
    
  if(EnterKey){     //đợi tín hiệu nhập vào
    // Nhập mật khẩu
    if (i == 0) {
      password[0] = EnterKey;
      lcd.setCursor(6, 1);
      lcd.print(password[0]);
      delay(500); // Ký tự hiển thị trên màn hình LCD trong 0.5s
      lcd.setCursor(6, 1);
      lcd.print("*"); // Ký tự được thay bởi dấu *
      Serial.print(password[0]);
    }
    if (i == 1) {
      password[1] = EnterKey;
      lcd.setCursor(7, 1);
      lcd.print(password[1]);
      delay(500);
      lcd.setCursor(7, 1);
      lcd.print("*");
      Serial.print(password[1]);
    }
    if (i == 2) {
      password[2] = EnterKey;
      lcd.setCursor(8, 1);
      lcd.print(password[2]);
      delay(500);
      lcd.setCursor(8, 1);
      lcd.print("*");
      Serial.print(password[2]);
    }
    if (i == 3) {
      password[3] = EnterKey;
      lcd.setCursor(9, 1);
      lcd.print(password[3]);
      delay(500);
      lcd.setCursor(9, 1);
      lcd.print("*");
      Serial.println(password[3]);
    }
    i++;
    demMK++;
 }
}
//********************************************************************************************
void loop(){
  while(1){
    enterKey();

    if(demMK==4) {
      if(strcmp(password,On_equip)== 0 ){
          lcd.clear();
          lcd.print("    Correct!");
          myservo1.write(180);      //Mở cửa
          myservo2.write(-180);
          lcd.clear();
          lcd.print("     Opened!");
          delay(1000);
          lcd.clear();
          lcd.print(" Enter Password");
          Serial.println(" Dung mat khau mo cua!"); 
        }
        
       else if(strcmp(password,Off_equip) == 0){
          lcd.clear();
          lcd.print("     Closed!");
          myservo1.write(-180);       //Đóng cửa
          myservo2.write(180);
          lcd.clear();
          lcd.print(" Enter Password");
        }
        
        else{
          lcd.clear();
          lcd.print("   Incorrect!");
          delay(1000);
          lcd.clear();
          lcd.print("   Try Again!");
          delay(1000);
          lcd.clear();
          lcd.print(" Enter Password");
          Serial.println(" Sai mat khau nhap lai.............");
       }
      i=0;
      demMK=0;
    }
      
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
}
