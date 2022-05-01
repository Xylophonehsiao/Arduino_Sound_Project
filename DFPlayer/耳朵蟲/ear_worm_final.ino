/*
 * 2022.04.30 for ear_worm 
 * Arduino NANO with two DF_Players
 * for strangle UART to second DF_Player with auto-stop
 * so just send message in setup
 */
 
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

SoftwareSerial mySerial_1(2, 3); // RX, TX
DFPlayerMini_Fast DFP_1;
SoftwareSerial mySerial_2(9, 10); // RX, TX
DFPlayerMini_Fast DFP_2;"

const byte potPin_1 = A2;
const byte potPin_2 = A0;

byte volumeLevel_1 = 0;
byte volumeLevel_2 = 0;
int vol_1 = 0;
int vol_2 = 0;

void setup()
{
  mySerial_1.begin(9600);
  DFP_1.begin(mySerial_1);
  mySerial_2.begin(9600);
  DFP_2.begin(mySerial_2);
  
  delay(100);
  mySerial_1.listen();
    vol_1 = analogRead(potPin_1);
    volumeLevel_1 = map(vol_1, 0, 1023, 0, 30);   
    DFP_1.volume(volumeLevel_1);

  delay(100);
  mySerial_2.listen();
    vol_2 = analogRead(potPin_2);
    volumeLevel_2 = map(vol_2, 0, 1023, 0, 30);
    DFP_2.volume(volumeLevel_2); 
}

void loop()
{
}
