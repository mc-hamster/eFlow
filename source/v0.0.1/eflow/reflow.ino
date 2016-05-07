
uint16_t processTimer = 0;
uint16_t processReflowTimer = 0;
uint8_t processReflowInitTimer = 0;
uint8_t profileZone = 0;
double Kp_previous = 0, Ki_previous = 0, Kd_previous = 0;
uint8_t processAgressiveness = 15;
uint8_t processTempReached = 0;
uint8_t processTempHysteresis = 3;
void dispatchProcessPerSecond ( ) {
   uint16_t zoneTime = 0;

  if (processTimer == reflowStatsProfileLength) {
     Serial.println("Process has taken too long to complete.");
     systemMessage = "Process has taken too long to complete.";
     processStop();
     return;
  }


  // Init
  if (processEnable == 1) {
    processEnable = 2;

    processTimer = 0;
    
    Setpoint = startup_temp;

    reflowStats.profile[processTimer].time = processTimer;
    reflowStats.profile[processTimer].sensorA= sensorA * 100;
    reflowStats.profile[processTimer].sensorB = sensorB * 100;
    reflowStats.profile[processTimer].Setpoint = Setpoint;

  // Reflow Process in progress
  } else if ( processEnable == 2 ) {

    if (profileZone == 0) {
      // TODO:
      //   During this phase, measure the ability of the oven to gain temperature.
      //   If it is unable to maintain a set rate of rise, abort the process.
      //   Inability to maintain a rise may indicate equipment failure.

      if ( Input + processTempHysteresis >= startup_temp) {
        processTempReached = 1;
      }


      
      Setpoint = startup_temp;
      if (processTempReached && processTimer >= startup_sec) {
        profileZone = 1;
        processReflowTimer = 0;
        processReflowInitTimer = 0;
        processTempReached = 0;
      } else {
        if (processTimer >= startup_sec) {
          systemMessage = "Unable to reach process startup temperature within given time! Aborting.";
          processStop();
          return;
          
        }
      }

      systemMessage = "Normalizing oven conditions...";
      
    } else if (profileZone == 1) {
      if (processReflowInitTimer < processAgressiveness) {
        if (processReflowInitTimer == 0) {
          Kp_previous = Kp;
          Ki_previous = Ki;
          Kd_previous = Kd;
        }

        Kp = Kp_agressive;
        Ki = Ki_agressive;
        Kd = Kd_agressive;
        myPID.SetTunings(Kp, Ki, Kd);

        processReflowInitTimer++;
      } else {
        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);

      }

      if ( Input + processTempHysteresis >= reflowProfile[0].profileRamp[1]) {
        processTempReached = 1;
      }
      

      Setpoint = reflowProfile[0].profileRamp[1];
      zoneTime = reflowProfile[0].profileRamp[0]; // At what point in the reflow should we exit this zone?
      if (processTempReached && processReflowTimer > zoneTime) {
        profileZone = 2;
        processReflowInitTimer = 0;
        processTempReached = 0;

        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);     
      
      }

      systemMessage = "Ramp to soak ...";

    
    } else if (profileZone == 2) {
      if (processReflowInitTimer < processAgressiveness) {
        if (processReflowInitTimer == 0) {
          Kp_previous = Kp;
          Ki_previous = Ki;
          Kd_previous = Kd;
        }

        Kp = Kp_agressive;
        Ki = Ki_agressive;
        Kd = Kd_agressive;
        myPID.SetTunings(Kp, Ki, Kd);

        processReflowInitTimer++;
      } else {
        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);

      }

      if ( Input + processTempHysteresis >= reflowProfile[0].profileRamp[1] ) {
        processTempReached = 1;
      }

      Setpoint = reflowProfile[0].profilePreheat[1];
      zoneTime = reflowProfile[0].profilePreheat[0]; // At what point in the reflow should we exit this zone?
      if (processTempReached && processReflowTimer > zoneTime) {
        profileZone = 3;
        processReflowInitTimer = 0;
        processTempReached = 0;

        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);     
      
      }
    
      systemMessage = "Preheat / Soak ...";

    } else if (profileZone == 3) {
      if (processReflowInitTimer < processAgressiveness) {
        if (processReflowInitTimer == 0) {
          Kp_previous = Kp;
          Ki_previous = Ki;
          Kd_previous = Kd;
        }

        Kp = Kp_agressive;
        Ki = Ki_agressive;
        Kd = Kd_agressive;
        myPID.SetTunings(Kp, Ki, Kd);

        processReflowInitTimer++;
      } else {
        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);

      }

      if ( Input + processTempHysteresis >= reflowProfile[0].profileRampToPeak[1] ) {
        processTempReached = 1;
      }

      Setpoint = reflowProfile[0].profileRampToPeak[1];
      zoneTime = reflowProfile[0].profileRampToPeak[0]; // At what point in the reflow should we exit this zone?
      if (processTempReached && processReflowTimer > zoneTime) {
        profileZone = 4;
        processReflowInitTimer = 0;
        processTempReached = 0;

        Kp = Kp_previous;
        Ki = Ki_previous;
        Kd = Kd_previous;
        myPID.SetTunings(Kp, Ki, Kd);     
      
      }

      systemMessage = "Ramp to peak ...";

    
    } else if (profileZone == 4) {
      myPID.SetTunings(Kp_agressive, Ki_agressive, Kd_agressive);

      // We don't need to use the process hysteresis here since we want to get up to
      //  the set point as fast as possible.

      Setpoint = reflowProfile[0].profileReflow[1];
      zoneTime = reflowProfile[0].profileReflow[0]; // At what point in the reflow should we exit this zone?
      if (( Input + 4 ) >= reflowProfile[0].profileReflow[1] && processReflowTimer > zoneTime) {
        profileZone = 5;
        processReflowInitTimer = 0;
      }

      systemMessage = "Reflowing!";
    
    } else if (profileZone == 5) {
      Setpoint = reflowProfile[0].profileCooling[1];
      zoneTime = reflowProfile[0].profileCooling[0]; // At what point in the reflow should we exit this zone?
      if (( Input + 1 ) >= reflowProfile[0].profileCooling[1] && processReflowTimer > zoneTime) {
        profileZone = 6;
      }

      systemMessage = "Cooling ...";

    
    } else if (profileZone == 6) {
      Setpoint = reflowProfile[0].profileFinishing[1];
      zoneTime = reflowProfile[0].profileFinishing[0]; // At what point in the reflow should we exit this zone?
      if (( Input + 3 ) >= reflowProfile[0].profileFinishing[1] && processReflowTimer > zoneTime) {
        profileZone = 7;
      }

      systemMessage = "Finishing ...";

    }
    
    /*
    Serial.print(" Job Timer ");
    Serial.print(processTimer);
    Serial.print(" Reflow Timer ");
    Serial.print(processReflowTimer);
    Serial.print(" Zone Time ");
    Serial.print(zoneTime);
    Serial.print(" Setpoint ");
    Serial.print(Setpoint);
    Serial.print(" Input ");
    Serial.print(Input);
    Serial.println();
    */

    reflowStats.profile[processTimer].time = processTimer;
    reflowStats.profile[processTimer].sensorA= sensorA * 100;
    reflowStats.profile[processTimer].sensorB = sensorB * 100;
    reflowStats.profile[processTimer].Setpoint = Setpoint;
    reflowStats.profile[processTimer].reflowTime = processReflowTimer;
    


