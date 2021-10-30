void ranSound(){
  if (buttom > 4){
      //Serial.println("Next!");
      minimum = minimum + 20;
      maxmum = maxmum + 20;
      buttom = 0;
      cycle ++;
  }
  String num = String(ranNum, DEC);
  Serial.println("/mp3/"+ num +".wav");
  String fileName = String("/mp3/"+ num +".wav");
  char charBuf[50];
  fileName.toCharArray(charBuf, 50);
  musicPlayer.playFullFile(charBuf);
  buttom ++;
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
