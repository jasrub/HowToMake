 #include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

#define DOT_DURATION   700               // Duration of a Morse Code "dot" (in milliseconds)
#define DASH_DURATION  DOT_DURATION * 3  // Duration of a Morse Code "dash" (in milliseconds)
#define SIGNAL_GAP     DOT_DURATION      // Gap between dots/dashes of a single letter (in ms)
#define LETTER_GAP     DOT_DURATION * 3  // Gap between two letters (in milliseconds)
#define WORD_GAP       DOT_DURATION * 7  // Gap between two words (in milliseconds)

#define LED            7                // The digital connector port to LED anode
#define BUTTON         3                // The diginal connector port to the button

boolean buttonWasPressed = false;        // Indicator of whether button was pressed in the last cycle
long lastTimestamp = 0;                  // Last recorded timestamp  (used for mesuring duration)
int inputSignal;                         // Input signal buffer

void setup() {
  pinMode(LED, OUTPUT);                  // Set the LED output
  pinMode(BUTTON, INPUT);                // Set the button input
  digitalWrite(LED, LOW);                // Turn off the LED
  mySerial.begin(9600);   // Init the serial port
  inputSignal=1;
}

char* letters = "ETIANMSURWDKGOHVF-L?PJBXCYZQ.?54?3???2??+????16=/?????7???8?90?";

int getIndex(char c)
{
    char* ptr;
    int index;
    if (c==' ') {
      index = -2; //special index for blinking space
      return index;
    }

    if (97 <= c && c <= 122) { // if a-z
      c -= 32; // map to A-Z
    }

    ptr = strchr(letters, c);
    if (ptr == NULL)
    {
       // mySerial.println("Character not found \n");
        index = -1;
    }
    else {
      index = ptr - letters;
    }
    return index;
}

void blinkLetter(int index)
{
  if (index==-1) {
    return;
  }
  if (index==-2) { //in case this is a space
    delay(WORD_GAP);
  }
  else {
    char s[9];
    itoa(index+2, s, 2);
    for (int i = 1; s[i] != '\0'; i++){
      mySerial.print(s[i]);
      if (s[i]=='1') {
        showLightForDuration(DASH_DURATION);
      }
      else {
        showLightForDuration(DOT_DURATION);
      }
      delay(SIGNAL_GAP);
    }
    mySerial.println();
    delay(LETTER_GAP);
  }
}

// turn on the LED for the specified duration in milliseconds
void showLightForDuration(long duration) {
  digitalWrite(LED, HIGH);
  delay(duration);
  digitalWrite(LED, LOW);
}  
  
void loop() {
  long currentTimestamp  = millis(); // get the current timestamp
  long duration = currentTimestamp - lastTimestamp; // get elapsed time
  if (digitalRead(BUTTON) == HIGH) { // if the button is pressed
    //digitalWrite(LED, HIGH); // turn on the LED  
    if (!buttonWasPressed) { //  if the button was previously not pressed
      buttonWasPressed = true; // remember the button press
      digitalWrite(LED, HIGH); // turn on the LED
      lastTimestamp = currentTimestamp; // record the time of the button press
      if (duration > LETTER_GAP) {
        mySerial.print(' ');
      }
    } // end of if (button was not pressed)
  } else { // the button is not pressed
    if (buttonWasPressed) {  // the button was just released
      if (duration < DOT_DURATION) { // if the button was pressed for up to DOT cutoff
        inputSignal = inputSignal << 1 ; // remember the current signal as a DOT, add 0 to number
      } else { // if the button was pressed for longer than DOT cutoff
        inputSignal = (inputSignal << 1) + 1; // remember the current signal as a DASH add 1 to number
      }
      digitalWrite(LED, LOW); // turn off the LED
      buttonWasPressed = false; // consume previous button press
      lastTimestamp = currentTimestamp; // record the time the button was released
    } else { // the button was not just released
      if (inputSignal > 1) { // if there is data in the input signal buffer
        if (duration > SIGNAL_GAP || inputSignal >= strlen(letters)+2) { // if we have a complete letter
          mySerial.print(letters[inputSignal-2]); // parse the letter and send it via serial
          inputSignal=1; // reset the input signal buffer
        }
      }
    } // end of else (button was not previously pressed)
  } // end of else (button is not pressed)    
  if (mySerial.available() > 0) { // if there is data availalbe on the serial port
    char c = mySerial.read();
    mySerial.print(c);
    mySerial.print(": ");
    int index = getIndex(c);
    blinkLetter(index);
  }
}