/*
struct reflowStats_t
{
  uint8_t run; // 0 = Unexecuted, 1 = Completed, 2, In Progress, 3 = Aborted, 4 = Abnormal Error
  uint8_t reflowProfilePrevious; // What reflow profile was selected?
  uint8_t reflowProfileNext; // What reflow profile is selected?
  uint16_t profile[900][4]; // 900 positions to save up to 1200 seconds (15 minutes). uInt for each temerature sensor, Input and Setpoint.
} reflowStats;
*/
    if (profileZone != 0) {
      processReflowTimer++;
    }

  // TBD
  } else if ( processEnable == 3 ) {
    // Process aborted
  // Do nothing
  } else {
    
  }
  
  // Progress the timer.
  if (processEnable != 0) {
    processTimer++;
  }


}


void processGo ( void ) {

  if (safeTemperature < ((sensorA + sensorB) / 2)) {
    systemMessage = "Initialization aborted. Oven is warmer than the safe temperature.";
    return;
  }

  if (processEnable != 2) {
    processEnable = 1;
    processTimer = 0;
    processReflowInitTimer = 0;
    processReflowTimer = 0;
    profileZone = 0;

    memset(&reflowStats, 0, sizeof reflowStats);
    return;
  }

}

void processStop ( void ) {

  Serial.println ("Process Aborting ...");

  //if (processEnable == 2) {

  processEnable = 0;
  processTempReached = 0;
  Setpoint = 0;
  digitalWrite(SSR_OUTPUT, 0); // Make sure SSR is turned off!

  processTimer = 0;
  processReflowTimer = 0;
  processReflowInitTimer = 0;
  profileZone = 0;


  //}


}



