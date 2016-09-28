/*
 * Bi Pride Necklace
 * by brightcolorfulflickers
 * August 2016
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

unsigned long lastButtonCheck = 0;
const unsigned long buttonDebounceTime = 200; //200 ms
bool firstUpdate = false;

byte buttonFlag;//this flag is used to communicate to the main loop that a new value was read.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Colors!
const uint32_t pan_blue = 38505;// = Wheel(120);
const uint32_t pan_pink = 15728655;// = Wheel(250); 
const uint32_t pan_yellow = 9857280;// = Wheel(35);

const uint32_t white = 16777215;// = strip.Color(255, 255, 255);
const uint32_t black = 0;

//Flags!
const uint32_t panFlag[NUM_LEDS] = {pan_pink, pan_pink, pan_pink, pan_pink, pan_yellow, pan_yellow, pan_blue, pan_blue, pan_blue, pan_blue, pan_blue, pan_blue, pan_yellow, pan_yellow, pan_pink, pan_pink};
const uint32_t panChase[NUM_LEDS] = {pan_pink, pan_yellow, pan_blue, black, black, black, black, black, pan_pink, pan_yellow, pan_blue, black, black, black, black, black};

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
      //Debug -- See which mode you're in when you click
      uint32_t tempcolor;
      if (modeCount % numModes == 0) {
        tempcolor = strip.Color(255,0,0);
      }
      else if (modeCount % numModes == 1) {
        tempcolor = strip.Color(0,255,0);
      }
      else if (modeCount % numModes == 2) {
        tempcolor = strip.Color(0,0,255);
      }
      else if (modeCount % numModes == 3) {
        tempcolor = strip.Color(128,128,0);
      }
      for(uint8_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, tempcolor);
      }
      strip.show(); 
      delay(250);
    }
   
  }
  if (modeCount % numModes == 0) {
    FlagDisplay();
  }
  else if (modeCount % numModes == 1) {
    FlagRotate(200);
  }
  else if (modeCount % numModes == 2) {
    ColorChase(100);
  }
  else if (modeCount % numModes == 3) { //random mode!
    
    int randMode = random(numModes-1); // choose a random mode
    long randTime = random(3000, 15000); // keep for a random time from 3-15 seconds
    long startMode = millis();
    if (randMode == 0) {
      while ((unsigned long)(millis() - startMode) < randTime) {   
        FlagDisplay(); 
        if (intDelay()) {
          return;  
        }
      }
    }
    else if (randMode == 1) {
      while ((unsigned long)(millis() - startMode) < randTime) {   
        FlagRotate(200); 
        if (buttonFlag == 1) {
          return;
        }
      }       
    }
    else if (randMode == 2) {
      while ((unsigned long)(millis() - startMode) < randTime) {   
        ColorChase(100);
        if (buttonFlag == 1) {
          return;
        }
      }         

    }
  }
  
}

// This function appears to have stopped working. Unclear why.
bool intDelay() {
  if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
    int buttonRead = digitalRead(BUTTON);
    lastButtonCheck = millis();
    if (buttonRead == HIGH) {
        buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
        return true; //return to the main loop to change the mode
      }
    else {
      return false;
    }
  }
}

/* PAN PRIDE */

void FlagDisplay() {
  uint8_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, panFlag[i]);
  }
  strip.show();
}

void FlagRotate(uint8_t wait) {
  uint8_t i;
  uint8_t j;
  
  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, panFlag[(i+j) % NUM_LEDS]);
    }
    strip.show();
    //we need to check the button in here because of the delay 
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {    
//      if (intDelay()) {
//        return;  
//      }
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
        if (buttonRead == HIGH) {
          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
          return; //return to the main loop to change the mode
        }
      }
    }
  }
}

void ColorChase(uint8_t wait) {
  uint8_t i;
  uint8_t j;
  
  for (j=0; j<strip.numPixels(); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, panChase[(i+j) % NUM_LEDS]);
    }
    strip.show();
        //we need to check the button in here because of the delay 
    long startWait = millis();
    while ((unsigned long)(millis() - startWait) < wait) {    
//      if (intDelay()) {
//        return;  
//      }
      if ((unsigned long)(millis() - lastButtonCheck) > buttonDebounceTime) {
        int buttonRead = digitalRead(BUTTON);
        lastButtonCheck = millis();
        if (buttonRead == HIGH) {
          buttonFlag = 1; //set the flag that tells the loop() that a button was pushed 
          return; //return to the main loop to change the mode
        }
      }
    }
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
