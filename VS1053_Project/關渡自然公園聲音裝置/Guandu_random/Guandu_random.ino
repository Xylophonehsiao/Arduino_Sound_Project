/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

  2021.10.18 For 關渡自然公園聲音裝置  re-written by Yu-Li Hsiao
  2021.10.30 For 100 wav file
 ****************************************************/
// 定義按鈕
int button1;
// reset button connect to reset pin
int button_state = 0;
int ranNum;
const int minimum1 = 1;
const int maxmum1 = 50;
const int minimum2 = 51;
const int maxmum2 = 60;
const int minimum3 = 61;
const int maxmum3 = 65;
int minimum = minimum1;
int maxmum = maxmum1;
int cycle = 0;
int buttom = 1;
int sound_signal = 0;
int sound_gate = 200;                   //聲音門檻在這～

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13                  // SPI Clock, shared with SD card
#define MISO 12                 // Input data, from VS1053/SD card
#define MOSI 11                 // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  8      // VS1053 reset pin (output)
#define BREAKOUT_CS     6      // VS1053 chip select pin (output)
#define BREAKOUT_DCS    7      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS  9              // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2                 // VS1053 Data request, ideally an Interrupt pin

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
  pinMode(A1, INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  sound_signal = analogRead(A1);
  //sound_signal = Serial.read();
  ranNum = random(minimum, maxmum);
  
  if (button_state == 0){
    if (sound_signal < sound_gate){
    //if (sound_signal == 49){
      button_state = 1;
      Serial.println("play!");
      ranSound();
    }
  }

  if (musicPlayer.stopped() && button_state == 1){
    Serial.println("stop~");
    button_state = 0;
    while(Serial.read()>= 0){}    // clean Sreial buffer
  }

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
//  delay(100);  // File is playing in the background
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
}
