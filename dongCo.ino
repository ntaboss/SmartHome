#define IN1 2
#define IN2 4
#define enA 3

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(enA, OUTPUT);
}

void motor1_Tien(){
  analogWrite(enA, 70);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motor1_Dung(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor1_Lui(){
  analogWrite(enA, 70);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop(){
  motor1_Tien();
  delay(5000);
  
  motor1_Dung();
  delay(3000);

  motor1_Lui();
  delay(5000);

  motor1_Dung();
}
