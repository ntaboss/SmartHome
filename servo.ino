#include <Servo.h>   
int cam_bien_1=7;
int cam_bien_2=8;

//tạo 2 biến myservo1-2
Servo myservo1;
Servo myservo2; 


void setup() { 
  Serial.begin(9600);
  myservo1.attach(A6);
  myservo2.attach(A7);
} 
 
//void read_cam_bien_hong_ngoai(int cam_bien_thu_i)
//{
//  int cam_bien; 
//  Servo myservo;
//  if(cam_bien_thu_i==1)
//  {
//    cam_bien = cam_bien_1;
//    myservo = myservo1;
//  }
//  else if(cam_bien_thu_i==2)
//  {
//    cam_bien = cam_bien_2;
//    myservo = myservo2;
//  }
//  int gia_tri = digitalRead(cam_bien);
//  if(gia_tri==0)
//  {
//    myservo.write(-90);
//    delay(2000);
//    myservo.write(90);
//  }
//}
void loop() 
{
    myservo2.write(90);
    delay(2000);
    myservo2.write(-90);

    myservo1.write(90);
    delay(2000);
    myservo1.write(-90);
    
//  read_cam_bien_hong_ngoai(1);
//  read_cam_bien_hong_ngoai(2);
int gia_tri_2 = digitalRead(cam_bien_2);
int gia_tri_1 = digitalRead(cam_bien_1);

  if(gia_tri_2==0)
  {
    myservo2.write(90);
    delay(2000);
    myservo2.write(-90);
  }
  else if(gia_tri_1==0){
    myservo1.write(90);
    delay(2000);
    myservo1.write(-90);
  }
  
}
