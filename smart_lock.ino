#include <Servo.h>
#include <Keypad.h>

// keypad

const byte ROWS = 4; // 4 แถว
const byte COLS = 4; // 4 ตาราง
// 1 2 3 A
// 4 5 6 B
// 7 8 9 C
// * 0 # D
// ---------------------------------------------------------------------------------
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // สร้าง keypad จาก library

String currentKey = ""; // password ที่ใส่
Servo servo; // servo
bool saved = false; // เช็คว่า
void setup() {
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  servo.attach(3);
  digitalWrite(2, 0);
  Serial.begin(9600);
}

void loop() {
  if (currentKey.length() == 4) { // เช็คว่า password นั้นมี 4 หลักหรือยัง
    if (currentKey.equals("0000")) { // password ตรงกับที่ถูกหรือเปล่า
      Serial.println("ผ่าน"); // ขึ้นใน serial monitor ว่าผ่านแล้ว
      digitalWrite(4, 1); // ไฟเขียวขึ้น
      for (int i = 0; i<=180; i++) { // for loop ทำงาน 180 เพื่อให้หมุน 180 องศา
        servo.write(i); // หมุ่น ที่ละ 1 องศา
        delay(15); // รอ 0.015 วิเพื่อให้ servo ทำงานสำเร็จ
      }
      delay(5000); // รอ 5 วิเพื่อให้ล็อคเปิดได้และไม่ปิดทันที
      digitalWrite(4, 0); // ดับไฟ
      servo.write(0); // รีเซ็ทให้ servo กลับไปที่องศาเริ่มต้น
      currentKey = ""; // รีเซ็ท password ที่เก็บเอาไว้
    }else {
      digitalWrite(5, 1); // ไฟแดงขึ้น
      Serial.println("ไม่ผ่าน"); // ขึ้นใน serial monitor ว่าผิด
      digitalWrite(2, 1); // เสียง piezo สุดน่ารำคาญ
      delay(100);
      digitalWrite(2,0);
      delay(5000); // รอ 5 วิ เพื่อไม่ให้ลองรหัสได้ตลอดเวลา
      digitalWrite(5, 0); // ไฟดับ
      
      
      currentKey = ""; // รีเซ็ท password ที่เก็บเอาไว้
    }
  }
  char key = keypad.getKey(); // เอาปุ่มที่กด
  if (key) { // เช็คว่ามีปุ่มที่กดไหม
    currentKey = currentKey + String(key); // เพิ่มปุ่มที่กดเข้าสู่ตัวแปร
    Serial.println(currentKey); // แสดงตัวแปรใน serial monitor 
  }  
}
