void loadSettings ( void ) {

  Serial.println ("Reading EEPROM ...");

  EEPROM_readAnything(0, settings);

  if (settings.initialized != 1) {
    Serial.println ("Loading defaults ...");
    loadDefaults();
  }

  Serial.println ("Loading reflow profiles ...");
  loadReflowProfiles();

};

void loadDefaults( void ) {

  // If initialized is anything but 1, programmatically set defaults. This is useful for initial configuration.
  settings.initialized = 1;

  // Set default IP address
  settings.ipAddress[0] = 192;
  settings.ipAddress[1] = 168;
  settings.ipAddress[2] = 1;
  settings.ipAddress[3] = 100;

  settings.ipGateway[0] = 192;
  settings.ipGateway[1] = 168;
  settings.ipGateway[2] = 1;
  settings.ipGateway[3] = 1;

  settings.ipSubnet[0] = 255;
  settings.ipSubnet[1] = 255;
  settings.ipSubnet[2] = 255;
  settings.ipSubnet[3] = 0;

  // Set defaults for IP acquisition default
  settings.ipMode = 1; // 0 = Dynamic, 1 = Static

  // Set defaults for wifi access
  strncpy(settings.ssid, "default_ssid", 32);
  strncpy(settings.ssidPassword, "password", 64);




}

void loadReflowProfiles ( void ) {

  strncpy(reflowProfile[0].name, "ChipQuik SMD4300AX10 Sn63/Pb37 Water Wash", reflowProfileNameLength);
  reflowProfile[0].sort = 1;
  reflowProfile[0].profileRamp[0] = 30;
  reflowProfile[0].profileRamp[1] = 100;

  reflowProfile[0].profilePreheat[0] = 120;
  reflowProfile[0].profilePreheat[1] = 150;

  reflowProfile[0].profileRampToPeak[0] = 150;
  reflowProfile[0].profileRampToPeak[1] = 183;

  reflowProfile[0].profileReflow[0] = 210;
  reflowProfile[0].profileReflow[1] = 235;

  reflowProfile[0].profileCooling[0] = 240;
  reflowProfile[0].profileCooling[1] = 183;

  reflowProfile[0].profileFinishing[0] = 600;
  reflowProfile[0].profileFinishing[1] = 55; 

  strncpy(reflowProfile[1].name, "ChipQuik SMD291AX10 Sn63/Pb37", reflowProfileNameLength);
  reflowProfile[1].sort = 2;
  reflowProfile[1].profileRamp[0] = 30;
  reflowProfile[1].profileRamp[1] = 100;

  reflowProfile[1].profilePreheat[0] = 120;
  reflowProfile[1].profilePreheat[1] = 150;

  reflowProfile[1].profileRampToPeak[0] = 150;
  reflowProfile[1].profileRampToPeak[1] = 183;

  reflowProfile[1].profileReflow[0] = 210;
  reflowProfile[1].profileReflow[1] = 235;

  reflowProfile[1].profileCooling[0] = 240;
  reflowProfile[1].profileCooling[1] = 183;

  reflowProfile[1].profileFinishing[0] = 600;
  reflowProfile[1].profileFinishing[1] = 55; 

  strncpy(reflowProfile[2].name, "ChipQuik SMD4300SNL10 Sn96.5/Sn3/Ag0.5 Water Wash", reflowProfileNameLength);
  reflowProfile[2].sort = 3;
  reflowProfile[2].profileRamp[0] = 90;  // Time
  reflowProfile[2].profileRamp[1] = 150; // Temp

  reflowProfile[2].profilePreheat[0] = 180; // Time
  reflowProfile[2].profilePreheat[1] = 175; // Temp

  reflowProfile[2].profileRampToPeak[0] = 210; // Time
  reflowProfile[2].profileRampToPeak[1] = 217; // Temp

  reflowProfile[2].profileReflow[0] = 240; // Time
  reflowProfile[2].profileReflow[1] = 249; // Temp

  reflowProfile[2].profileCooling[0] = 270; // Time
  reflowProfile[2].profileCooling[1] = 217; // Temp

  reflowProfile[2].profileFinishing[0] = 600;
  reflowProfile[2].profileFinishing[1] = 55; 
  

  strncpy(reflowProfile[3].name, "ChipQuik SMD291SNL10 Sn96.5/Sn3/Ag0.5", reflowProfileNameLength);
  reflowProfile[3].sort = 4;
  reflowProfile[3].profileRamp[0] = 90;  // Time
  reflowProfile[3].profileRamp[1] = 150; // Temp

  reflowProfile[3].profilePreheat[0] = 180; // Time
  reflowProfile[3].profilePreheat[1] = 175; // Temp

  reflowProfile[3].profileRampToPeak[0] = 210; // Time
  reflowProfile[3].profileRampToPeak[1] = 217; // Temp

  reflowProfile[3].profileReflow[0] = 240; // Time
  reflowProfile[3].profileReflow[1] = 249; // Temp

  reflowProfile[3].profileCooling[0] = 270; // Time
  reflowProfile[3].profileCooling[1] = 217; // Temp

  reflowProfile[3].profileFinishing[0] = 600;
  reflowProfile[3].profileFinishing[1] = 55; 

}


