
void updateSensors( void ) {

  double sensorA_offset = 7;
  double sensorB_offset = 7;

  sensorA = readSensor(0) + sensorA_offset;
  sensorB = readSensor(1) + sensorB_offset;

}

// 0 = Sensor A
// 1 = Sensor B
double readSensor(uint8_t sensor) {
  double temperature;                // current reading
  double total = 0;                  // the running total
  double average = 0;                // the average

  if (sensor == 0) {
    temperature = thermocouple_A.readCelsius();
    readings_A[readIndex_A] = temperature;

    readIndex_A++;

    // if we're at the end of the array...
    if (readIndex_A >= numReadings) {
      // ...wrap around to the beginning:
      readIndex_A = 0;
    }

    for (uint8_t i = 0; i < numReadings; i++) {
      total += readings_A[i];
    }

    average = total / numReadings;
  } else if (sensor == 1) {
    temperature = thermocouple_B.readCelsius();
    readings_B[readIndex_B] = temperature;

    readIndex_B++;

    // if we're at the end of the array...
    if (readIndex_B >= numReadings) {
      // ...wrap around to the beginning:
      readIndex_B = 0;
    }

    for (uint8_t i = 0; i < numReadings; i++) {
      total += readings_B[i];
    }

    average = total / numReadings;
  } else {
    Serial.println("Invalid sensor selected in: readSensor");
    return (0);
  }


  if (isnan(temperature)) {
    if (sensor == 0) {
      Serial.println("Something wrong with thermocouple A!");
      return (0);
    } else if (sensor == 1) {
      Serial.println("Something wrong with thermocouple B!");
      return (0);
    }

  } else {
    return (average);
  }
}

