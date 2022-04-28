/*
 * 2022.04.29 for ear_worm 
 * Arduino NANO with two DF_Players
 */

#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

SoftwareSerial mySerial_1(2, 3); // RX, TX
DFPlayerMini_Fast DFP_1;
SoftwareSerial mySerial_2(4, 5); // RX, TX
DFPlayerMini_Fast DFP_2;

const byte potPin_1 = A0;
const byte potPin_2 = A2;

byte volumeLevel_1 = 0; //variable for holding volume level
byte volumeLevel_2 = 0; //variable for holding volume level
int vol_1 = 0;
int vol_2 = 0;

void setup()
{
  mySerial_1.begin(9600);
  DFP_1.begin(mySerial_1);
  mySerial_2.begin(9600);
  DFP_2.begin(mySerial_2);
  delay(1000);
  mySerial_1.listen();
//  DFP_1.play(1);
//  delay(1000);
  DFP_1.loop(1);
  delay(1000);
  mySerial_2.listen();
//  DFP_2.play(1);
//  delay(1000);
  DFP_2.loop(1);
}

void loop()
{
  delay(100);
  mySerial_1.listen(); // Select Ser1 for receiving 
    vol_1 = analogRead(potPin_1);
    volumeLevel_1 = map(vol_1, 0, 1023, 0, 30);   
    DFP_1.volume(volumeLevel_1);
    
  delay(100);
  mySerial_2.listen(); // Select Ser2 for receiving
    vol_2 = analogRead(potPin_2);
    volumeLevel_2 = map(vol_2, 0, 1023, 0, 30);
    DFP_2.volume(volumeLevel_2); 
}
