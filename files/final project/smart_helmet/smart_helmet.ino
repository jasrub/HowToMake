#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>


Adafruit_LSM303 lsm;

#define BRAKETHRESHOLD        350
#define BRAKETIMETHRESHOLD    200

#define TOUCHTHRESHOLD 100
#define TOUCH_DEBOUNCE 1000

#define PIXEL_PIN 10

#define PIXEL_COUNT 77

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )


const int cPin = 11;
const int dPin = 6;


// Set the first variable to the NUMBER of pixels. 32 = 32 pixels in a row
// The LED strips are 32 LEDs per meter but you can extend/cut the strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

CapacitiveSensor   left_touchpad = CapacitiveSensor(7, 6);       // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   right_touchpad = CapacitiveSensor(7, 8);       // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

int front_right[5][3] = {
  { 45, 45, 68},
  { 44, 61, 67 },
  { 43, 62, 66 },
  { 42, 63, 65 },
  { 64, 41, 64}
};
int back_right[5][3]  = {
  {24, 15, 3},
  {23, 16, 2 },
  {22, 17, 1 },
  {21, 18, 0 },
  {20, 19, 19}
};
int front_left[5][3] = {
  { 49, 72, 72},
  { 50, 56, 73 },
  { 51, 55, 74 },
  { 52, 54, 75 },
  { 53, 76, 76}
};
int back_left[5][3]  = {
  {26, 13, 5},
  {27, 12, 6 },
  {28, 11, 7 },
  {29, 10, 8 },
  {30, 9, 9}
};

bool left = false;
bool right = false;

int turnState = 0;
long turnWait = 200;
int turnAllLightsCounter = 0;
long turnMillis = 0;
int turnCounter = 0;
long lsm_time = 0;

int start = 0;

int prevX = 0;
int currentX = 0;

int cState = 0;
int dState = 0;

long brakeTime = 0;

long touchMillis = 0;

void setup()
{
  Serial.begin(9600);
  left_touchpad.set_CS_AutocaL_Millis(5000);
  right_touchpad.set_CS_AutocaL_Millis(5000);


  // Start up the LED strip
  strip.begin();
  strip.show();
  // blink rainbow color when turning strip on
  rainbow (1);
  hideAll();
  //strip.show();
  delay(1000);
  //Show regular lights
  normalLights();

  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  touchMillis = millis();
  lsm_time = millis();
}

void loop()
{
  check_switches();      // when we check the switches we'll get the current state
  
  if (millis() - lsm_time > 200) {
    lsm_time = millis();

    lsm.read();
    currentX = abs(lsm.accelData.x);
  
    if (start == 0) {
      prevX = currentX;
      start = 1;
    }
  
    int i = currentX - prevX;
  
    if (abs(i) > BRAKETHRESHOLD) {
      brakeTime = millis();
      int strikes = 0;
      while ((abs(i) > BRAKETHRESHOLD) && (strikes < 3)) {
        if (abs(i) < BRAKETHRESHOLD) {
          strikes = strikes + 1;
        }
        lsm.read();
        currentX = abs(lsm.accelData.x);
        i = currentX - prevX;
  
        if ((millis() - brakeTime) > BRAKETIMETHRESHOLD) {
          brakeLights();
          //brakeLights();
          while (abs(i) > BRAKETHRESHOLD) {
            lsm.read();
            currentX = abs(lsm.accelData.x);
            i = currentX - prevX;
           // Serial.println(i);
            delay(100);
          }
          //hideAll();
          brakeTime = millis();
          i = 0;
          lsm.read();
          currentX = abs(lsm.accelData.x);
        }
        else {
          normalLights();
        }
      }
    }
  
    prevX = currentX;
  }
}

