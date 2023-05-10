//  in USER_SETUP_ID 206 >  #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//  flash 16MB / ST7789  / 170 x 320 / 3,3 volt / 
// connector  GND , 3V , 43 , 44
// LILYGO T-DISPLAY S3
// ADC2 gaat niet samen met WIFI


#include <Arduino.h>
#include "GP2Y0E03.h"
#include <Wire.h>
#include "TFT_eSPI.h"
#include "pinoutS3.h" 

GP2Y0E03 meter(0x40) ;
float distance;

TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd); 


unsigned int teller = 0;
unsigned int counter = 0;
unsigned int minuten = 0;
unsigned int uren = 0;
unsigned int seconden = 0 , msec = 0 ;

#define adc_BATTERIJ  4  // 1/2 x Vsupp. = ± 3.3
#define BUTTON_LEFT   0 // BOOT BUTTON
#define BUTTON_RIGHT  14

void show_pinout(unsigned int tijdms )  {  lcd.setRotation(4); lcd.fillScreen(TFT_BLACK); lcd.pushImage( 0 , 0 , 170 , 320 , pinoutS3 ); delay(tijdms); }

unsigned long previousMillis = 0;  
const long interval = 100;   
String HS , MS, SSEc ;

void setup(void)
{   Wire.begin(43,44);
    pinMode(BUTTON_RIGHT,INPUT);
    pinMode(BUTTON_LEFT,INPUT);

    lcd.init();
    lcd.setSwapBytes(true);
    show_pinout(500);
    sprite.createSprite(320, 170); //  lcd.setRotation(1) / lcd.setRotation(3);
    sprite.setTextDatum(3);
    sprite.setSwapBytes(true);  // nr1 sprite actie 3
    sprite.setFreeFont();
 }

void loop()
{
  if(digitalRead(BUTTON_RIGHT)  ==0)  { show_pinout(2000); }
  if(digitalRead(BUTTON_LEFT)   ==0)  {       counter = 0 ; }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      lcd.setRotation(3); sprite.fillSprite(TFT_BLACK); sprite.setTextColor(TFT_GREENYELLOW);
        teller    = counter  ; 
        uren      = teller / 36000  ; teller = teller - ( uren  * 36000  );
        minuten   = teller / 600    ; teller = teller - ( minuten * 600  );
        seconden  = teller / 10     ; teller = teller - ( seconden * 10  );
        msec = teller ;
        if ( uren <10 )     {  HS = "0" + String(uren );     } else  {HS = String(uren );      }
        if ( minuten <10 )  {  MS = "0" + String(minuten );  } else  { MS = String(minuten );  }
        if ( seconden <10 ) {  SSEc = "0" + String(seconden ); } else  { SSEc = String(seconden );  }

      sprite.drawString(HS + ":" + MS + ":" + SSEc + "." + String(msec ), 30 , 85 , 7 );
      
      distance = meter.get_length();
      if (distance == -1) {  sprite.setTextColor(TFT_RED);   sprite.drawString("Meter buiten bereik" , 30 , 150 , 4 ); }
      else { sprite.setTextColor(TFT_CYAN);        sprite.drawString("afstand = " + String(distance ) + " cm", 30 , 150 , 4 ); }

      sprite.pushSprite(0,0);  // nr1 sprite actie 5
      counter += 1 ;
  }
} 


   
 
