#include <Wire.h>
#include <RTClib.h>

// Định nghĩa các chân LED
const int redLight = 2;
const int yellowLight = 3;
const int greenLight = 4;

// Định nghĩa chân cảm biến ánh sáng
const int lightSensorPin = A0;
int lightThreshold = 500; // Ngưỡng ánh sáng để kích hoạt

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Cài đặt thời gian nếu cần
  }

  // Cài đặt các chân đầu ra cho LED
  pinMode(redLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(greenLight, OUTPUT);

  // Cài đặt chân đầu vào cho cảm biến ánh sáng
  pinMode(lightSensorPin, INPUT);
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);

   if (Serial.available() > 0) {
    int command = Serial.read() - '0';

    if (command == 1) {
      controlTrafficLight(30, 2, 30);
    } else if (command == 2) {
      controlTrafficLight(20, 1, 15);
    }
  }
  DateTime now = rtc.now();

  // In giá trị ánh sáng và thời gian với dấu phẩy ở giữa
  Serial.print(lightLevel);
  Serial.print(", ");  // Thêm dấu phẩy giữa giá trị ánh sáng và thời gian
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1000);
}

void controlTrafficLight(int redDuration, int yellowDuration, int greenDuration) {
  digitalWrite(redLight, HIGH);
  digitalWrite(yellowLight, LOW);
  digitalWrite(greenLight, LOW);
  delay(redDuration * 1000);

  digitalWrite(redLight, LOW);
  digitalWrite(yellowLight, HIGH);
  digitalWrite(greenLight, LOW);
  delay(yellowDuration * 1000);

  digitalWrite(redLight, LOW);
  digitalWrite(yellowLight, LOW);
  digitalWrite(greenLight, HIGH);
  delay(greenDuration * 1000);

  digitalWrite(redLight, LOW);
  digitalWrite(yellowLight, LOW);
  digitalWrite(greenLight, LOW);
}