void check_switches()
{
  long currTime = millis();
  long total_left =  left_touchpad.capacitiveSensor(30);
  long total_right =  right_touchpad.capacitiveSensor(30);
  Serial.print(total_left);                  // print sensor output 2
  Serial.print(" ");
  Serial.print(left);                  // print sensor output 2
  Serial.print("\t");
  Serial.print(total_right);                // print sensor output 3
  Serial.print(" ");
  Serial.println(right);                // print sensor output 3

  if (total_left > TOUCHTHRESHOLD && total_left>total_right) {
    if (currTime - touchMillis > TOUCH_DEBOUNCE) {
      normalLights();
      touchMillis = currTime;
      left = !left;
      right = false;
      turnState = 0;
      turnMillis = millis();
      turnCounter = 0;
    }
  }
  if (total_right > TOUCHTHRESHOLD) {
    if (currTime - touchMillis > TOUCH_DEBOUNCE && total_right>total_left) {
      normalLights();
      touchMillis = currTime;
      right = !right;
      left = false;
      turnState = 0;
      turnMillis = millis();
      turnCounter = 0;
    }
  }


  if (right) {
    long curMillis = millis();
    if (curMillis - turnMillis > turnWait) {
      turnMillis = curMillis;
      Serial.println(__LINE__);
      for (int i = 0; i < arr_len(front_right); i++) {
        for (int j = 0; j < arr_len(front_right[i]); j++) {
          strip.setPixelColor(front_right[i][j], strip.Color(237, 120, 6));
        }
      }
      for (int i = 0; i < arr_len(back_right); i++) {
        for (int j = 0; j < arr_len(back_right[i]); j++) {
          strip.setPixelColor(back_right[i][j], strip.Color(237, 120, 6));
        }
      }
      strip.show();

      for (int j = 0; j < arr_len(front_right[turnState]); j++) {
        strip.setPixelColor(front_right[turnState][j], strip.Color(0, 0, 0));

      }
      for (int j = 0; j < arr_len(back_right[turnState]); j++) {
        strip.setPixelColor(back_right[turnState][j], strip.Color(0, 0, 0));

      }
      strip.show();
      turnState++;
    }
    if (turnState == 5) {
      turnState = 0;
    }
  }
  else if (left) {
    long curMillis = millis();
    if (curMillis - turnMillis > turnWait) {
      turnMillis = curMillis;
      Serial.println(__LINE__);
      for (int i = 0; i < arr_len(front_left); i++) {
        for (int j = 0; j < arr_len(front_left[i]); j++) {
          strip.setPixelColor(front_left[i][j], strip.Color(237, 120, 6));
        }
      }
      for (int i = 0; i < arr_len(back_left); i++) {
        for (int j = 0; j < arr_len(back_left[i]); j++) {
          strip.setPixelColor(back_left[i][j], strip.Color(237, 120, 6));
        }
      }
      strip.show();

      for (int j = 0; j < arr_len(front_left[turnState]); j++) {
        strip.setPixelColor(front_left[turnState][j], strip.Color(0, 0, 0));

      }
      for (int j = 0; j < arr_len(back_left[turnState]); j++) {
        strip.setPixelColor(back_left[turnState][j], strip.Color(0, 0, 0));

      }
      strip.show();
      turnState++;
    }
    if (turnState == 5) {
      turnState = 0;
    }
    
  }
  else {
    normalLights();
  }

}


void brakeLights() {
  for (int i = 0; i < 41; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();

}

void hideAll() {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}


void normalLights() {
  uint16_t i;
  for (i = 0; i < 12; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  for (i = 17; i < 23; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  for (i = 17; i < 23; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  for (i = 28; i < 45; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  for (i = 50; i < 56; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  for (i = 62; i < 77; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  for (i = 12; i < 17; i++) {
    strip.setPixelColor(i, strip.Color(127, 0, 0));
  }
  for (i = 23; i < 28; i++) {
    strip.setPixelColor(i, strip.Color(127, 0, 0));
  }
  for (i = 45; i < 50; i++) {
    strip.setPixelColor(i, strip.Color(127, 127, 127));
  }
  for (i = 56; i < 62; i++) {
    strip.setPixelColor(i, strip.Color(127, 127, 127));
  }
  strip.show();

}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}




void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


