/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define ledPin 13
#define button A1
int data;
RF24 radio(8, 7); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

boolean buttonState = 0;
void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
}
void loop() {
    radio.stopListening();
    buttonState = digitalRead(button);
    if (buttonState == LOW){
         data = 0;
         for(int i=0; i<10; i++){
         radio.write(&data, sizeof(data));
         }
         delay(2000);
    }
    delay(1);
  }
