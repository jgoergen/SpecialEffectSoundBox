
void config_load() {

  Serial.println("CONFIG LOAD NOT DONE");
  return;
  /*
  Serial.print("Checking SD card for config file...");

  configFile = SD.open("config.init", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (configFile) {

    Serial.println("found");
    Serial.print("Reading config file...");

    //string dataString = myFile.readStringUntil('\n');
    // dataString.toInt()
    
    char[10000] configData;
    while (myFile.available()) {
      configData += myFile.read();
    }
    
    configFile.close();
    processConfigData(configData);
    
  } else {
    
    Serial.println("failed, using default configuration");
  }
  
  Serial.println("Config Data:");
  Serial.println(configData);  
  */
}

void config_save() {

  // YOU CANNOT WRITE TO THE SD CARD BECAUSE THE TEENSY 3.x SD LIB IS SET TO OPTIMZED READ!
  // SEE C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\SD\SD_t3.h 
  
  Serial.println("CONFIG SAVE NOT DONE");
  return;

  /*
     waveLayer1Volume
     waveLayer2Volume
     waveLayer3Volume
     voiceVolume
     voicePitch
     voiceDelay
     voiceReverb
  
  Serial.print("Saving config file...");
  configFile = SD.open("config.init", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (configFile) {

    // Serial.print("Writing to test.txt...");
    // myFile.println("testing 1, 2, 3.");
    // close the file:
    // myFile.close();
    
    Serial.println("done.");
    
  } else {
    
    Serial.println("failed");
  }*/
}
