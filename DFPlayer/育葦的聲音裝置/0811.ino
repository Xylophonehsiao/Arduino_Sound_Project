/*
 * 2022.08.08 for YW~
 * Arduino NANO with DF_Player
 * play when press the button, and change volume with knob.
 * 
 * 2022.08.09
 * add millis() to avoid from double click button.
 * 
 * 2022.08.10
 * fix for wiring broad.
 * 
 */
 
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

SoftwareSerial mySerial(2, 3); 
// RX connect to mp3's TX, TX connect to mp3's RX with 1kohm
DFPlayerMini_Fast DFP;

const byte potPin = A0;
const byte playPin = A2;
byte volumeLevel = 0;
int vol = 0;
int flag = 0;
const int button_waitting_time = 10000;

unsigned long t;
unsigned long t1;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  DFP.begin(mySerial);
  
  delay(100);
  mySerial.listen();
  vol = analogRead(potPin);
  volumeLevel = map(vol, 0, 1023, 30, 0); // Volume range 0 - 30
  DFP.volume(volumeLevel);
}

void loop()
{
  mySerial.listen();
  vol = analogRead(potPin);
  volumeLevel = map(vol, 0, 1023, 30, 0);   
  DFP.volume(volumeLevel);
  
  if (flag == 0 && analogRead(playPin) <100){
    DFP.play(1);
    flag = 1;
    t1 = millis();
    Serial.println(t1);
  }
  t = millis();
  if (flag == 1 && t >= t1 + button_waitting_time){
    flag = 0;
    Serial.println(flag);
  }
}
