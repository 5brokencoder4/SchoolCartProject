#include <SPI.h>
#include <MFRC522.h>
#define buzzer 7
#define led 8
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#include <SoftwareSerial.h>
SoftwareSerial melih(2, 3); // RX,TX
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 6 // DHT11PIN olarak Dijital 2'yi belirliyoruz.
dht11 DHT11;
#include <EEPROM.h>

void setup() 
{
  Serial.begin(38400);   // Initiate a serial communication
  melih.begin(38400);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
}
void loop() 
{
  int chk = DHT11.read(DHT11PIN);
  //Serial.println((float)DHT11.temperature, 2);
  melih.println((float)DHT11.temperature, 2);
  delay(1100);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if(content.substring(1) == "27 69 4C 79"){
  //while(content.substring(1) == "27 69 4C 79") //change here the UID of the card/cards that you want to give access
 // {
     digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(400);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    melih.println(6);
    delay(3000);
 //   break;
 // }
  }
  else{
 //  while(content.substring(1) == "84 77 6C 1E") //change here the UID of the card/cards that you want to give access
//  {
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(400);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    melih.println(2);
    delay(3000);
  //  break;
  }
 // }
} 
