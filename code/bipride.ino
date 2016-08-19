#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 1
#define BUTTON 0
#define GNDPIN 2
#define NUM_LEDS 16
int modeCount = 0;
const byte numModes = 3;

long lastButtonCheck = 0;
const byte buttonDebounceTime = 200; //200 ms
bool firstUpdate = false;

byte buttonFlag;//this flag is used to communicate to the main loop that a new value was read.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Colors!
const uint32_t bi_blue = 255;// = Wheel(170);
const uint32_t bi_pink = 13762605;// = Wheel(240); 
const uint32_t bi_purple = 4522170;// = Wheel(193);

const uint32_t white = 16777215;// = strip.Color(255, 255, 255);
const uint32_t black = 0;

//Flags!
const uint32_t biFlag[NUM_LEDS] = {bi_pink, bi_pink, bi_pink, bi_pink, bi_purple, bi_purple, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_purple, bi_purple, bi_pink, bi_pink};
const uint32_t biChase[NUM_LEDS] = {bi_pink, bi_purple, bi_blue, black, black, black, black, black, bi_pink, bi_purple, bi_blue, black, black, black, black, black};

void setup() {
  strip.begin();
  strip.setBrightness(60);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON, INPUT);
  pinMode(GNDPIN, OUTPUT);
  digitalWrite(GNDPIN, LOW);
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
    biFlagDisplay();
  }
  else if (modeCount % numModes == 1) {
    biFlagRotate(200);
  }
  else if (modeCount % numModes == 2) {
    biColorChase(100);
  }
   

}

bool intDelay() {
  if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
    int buttonRead = digitalRead(BUTTON);
    lastButtonCheck = millis();
    if (buttonRead == HIGH) {
        buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
        return true; //return to the main loop to change the mode
      }
    }
}

/* BI PRIDE */

void biFlagDisplay() {
  uint8_t i;

  //uint32_t biFlag[NUM_LEDS] = {bi_pink, bi_pink, bi_pink, bi_pink, bi_pink, bi_pink, bi_purple, bi_purple, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_purple, bi_purple};

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, biFlag[i]);
  }
  strip.show();
}

void biFlagRotate(uint8_t wait) {
  uint8_t i;
  uint8_t j;
  
  //uint32_t biFlag[NUM_LEDS] = {bi_pink, bi_pink, bi_pink, bi_pink, bi_pink, bi_pink, bi_purple, bi_purple, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_blue, bi_purple, bi_purple};

  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, biFlag[(i+j) % NUM_LEDS]);
    }
    strip.show();
    //we need to check the button in here because of the delay 
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {    
//      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
//        int buttonRead = digitalRead(BUTTON);
//        lastButtonCheck = millis();
//        if (buttonRead == HIGH) {
//          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
//          return; //return to the main loop to change the mode
//        }
//      }
      if (intDelay()) {
        return;  
      }
    }
    //not using delays
//    delay(wait);
  }
}

void biColorChase(uint8_t wait) {
  uint8_t i;
  uint8_t j;
  
  //uint32_t biChase[NUM_LEDS] = {bi_pink, bi_purple, bi_blue, black, black, black, black, black, bi_pink, bi_purple, bi_blue, black, black, black, black, black};

  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, biChase[(i+j) % NUM_LEDS]);
    }
    strip.show();
        //we need to check the button in here because of the delay 
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {    
//      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
//        int buttonRead = digitalRead(BUTTON);
//        lastButtonCheck = millis();
//        if (buttonRead == HIGH) {
//          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
//          return; //return to the main loop to change the mode
//        }
//      }
      if (intDelay()) {
        return;  
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
