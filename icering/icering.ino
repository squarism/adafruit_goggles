#include <Adafruit_NeoPixel.h>

// ---- CHANGE THIS ----
#define PIN 4
#define LEDS 24


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  iceRing(500);
}

void iceRing(uint16_t wait) {
  uint16_t i, j;
  int start = 170;  // a pure red
  int end = 205;   // the led starts to blink purple

  // some random values each rotation
  int r_brightness = random(10) + 5;
  int g_brightness = random(35) + 5;


  // first cycle
  for(j=start; j<end; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(j & 255));
    }
    strip.show();
    delay(wait);
  }

  for(j=end; j>start; j--) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(j & 255));
    }
    strip.show();
    delay(wait);
  }

  int overdrive = 25;
  for(j=(start + overdrive); j < (end + overdrive); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      i++;
      strip.setPixelColor(i, Wheel(j & 255));
    }
  }

  for(j=(end + overdrive); j>(start + overdrive); j--) {
    for(i=0; i<strip.numPixels(); i++) {
      i++;
      strip.setPixelColor(i, Wheel(j & 255));
    }
  }

  // transition
  for(uint16_t blue = start; blue > 10; blue--) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(
        min(0, r_brightness - (start - blue)),
        min(0, g_brightness - (start - blue)),
        blue)
      );
    }
    strip.show();
    delay(wait);
  }

  for(uint16_t blue = 10; blue < start; blue++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, r_brightness, blue));
    }
    strip.show();
    delay(wait);
  }

  for(j=r_brightness; j>0; j--) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, j, start));
    }
    strip.show();
    delay(wait);
  }

}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

