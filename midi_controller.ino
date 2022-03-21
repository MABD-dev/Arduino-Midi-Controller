#include <usbmidi.h>


int startNote = 40;

int cPin = 8;
int dPin = 7;
int ePin = 6;
int fPin = 5;
int gPin = 4;
int aPin = 3;
int bPin = 2;

int pinNumberOffset = 2;

int buttonIsPushed[] = {0, 0, 0, 0, 0, 0, 0};


int potPin = A0;

int plusButtonOn = 0;
int plusOctavePin = 10;

int minusButtonOn = 0;
int minusOctavePin = 9;

int oldPotValue = -1;
int potValue = 0;



void setup() {
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(ePin, INPUT);
  pinMode(fPin, INPUT);
  pinMode(gPin, INPUT);
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);


  pinMode(plusOctavePin, INPUT);
  pinMode(minusOctavePin, INPUT);


  Serial.begin(9600);
}

void loop() {
  
  for (int i = 0; i < 7; i++) {
    checkPushButtonPin(i + pinNumberOffset);
  }

  checkPlusOctaveButton();
  checkMinusOctaveButton();
  

  
//  potValue = analogRead(potPin);
//  potValue = map(potValue, 0, 1023, 0, 127);

//  if (potValue > oldPotValue +10 || potValue < oldPotValue-10) {
//    oldPotValue = potValue;
//    MIDIcontrolChange(0xB2, 07, potValue);
//  }


}

void checkPushButtonPin(int pinNumber) {
  if (digitalRead(pinNumber) == 1) {
    if (buttonIsPushed[pinNumber - pinNumberOffset] == 0) {
      MIDImessage(0x91, startNote+(6-pinNumber-pinNumberOffset), 122);
      buttonIsPushed[pinNumber - pinNumberOffset] = 1;
    }
  }else {
    if (buttonIsPushed[pinNumber - pinNumberOffset] == 1) {
      MIDImessage(0x81, startNote+(6-pinNumber-pinNumberOffset), 122);
      buttonIsPushed[pinNumber - pinNumberOffset] = 0;
    }
  }
}

void checkPlusOctaveButton() {
  if (digitalRead(plusOctavePin) == 1) {
    if (plusButtonOn == 0) {
      startNote += 12 - pinNumberOffset;
      plusButtonOn = 1;
    }
  }else {
      if (plusButtonOn == 1) {
        plusButtonOn = 0;
      }
    }
}

void checkMinusOctaveButton() {
  if (digitalRead(minusOctavePin) == 1) {
    if (minusButtonOn == 0) {
      startNote -= 12 + pinNumberOffset;
      minusButtonOn = 1;
    }
  }else {
      if (minusButtonOn == 1) {
        minusButtonOn = 0;
      }
    }
}



void MIDIcontrolChange(int command, int controller, int numberData) {
  Serial.write(command);
  Serial.write(controller);
  Serial.write(numberData);
}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}