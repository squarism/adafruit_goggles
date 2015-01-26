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
  // Xmas Time!
  dotChase(strip.Color(127,   0,   0), 60, 2); // Red
  dotChase(strip.Color(0,   127,   0), 60, 2); // Green
}

// dot chase visual effect
void dotChase(uint32_t c, uint8_t wait, int cycles) {
  int offset = 5;  // pixel separation

  for (int j=0; j<cycles; j++) {
    for (int q=0; q < offset; q++) {
      for (int i=0; i < strip.numPixels(); i=i+offset) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }

      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+offset) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
