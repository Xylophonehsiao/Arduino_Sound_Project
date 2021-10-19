/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

  For MiniGolf 迷你高爾夫  Re-written by Yu-Li Hsiao
  
  2020.08.28  從Ardafruit 移植程式給這個shield
  2020.08.29  完成Demo
  2020.09.01  發現D10 reset後會送訊號，研究一下 Multiplexer 解決這個問題
              或是 button 跟 switch4 對調(沒用 pin10怪怪要看pinout
              
              Pinout:
                A0 - button1          D10 - switch4
                A1 - button2
                A2 - button3          D5  - switch3
                A3 - button4          D4  - switch2
                A4 - button5          D3  - switch1
                A5 - switch5
 ****************************************************/
// 定義按鈕
int button1, button2, button3, button4, button5; 
// reset button connect to reset pin
int button_state = 0;

// 定義開關
#define switch1 3
#define switch2 4
#define switch3 5
#define switch4 10 
#define switch5 A5

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  8      // VS1053 reset pin (output)
#define BREAKOUT_CS     6     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    7      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS  9    // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  
void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(3,3);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  //________________________________________________________________
  pinMode(A0, INPUT);         pinMode(switch1, OUTPUT);
  pinMode(A1, INPUT);         pinMode(switch2, OUTPUT);
  pinMode(A2, INPUT);         pinMode(switch3, OUTPUT);
  pinMode(A3, INPUT);         pinMode(switch4, OUTPUT);  
  pinMode(A4, INPUT);         pinMode(switch5, OUTPUT);

  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);
  digitalWrite(switch4, LOW);
  analogWrite(switch5, 0);
}

void loop() {
  // File is playing in the background
//  if (musicPlayer.stopped()) {
//    Serial.println("Done playing music");
//    while (1) {
//      delay(10);  // we're done! do nothing...
//    }
//  }
//  if (Serial.available()) {
//    char c = Serial.read();
//    
//    // if we get an 's' on the serial console, stop!
//    if (c == 's') {
//      musicPlayer.stopPlaying();
//    }
//    
//    // if we get an 'p' on the serial console, pause/unpause!
//    if (c == 'p') {
//      if (! musicPlayer.paused()) {
//        Serial.println("Paused");
//        musicPlayer.pausePlaying(true);
//      } else { 
//        Serial.println("Resumed");
//        musicPlayer.pausePlaying(false);
//      }
//    }
//  }
//
//  delay(100);

  button1 = analogRead(A0); button2 = analogRead(A1); button3 = analogRead(A2);
  button4 = analogRead(A3); button5 = analogRead(A4);
  
  if (button_state == 0){
    if (button1 >= 500){
      Serial.println("playing 001");
      digitalWrite(switch1, HIGH);
      musicPlayer.playFullFile("/001.mp3");
      button_state = 1;
    }
    else if (button2 >= 500){
      Serial.println("playing 002");
      digitalWrite(switch2, HIGH);
      musicPlayer.playFullFile("/001.mp3");
      button_state = 1;
    }
    else if (button3 >= 500){
      Serial.println("playing 003");
      digitalWrite(switch3, HIGH);
      musicPlayer.playFullFile("/001.mp3");
      button_state = 1;
    }
    else if (button4 >= 500){
      Serial.println("playing 004");
      digitalWrite(switch4, HIGH);
      musicPlayer.playFullFile("/001.mp3");
      button_state = 1;
    }
    else if (button5 >= 500){
      Serial.println("playing 005");
      analogWrite(switch5, 255);
      musicPlayer.playFullFile("/001.mp3");
      button_state = 1;
    }
  }

  if (musicPlayer.stopped() && button_state == 1){
    Serial.println("stop~");
    button_state = 0;
  }
}


/// File listing helper
//void printDirectory(File dir, int numTabs) {
//   while(true) {
//     
//     File entry =  dir.openNextFile();
//     if (! entry) {
//       // no more files
//       //Serial.println("**nomorefiles**");
//       break;
//     }
//     for (uint8_t i=0; i<numTabs; i++) {
//       Serial.print('\t');
//     }
//     Serial.print(entry.name());
//     if (entry.isDirectory()) {
//       Serial.println("/");
//       printDirectory(entry, numTabs+1);
//     } else {
//       // files have sizes, directories do not
//       Serial.print("\t\t");
//       Serial.println(entry.size(), DEC);
//     }
//     entry.close();
//   }
//}
