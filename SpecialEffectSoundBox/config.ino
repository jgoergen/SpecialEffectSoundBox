
void config_load(char[] configData) {

  Serial.print("CONFIG LOAD NOT DONE");
  return;
  
  Serial.print("Checking SD card for config file...");

  configFile = SD.open("config.init", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (configFile) {

    Serial.println("found");
    Serial.print("Reading config file...");

    /*
     string dataString = myFile.readStringUntil('\n');
     dataString.toInt()
     */
    
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
}

void config_save() {

  /*
    int waveLayer1Volume
    int waveLayer2Volume
    int waveLayer3Volume
    int voiceVolume
    int voicePitch
    int voiceDelay
    int voiceReverb
  */
   
  Serial.print("CONFIG SAVE NOT DONE");
  return;

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
  }
}
