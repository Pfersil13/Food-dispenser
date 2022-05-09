#include "Light.h"

 
//the Wemos WS2812B RGB shield has 1 LED connected to pin 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, LEDS, NEO_GRB + NEO_KHZ800);
 
 ///////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////
void setupNeopixel() 
{
  pixels.begin(); // This initializes the NeoPixel library.
}
 

///////////////////////////////////////////////////////////////
//Simple function which takes values for the red, green and blue led and also
///////////////////////////////////////////////////////////////
void setColor(int led, int redValue, int greenValue, int blueValue)
{
  pixels.setPixelColor(led, pixels.Color(redValue, greenValue, blueValue)); 
  pixels.setBrightness(50);
  pixels.show();
  ;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void setLeds(int porcenaje){
  int  nLeds = (porcenaje * 7/100);
  pixels.clear();
  switch (nLeds)
  {
  case 7:
        pixels.setBrightness(100);
        setColor(7, 0,255, 0);
        setColor(6, 0,255, 0);
        setColor(5, 0,255, 0);
        setColor(4, 0,255, 0);
        setColor(3, 0,255, 0);
        setColor(2, 0,255, 0);
        setColor(1, 0,255, 0);
        setColor(0, 0,255, 0);
      break;

    case 6:
        setColor(6, 0,230, 0);
        setColor(5, 0,230, 0);
        setColor(4, 0,230, 0);
        setColor(3, 0,230, 0);
        setColor(2, 0,230, 0);
        setColor(1, 0,230, 0);
        setColor(0, 0,230, 0);
      break;

    case 5:
        setColor(5, 20,200, 0);
        setColor(4, 20,200, 0);
        setColor(3, 20,200, 0);
        setColor(2, 20,200, 0);
        setColor(1, 20,200, 0);
        setColor(0, 20,200, 0);
      break;
    
    case 4:
        
        setColor(4, 120,255, 0);
        setColor(3, 120,255, 0);
        setColor(2, 120,255, 0);
        setColor(1, 120,255, 0);
        setColor(0, 120,255, 0);
      break;
    
    case 3:
        setColor(3, 120,200, 0);
        setColor(2, 120,200, 0);
        setColor(1, 120,200, 0);
        setColor(0, 120,200, 0);
      break;
    
    case 2:
        setColor(2, 200,100, 0);
        setColor(1, 200,100, 0);
        setColor(0, 200,100, 0);
      break;
    case 1:
        setColor(1, 255,100, 0);
        setColor(0, 255,100, 0);
      break;
    case 0:
        setColor(0, 255,0, 0);
      break;
  default:
      break;
  }
 
}