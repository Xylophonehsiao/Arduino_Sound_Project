/*
 * 2022.08.08 for YW~
 * Arduino NANO with DF_Player
 * play when press the button, and change volume with knob.
 * 
 */
 
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

SoftwareSerial mySerial(2, 3); 
// RX connect to mp3's TX, TX connect to mp3's RX with 1kohm
DFPlayerMini_Fast DFP;

const byte potPin = A0;
const byte playPin = 12;
byte volumeLevel = 0;
int vol = 0;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  DFP.begin(mySerial);
  
  delay(100);
  mySerial.listen();
  vol = analogRead(potPin);
  volumeLevel = map(vol, 0, 1023, 0, 30); // Volume range 0 - 30
  DFP.volume(volumeLevel);

  DFP.play(1);
//  DFP.startRepeat();
}

void loop()
{
  mySerial.listen();
  vol = analogRead(potPin);
  volumeLevel = map(vol, 0, 1023, 0, 30);   
  DFP.volume(volumeLevel);
  if (digitalRead(playPin) == 0){
    DFP.play(1);
  }
  
  delay(100);
}
