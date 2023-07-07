/*4X4     Arduin0
 * 2  -     A0
 * 3  -     A1
 * 4  -     A2
 * 5  -     A3
 * 6  -     7
 * 7  -     6
 * 8  -     5
 * 9  -     4
 * 
 * 
 * Nạp code mở Serial Monitor, chọn No line ending, baud 9600.

*/
#include <Keypad.h>
#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // Khai báo thư viện LCD sử dụng I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng
//Servo myservo; //Tạo biến myServo của loại Servo

const byte ROWS = 4; 
const byte COLS = 4; 
char password[5];
char On_equip[]="1609"; // Mật khẩu mở cửa
char Off_equip[]="1221"; // Mật khẩu đóng cửa
int i = 0;
int dem=0;
//int servo = 10;
int led = 9;

char MatrixKey[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3}; //connect to the column pinouts of the keypad

Keypad Mykeys = Keypad( makeKeymap(MatrixKey), rowPins, colPins, ROWS, COLS); 
//====================================================================

void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
  lcd.init(); // Khởi tạo màn hình Màn hình
  lcd.backlight(); // Bật đèn màn hình Màn hình
  
//  myservo.attach(servo); 
//  myservo.write (0); 
  
// Hiện chữ E-FIGHT
  lcd.setCursor(4, 0); // Di chuyển con trỏ đến cột 4 và hàng 0
  lcd.print("E-FIGHT");
  delay(5000);
  lcd.clear();
  lcd.print(" Enter Password");
  Serial.println("Mat khau: ");
}
//===================================================================
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
    dem++;
 }
}
void loop(){
  enterKey();

  if(dem==4) {
    if(strcmp(password,On_equip)== 0 ){
        lcd.clear();
        lcd.print("    Correct!");
//        myservo.write(180); // Mở cửa!
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);
        lcd.clear();
        lcd.print("     Opened!");
        delay(1000);
        lcd.clear();
        lcd.print(" Enter Password");
        Serial.println(" Dung mat khau mo cua!"); 
      }
      
     else if(strcmp(password,Off_equip) == 0){
        lcd.clear();
//        myservo.write(0); // Đóng cửa 
        lcd.print("     Closed!");
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);
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
        digitalWrite(led,LOW);
     }
    i=0;
    dem=0;
   }
 }
