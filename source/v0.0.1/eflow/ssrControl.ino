
void dispatch100ms( void ) {

  /*
  if (Output > WindowSize / 4) {
    digitalWrite(SSR_OUTPUT, 1);
  } else {
    digitalWrite(SSR_OUTPUT, 0);
  }
  */
  if (processEnable) { // If process is enabled, begin the reflow.
    
    if (heaterDutyIndex == -1) {
      if (Output >= 901) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 1;
        heaterDuty[6] = 1;
        heaterDuty[7] = 1;
        heaterDuty[8] = 1;
        heaterDuty[9] = 1;

        heaterDutyIndex = 9;
        //Serial.println ("--100%");
      } else if (Output >= 801 && Output <= 900) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 1;
        heaterDuty[6] = 1;
        heaterDuty[7] = 1;
        heaterDuty[8] = 1;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--90%");
      } else if (Output >= 701 && Output <= 800) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 1;
        heaterDuty[6] = 1;
        heaterDuty[7] = 1;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--80%");
      } else if (Output >= 601 && Output <= 700) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 1;
        heaterDuty[6] = 1;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--70%");
      } else if (Output >= 501 && Output <= 600) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 1;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--60%");
      } else if (Output >= 401 && Output <= 500) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 1;
        heaterDuty[5] = 0;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--50%");
      } else if (Output >= 301 && Output <= 400) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 1;
        heaterDuty[4] = 0;
        heaterDuty[5] = 0;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--40%");
      } else if (Output >= 201 && Output <= 300) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 1;
        heaterDuty[3] = 0;
        heaterDuty[4] = 0;
        heaterDuty[5] = 0;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--30%");
      } else if (Output >= 101 && Output <= 200) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 1;
        heaterDuty[2] = 0;
        heaterDuty[3] = 0;
        heaterDuty[4] = 0;
        heaterDuty[5] = 0;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--20%");
      } else if (Output >= 1 && Output <= 100) {
        heaterDuty[0] = 1;
        heaterDuty[1] = 0;
        heaterDuty[2] = 0;
        heaterDuty[3] = 0;
        heaterDuty[4] = 0;
        heaterDuty[5] = 0;
        heaterDuty[6] = 0;
        heaterDuty[7] = 0;
        heaterDuty[8] = 0;
        heaterDuty[9] = 0;

        heaterDutyIndex = 9;
        //Serial.println ("--10%");
      } else {
        digitalWrite(SSR_OUTPUT, 0);
      }
    } else {
      digitalWrite(SSR_OUTPUT, heaterDuty[heaterDutyIndex]);
      heaterDutyIndex--;

    }
  }
}

