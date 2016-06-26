/*
 * LGBT Pride Necklace
 * by brightcolorfulflickers
 * June 2016
 *
 * github.com/brightcolorfulflickers
 * brightcolorfulflickers.tumblr.com
 * instagram.com/brightcolorfulflickers
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 1
#define BUTTON 0
#define GNDPIN 2
#define NUM_LEDS 16
int modeCount = 0;
const byte numModes = 4;

long lastButtonCheck = 0;
const long buttonDebounceTime = 200; //200 ms
bool firstUpdate = false;

byte buttonFlag;//this flag is used to communicate to the main loop that a new value was read.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t black;
uint32_t red;
uint32_t orange;
uint32_t yellow;
uint32_t green;
uint32_t blue;
uint32_t purple;

void setup() {
  strip.begin();
  strip.setBrightness(60);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON, INPUT);
  pinMode(GNDPIN, OUTPUT);
  digitalWrite(GNDPIN, LOW);

  //define colors
  black = strip.Color(0, 0, 0);
  red = strip.Color(255, 0, 0);
  orange = Wheel(10);
  yellow = strip.Color(255, 255, 0);
  green = strip.Color(0, 255, 0);
  blue = strip.Color(0, 0, 255);
  purple = Wheel(193);
}

void loop() {
  //if debounce time has passed, check button
  if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
    int buttonRead = digitalRead(BUTTON);
    if (buttonRead == HIGH) {
      buttonFlag = 1; //set the flag that tells the loop() that a button was pushed
    }
    lastButtonCheck = millis();
  }

  //if button has been pressed, update the display (or if it's never been set)
  if (buttonFlag == 1 || firstUpdate == false) {
    buttonFlag = 0; //clear button press
    if (firstUpdate == false) {
      firstUpdate = true; //the first update has occurred
    }
    else { // otherwise, increment mode counter as usual
      modeCount++;

    }


  }
  if (modeCount % numModes == 0) {
    rainbowFlagDisplay();
    //Serial.println("Display Flag");
  }
  else if (modeCount % numModes == 1) {
    rainbowFlagRotate(200);
  }
  else if (modeCount % numModes == 2) {
    rainbowColorChase(100);
  }
  else if (modeCount % numModes == 3) {
    rainbowCycle(40);
  }


}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();

    //we need to check the button in here because of the delay
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
        if (buttonRead == HIGH) {
          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed
          return; //return to the main loop to change the mode
        }
      }
    }
    //not using delays
    //delay(wait);
  }
}

void rainbowFlagDisplay() {
  uint16_t i;

  uint32_t rainbowFlag[NUM_LEDS] = {red, red, red, orange,orange, yellow, green, blue, purple, purple, purple, blue, blue, green, yellow, orange};

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, rainbowFlag[i]);
  }
  strip.show();
}

void rainbowFlagRotate(uint8_t wait) {
  uint16_t i;
  uint16_t j;

  uint32_t rainbowFlag[NUM_LEDS] = {red, red, red, orange,orange, yellow, green, blue, purple, purple, purple, blue, blue, green, yellow, orange};

  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, rainbowFlag[(i+j) % NUM_LEDS]);
    }
    strip.show();
    //we need to check the button in here because of the delay
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
        if (buttonRead == HIGH) {
          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed
          return; //return to the main loop to change the mode
        }
      }
    }
    //not using delays
//    delay(wait);
  }
}

void rainbowColorChase(uint8_t wait) {
  uint16_t i;
  uint16_t j;

  uint32_t rainbowChase[NUM_LEDS] = {red, orange, yellow, green, blue, purple, black, black, black, black, black, black, black, black, black, black};

  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, rainbowChase[(i+j) % NUM_LEDS]);
    }
    strip.show();
        //we need to check the button in here because of the delay
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
        if (buttonRead == HIGH) {
          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed
          return; //return to the main loop to change the mode
        }
      }
    }
    //not using delays
    //delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
