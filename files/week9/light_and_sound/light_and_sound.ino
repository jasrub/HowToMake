#include "pitches.h"

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

int speakerPin = 5;	// speaker connected to digital pin 5 (PA5)
const int buttonPin = 8;  // Button connected to pin 8 (PB2)
 	 
int buttonState = 0;

// 19, 18, 17, 16
// 15, 14, 13, 12
// 11, 10,  9,  8
//  7,  6,  5,  4
//  3,  2,  1,  0


const int to[] =   {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
const int from[] = {1,2,3,4,0,2,3,4,0,1,3,4,0,1,2,4,0,1,2,3};

int arrow1[] = {0,4,8,12,16,5,9,13,10};
int arrow2[] = {1,5,9,13,17,6,10,14,11};
int arrow3[] = {2,6,10,14,18,7,11,15,8};
int arrow4[] = {3,7,11,15,19,9,4,8,12};

int heart[] = {8, 5, 9, 13,2,6,10,14,18,7,15,3,19};

 // notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


void setup() {
  pinMode( 0, INPUT );
  pinMode( 1, INPUT );
  pinMode( 2, INPUT );
  pinMode( 3, INPUT );
  pinMode( 4, INPUT );
  
  pinMode(speakerPin, OUTPUT);	// sets the speakerPin to be an output
  pinMode(buttonPin, INPUT);

}

void flash ( int ledNum, long time_delay) {
  pinMode( from[ledNum], OUTPUT );
  digitalWrite( from[ledNum], HIGH );

  pinMode( to[ledNum], OUTPUT );
  digitalWrite( to[ledNum], LOW );
  delayMicroseconds(time_delay);
  pinMode( from[ledNum], INPUT );
  pinMode( to[ledNum], INPUT );
}

void flashLeds (int lights[], int len, int number, long time_delay) {
  for (int x=0; x<number; ++x) {
    for (int i=0; i<len; ++i ) {
      flash (lights[i], time_delay);
    }
  }
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{	 
          int x;	 
          long delayAmount = (long)(1000000/frequencyInHertz);
          long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
          for (x=0;x<loopTime;x++)	 
          {	 
              digitalWrite(speakerPin,HIGH);
              delayMicroseconds(delayAmount);
              digitalWrite(speakerPin,LOW);
              delayMicroseconds(delayAmount);
          }	 
}

void beepWithLight (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds, int ledArr[], int arrLen)
{
  
          int x;	 
          long delayAmount = (long)(1000000/frequencyInHertz);
          long led_delay = delayAmount/arrLen-100;
          long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
          for (x=0;x<loopTime;x++)	 
          {	 
              digitalWrite(speakerPin,HIGH);
              flashLeds (ledArr, arrLen, 1, led_delay);
              //delayMicroseconds(delayAmount);
              digitalWrite(speakerPin,LOW);
              flashLeds (ledArr, arrLen, 1, led_delay);
              //delayMicroseconds(delayAmount);
          }
  
  
}


void loop() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < arr_len(melody); thisNote++) {
    // Create random leds array
      int arr_len = random(20);
      int arr[arr_len];
      for (int i=0; i<arr_len; ++i) {
        arr[i] = random(20);
        }

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    beepWithLight(speakerPin, melody[thisNote], noteDuration, arr, arr_len);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
   }
   
   // For flashing the arrow: comment out everthing but the following lines:
//   flashLeds (arrow1, arr_len(arrow1), 1000, 10);
//   flashLeds (arrow2, arr_len(arrow2), 1000, 10);
//   flashLeds (arrow3, arr_len(arrow3), 1000, 10);
//   flashLeds (arrow4, arr_len(arrow4), 1000, 10);
   
}
