/* 

 This code is in the public domain.
 
 It's one of the examples from
 https://leanpub.com/lifeafterblink
 
 
 The code is adapted from
 http://www.arduino.cc/en/Tutorial/SerialEvent
 and
 http://arduino.cc/en/Tutorial/Blink
 
*/


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// Length of a dot in milliseconds
#define DIT 200

/*

Codes for Morse Coder
---------------------

The codes are strings representing the characters
including the alphabet, the digits from 0-9, and
sp,e punctuation.

The codes are stored as an array of strings,
indexed by the ASCII value of the character they represent.

ASCII characters that have no Morse code equivalent
are converted to *

Space is special.
It is converted to a string containing a single space.

*/

char *codes[127] = {
"*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"," ","*",".-..-.","*","*","*","*","*","*","*","*",".-.-.","--..--","-....-",".-.-.-","-..-.","-----",".----","..---","...--","....-",".....","-....","--...","---..","----.","---...","-.-.-.","*","-...-","-.--.","..--..",".--.-.",".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*",".-...","*","...-.-"
};

char *morse(char input) {
  return codes[input];
}

// Add code to define which LED to use here
int led = 13;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 141 bytes for the inputString:
  inputString.reserve(141);
  // Add code to initialise LED pin as output here
  pinMode(led, OUTPUT);  
}

void transmit(char *ascii_text) {
  int i = 0;
  Serial.print(ascii_text);
  while (ascii_text[i] != 0) {
    char c = ascii_text[i];
    switch (c) {
      case '*':
        break;
      case '.':
        on(1);
        break;
      case '-':
        on(3);
        break;
      case ' ':
        off(6);
        Serial.print(" ");
    }
    i++;
    off(1);
  }
  off(2);
  Serial.print(" ");
}

void on(int length) {
  // do something here
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(DIT * length);       // wait
}

void off(int length) {
  // do something here
  digitalWrite(led, LOW);
  delay(DIT * length);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    for (int i = 0; i < inputString.length(); i++) {
      transmit(morse(inputString.charAt(i)));
    }
    // print a newline
    Serial.print('\n');
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
  
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it and return
    if (inChar == '\n' or inChar == '\r') {
      stringComplete = true;
      return;
    } 
    // if not a newline, add the character to the inputString:
    inputString += inChar;
  }
}
  

