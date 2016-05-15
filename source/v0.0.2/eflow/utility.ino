
double c2f(double celsius)
{
  return 1.8 * celsius + 32;
}




void printMacAddress( void ) {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void printAPMacAddress( void ) {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.softAPmacAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

// Clear the eeprom of all values.
void eepromClear() {
  for (int i = 0; i < 1024; i++)
    EEPROM.write(i, 0);

  EEPROM.end();
}

String escapeParameter(String param) {
  param.replace("+", " ");
  param.replace("%21", "!");
  param.replace("%23", "#");
  param.replace("%24", "$");
  param.replace("%26", "&");
  param.replace("%27", "'");
  param.replace("%28", "(");
  param.replace("%29", ")");
  param.replace("%2A", "*");
  param.replace("%2B", "+");
  param.replace("%2C", ",");
  param.replace("%2F", "/");
  param.replace("%3A", ":");
  param.replace("%3B", ";");
  param.replace("%3D", "=");
  param.replace("%3F", "?");
  param.replace("%40", "@");
  param.replace("%5B", "[");
  param.replace("%5D", "]");

  return param;
}
