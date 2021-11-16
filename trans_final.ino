#include <aes.h>
#include <aes256_dec.h>
#include <aes256_enc.h>
#include <AESLib.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <AESLib.h>

#include <Wire.h>
#include "Adafruit_BMP280.h"
Adafruit_BMP280 bmp;
RF24 myRadio (9, 10);
byte addresses[][6] = {"0"};
const int chipSelect = 6;
char data[40];
String str;

void setup()
{
  bmp.begin();  
  Serial.begin(9600);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
   

void loop()
{ 

int nr = 0;
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};   
  
  str = bmp.readTemperature();
    for(int i = 0 ; i< sizeof(str); i++){
    data[nr++] = str[i];
  }
  
  str = "C," ;
  str = str + bmp.readAltitude();

    for(int i = 0 ; i< sizeof(str); i++){
    data[nr++] = str[i];
  }
  
  str = "m,";
  str = str + (bmp.readPressure()/101.325)*0.760;
  str=str+ "mmHg";
 
    for(int i = 0 ; i< sizeof(str); i++){
    data[nr++] = str[i];
  }
  
  aes256_enc_single(key, data);
  myRadio.write(&data, sizeof(data)); 

  String str_data = "";
  str_data = bmp.readTemperature();
  str_data = str_data + "C,";
  str_data = str_data + bmp.readAltitude();
  str_data = str_data + "m,";
  str_data = str_data + (bmp.readPressure()/101.325)*0.760;
  str_data = str_data + "mmHg";
  
  Serial.println(str_data);        
  delay(3000);

}
