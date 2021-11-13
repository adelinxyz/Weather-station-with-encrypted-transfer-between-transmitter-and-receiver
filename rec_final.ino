#include <aes.h>
#include <aes256_dec.h>
#include <aes256_enc.h>
#include <AESLib.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
RF24 myRadio (9, 10); 
byte addresses[][6] = {"0"}; 
char data[20];
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{
  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
      if ( myRadio.available()) 
      {
          while (myRadio.available())
          {
              myRadio.read( &data, sizeof(data) );
          }


          
         Serial.print("Encrypted data AES256 ");
          Serial.print("\n");
          for(int i=0;i<sizeof(data);i++){
          Serial.print(data[i]&0xFF,HEX);}
          Serial.print("\n");
          

               
         aes256_dec_single(key, data);
         Serial.print("Date senzor: ");
            for (int i=0; i<(sizeof(data)); i++) 
              {
                
                //lcd.setCursor(0, 0);
                String str=String (data[i]);
                Serial.print(str);
                   //lcd.setCursor(0, 0);
                 Serial.print(str);
                 //lcd.setCursor(16,0);
                 lcd.print(str);
                   //delay(700);
                //lcd.autoscroll();
               
              
              }
       lcd.setCursor(12, 1);       
     lcd.print("mmHg"); 
    Serial.print("\n");
    delay(8000);
  }
  lcd.clear();
}

 
