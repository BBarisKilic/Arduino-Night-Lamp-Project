#include <Arduino.h>
#include <SoftwareSerial.h>
//Add this external library to be able to use Neopixel LEDs.
//In Arduino IDE: Sketch -> Include Library -> Manage Libraries
//And search "Adafruit NeoPixel" then install library which provided by "Adafruit".
#include <Adafruit_NeoPixel.h>

//Pin connected to the NeoPixels.
#define PIN 6
//Number of NeoPixels attached to the Arduino.
#define NUMPIXELS 16
//Time (in milliseconds) to pause between pixels.
#define DELAYTIME 25

//RX, TX
SoftwareSerial BTSerial(2, 3);

//Variables for keep rgb color codes.
int red, green, blue;
int data;

// When setting up the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  //Starting software serial at 9600 Baudrate
  BTSerial.begin(9600);
  BTSerial.setTimeout(50);
  led.begin();
  led.show();
}

void loop()
{
  //Code executes only if there is any incoming data.
  while (BTSerial.available() > 0)
  {
    data = BTSerial.read();
    //If incoming data is "s", we are setting all pixels 'off'.
    if (data == 's')
    {
      //We are setting here all pixel colors to 'off'
      led.clear();
      led.show();
    }
    else
    {
      //Incoming data will be formatted as (R,G,B) from ArduBlu.
      //Since we know the format, it is easy to read and parse integer values.
      //The following 3 line just doing this.
      red = BTSerial.parseInt();
      green = BTSerial.parseInt();
      blue = BTSerial.parseInt();

      //When we see ")", we know that it is end of incoming data.
      if (BTSerial.read() == ')')
      {
        //We are applying here the new color for each Neopixels.
        for (int i = 0; i < NUMPIXELS; i++)
        {
          led.setPixelColor(i, led.Color(red, green, blue));
          led.show();
          delay(DELAYTIME);
        }
      }
    }
  }
}
