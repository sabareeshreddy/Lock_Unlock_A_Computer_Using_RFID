#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

uint8_t buf[8] = {
0 }; /* Keyboard report buffer */

int cardCount = 0; 
void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  delay(200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
 

}
void loop(){
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
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "E6 F4 94 F4" , "B3 C9 2C 83" , "F3 68 47 0C" , "43 55 51 0C" , "06 7D 4A F6" , "06 E8 5B F6" ) //change here the UID of the card/cards that you want to give access
  {
     delay(50);

buf[0] = 0;
buf[2] = 0xE3; // Win Key
buf[3] = 0x0F; // letter L
Serial.write(buf, 8);
releaseKey();

delay(200);

buf[0] = 0;
buf[2] = 0x04; // letter A
Serial.write(buf, 8);
releaseKey();

delay(50);

buf[0] = 0;
buf[2] = 0x05; // letter B
Serial.write(buf, 8);
releaseKey();

delay(50);

buf[0] = 0;
buf[2] = 0x06; // letter C
Serial.write(buf, 8);
releaseKey();

delay(50);

buf[0] = 0;
buf[2] = 0x07; // letter D
Serial.write(buf, 8);
releaseKey();

cardCount++;
  
  }
 
 else   {
  return;
     }

     if(cardCount= 1  ){
      delay(50);


buf[0] = 0;
buf[2] = 0x28; // letter Enter
Serial.write(buf, 8);
releaseKey();

cardCount--;
      }
  }

void releaseKey()
{
buf[0] = 0;
buf[2] = 0;
buf[3] = 0;
Serial.write(buf, 8); // Release key
}
