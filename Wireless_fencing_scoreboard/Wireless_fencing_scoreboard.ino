#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 4
#define DIO 5
#define p1 12
#define p2 13
#define buzzer 3
TM1637Display display(CLK, DIO);
RF24 radio(7, 8);
const byte addresses[][6] = {"00001", "00002","00003"};
int c1 = 0;
int c2 = 0;
int p1c = 0;
int p2c = 0;
int data;
const long intervalo = 2000;
long pm = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MAX);
  Serial.begin(9600);
  
}
void loop() {
  unsigned long cm = millis();
  long timeout = (cm) - (pm);
  display.setBrightness(5);
  display.clear();
  int p1cv = p1c/4;
  int p2cv = p2c/4;
  display.showNumberDec(p2cv, false, 4);
  display.showNumberDec(p1cv, false, 1);
  radio.startListening();
  while (!radio.available());
  radio.read(&data, sizeof(data));
  
  if (data == 0) {
    tone(buzzer, 500);
    digitalWrite(p2, HIGH);
    p2c = p2c +1;
    delay(100);
    noTone(buzzer);
    digitalWrite(p2, LOW);
  }
  
   if (data == 2) {
    tone(buzzer, 500);
    digitalWrite(p1, HIGH);
    p1c = p1c +1;
    delay(100);
    noTone(buzzer);
    digitalWrite(p1, LOW);
  }
  if (data == 8){
    p1c = p1c -1;  
  }
  if (data == 9){
    p1c = p1c +1;  
  }
  if (data == 6){
    p2c = p2c +1;  
  }
  if (data == 7){
    p2c = p2c -1;  
  }
  
  if(p1cv > 9){
    p1c = 0;
  }
  if(p2cv > 9){
    p2c = 0;
  }
  
  Serial.print(data);
  delay(1);
}
