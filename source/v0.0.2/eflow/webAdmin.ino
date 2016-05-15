
void handleAdminNav() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>eFlow -- Admin Main Menu</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Configure</h2>\n";
  message += "  <br>\n";
  message += "  <a href=/conf/wifi target=right>Wifi</a><br>\n";
  message += "  <a href=/conf/network target=right>Network</a><br>\n";
  message += "  <a href=/conf/accounts target=right>Accounts</a><br>\n";
  message += "  <a href=/conf/sensors target=right>Sensors</a> (Work in progress)<br>\n";
  message += "  <br>\n";
  message += "  <h2>System</h2>\n";
  message += "  <a href=/system/defaults target=right>Load Defaults</a><br>\n";
  message += "  <a href=/system/apply target=right>Apply Changes</a><br>\n";
  message += "  <a href=/system/restart target=right>Restart</a> (Leave admin configuration)<br>\n";
  message += "  <h2>Preview</h2>\n";
  message += "  <a href=/system/settings target=right>Display Settings</a><br>\n";
  message += "  <br>\n";
  //  message += "  Auto Restart in ... 30:00\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );
}

void handleAdminConfAccounts() {
  boolean saved = 0;

  if (server.arg("account_0") != "") {
    saved = 1;

    String account_0 = escapeParameter(server.arg("account_0"));
    String account_1 = escapeParameter(server.arg("account_1"));
    String account_2 = escapeParameter(server.arg("account_2"));
    String account_3 = escapeParameter(server.arg("account_3"));
    String account_4 = escapeParameter(server.arg("account_4"));

  }

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Accounts</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";

  if (saved) {
    message += "<b>Settings saved. Remember to apply settings before restarting.</b><br><br>\n";
  }

  message += "  <h2>Configure Accounts</h1>\n";
  message += "<form id=\"form1\" name=\"form1\" method=\"post\" action=\"/conf/accounts\">\n";
  message += "<p>Don't use these characters in any password: &quot; &gt; &lt;. It will break things. This is a known issue.</p>\n";
  message += "<table border=\"0\">\n";
  message += "<tr>\n";
  message += "<td>&nbsp;</td>\n";
  message += "<td>Password</td>\n";
  message += "</tr>\n";
  message += "<tr>\n";

  message += "</tr>\n";
  message += "</table>\n";
  message += "<p><br />\n";
  message += "<input type=\"submit\" name=\"button\" value=\"Submit\" />\n";
  message += "</p>\n";
  message += "</form>\n";
  message += "\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );
}

void handleAdminConfWifi() {
  boolean saved = 0;

  if (server.arg("ssid") != "" && server.arg("ssidPassword") != "") {
    saved = 1;

    String serverArgSsid = escapeParameter(server.arg("ssid"));
    String serverArgSsidPassword = escapeParameter(server.arg("ssidPassword"));

    serverArgSsid.toCharArray(settings.ssid, 32);
    serverArgSsidPassword.toCharArray(settings.ssidPassword, 64);

  }

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Wifi</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";

  if (saved) {
    message += "<b>Settings saved. Remember to apply settings before restarting.</b><br><br>\n";
  }

  if (!saved) {
    message += "<form method=\"post\" action=\"/conf/wifi\">\n";

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    if (n == 0)
      message += "no networks found";
    else  {
      message += "Select a network (unsecured networks are not supported):<br />\n";

      for (int i = 0; i < n; ++i) {
        if (WiFi.encryptionType(i) != ENC_TYPE_NONE) {
          message += "<input type=\"radio\" name=\"ssid\" value=\"" + String(WiFi.SSID(i)) + "\" />" + String(WiFi.SSID(i)) + " (" + WiFi.RSSI(i) + ")<br />\n";
        }
        // Yield some cpu cycles to IP stack.
        //   This is important in case the list is large and it takes us tome to return
        //   to the main loop.
        yield();
      }
    }
    message += "password <input type=\"text\" name=\"ssidPassword\" size=\"64\" maxlength=\"64\"/><br /><br />";
    message += "<input type=\"submit\" name=\"button\"  value=\"Submit\" />";
    message += "</form>";
  }

  message += "Current ssid: " + String(settings.ssid) + "<br>\n";
  message += "Current ssidPassword: " + String(settings.ssidPassword) + "<br>\n";


  message += "  <a href=/>Main Menu</a><br>\n";

  message += "</body>\n";
  message += "</html>\n";

  server.send( 200, "text/html", message );
  //server.send ( 200, "text/html", message );
}


void handleAdminConfNetwork() {

  boolean saved = 0;

  if (server.arg("ipMode") != "") {
    saved = 1;

    String ipMode = server.arg("ipMode");

    String ip_0 = server.arg("ip_0");
    String ip_1 = server.arg("ip_1");
    String ip_2 = server.arg("ip_2");
    String ip_3 = server.arg("ip_3");

    String gateway_0 = server.arg("gateway_0");
    String gateway_1 = server.arg("gateway_1");
    String gateway_2 = server.arg("gateway_2");
    String gateway_3 = server.arg("gateway_3");

    String subnet_0 = server.arg("subnet_0");
    String subnet_1 = server.arg("subnet_1");
    String subnet_2 = server.arg("subnet_2");
    String subnet_3 = server.arg("subnet_3");

    settings.ipMode = ipMode.toInt();

    if (settings.ipMode == 1) {
      settings.ipAddress[0] = ip_0.toInt();
      settings.ipAddress[1] = ip_1.toInt();
      settings.ipAddress[2] = ip_2.toInt();
      settings.ipAddress[3] = ip_3.toInt();

      settings.ipGateway[0] = gateway_0.toInt();
      settings.ipGateway[1] = gateway_1.toInt();
      settings.ipGateway[2] = gateway_2.toInt();
      settings.ipGateway[3] = gateway_3.toInt();

      settings.ipSubnet[0] = subnet_0.toInt();
      settings.ipSubnet[1] = subnet_1.toInt();
      settings.ipSubnet[2] = subnet_2.toInt();
      settings.ipSubnet[3] = subnet_3.toInt();
    }

  }

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Network</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";

  if (saved) {
    message += "<b>Settings saved. Remember to apply settings before restarting.</b><br><br>\n";
  }

  message += "<form id=form1 name=form1 method=post action=/conf/network>\n";
  message += "<table border=1>\n";
  message += "<tr>\n";
  message += "<td><p>\n";

  if (settings.ipMode == 1) {
    message += " <input name=ipMode type=radio value=1 checked=checked /> \n";
  } else {
    message += " <input name=ipMode type=radio value=1 /> \n";
  }

  message += "Static</p>\n";
  message += "<p>IP: \n";
  message += "<input name=ip_0 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[0]) + " />\n";
  message += "<input name=ip_1 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[1]) + " />\n";
  message += "<input name=ip_2 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[2]) + " />\n";
  message += "<input name=ip_3 type=text size=3 maxlength=3 value=" + String(settings.ipAddress[3]) + " />\n";
  message += "<br />\n";
  message += "Gateway:\n";
  message += "<input name=gateway_0 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[0]) + " />\n";
  message += "<input name=gateway_1 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[1]) + " />\n";
  message += "<input name=gateway_2 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[2]) + " />\n";
  message += "<input name=gateway_3 type=text size=3 maxlength=3 value=" + String(settings.ipGateway[3]) + " />\n";
  message += "<br />\n";
  message += "Subnet:\n";
  message += "<input name=subnet_0 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[0]) + " />\n";
  message += "<input name=subnet_1 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[1]) + " />\n";
  message += "<input name=subnet_2 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[2]) + " />\n";
  message += "<input name=subnet_3 type=text size=3 maxlength=3 value=" + String(settings.ipSubnet[3]) + " />\n";
  message += "</p></td>\n";
  message += "</tr>\n";
  message += "<tr>\n";
  message += "<td><p>\n";

  if (settings.ipMode == 0) {
    message += " <input name=ipMode type=radio value=0 checked=checked /> \n";
  } else {
    message += " <input name=ipMode type=radio value=0 /> \n";
  }

  message += " Dynamic<br />\n";
  message += " </p>\n";
  message += "<p>Select this to have your router automatically assign an address.<br />\n";
  message += "</p></td>\n";
  message += "</tr>\n";
  message += "</table>\n";
  message += "<input type=submit name=button id=button value=Submit />\n";
  message += "</p>\n";
  message += "</form>\n";

  message += "\n";
  message += "\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );
}

void handleAdminConfSensors() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Configure Sensors</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Sensor Configuration</h1>\n";
  message += "  <br>\n";
  message += "  Configure Accounts<br>\n";
  message += "  Configure Sensors<br>\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";


  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );
}


void handleAdminDefaults( void ) {

  loadDefaults();

  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Loading Defaults...</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Loading Defaults...DONE</h1>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );

  //delay(250);


}

void handleAdminRestart() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Restarting...</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Restarting...</h1>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send( 200, "text/html", message );

  ESP.restart();

  // This is here in the event ESP.reset doesn't work. This will trigger the watchdog.
  while (1) { };

}

void handleAdminApply() {
  String message = "\n\n";

  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Saving settings to EEPROM...</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Applying new settings...DONE</h1>\n";
  message += "<br>\n";
  message += "<br>\n";
  message += "<!-- Wrote ";
  message += EEPROM_writeAnything(0, settings);
  message += "bytes -->\n";
  message += "<br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "</body>\n";
  message += "</html>\n";

  EEPROM.commit(); // Required for ESP8266. Not part of normal eeprom library.

  // Reading the config back out is probably unnecessary, but it is good insurance.
  EEPROM_readAnything(0, settings);

  server.send( 200, "text/html", message );
  //  server.send ( 200, "text/html", message );

}
void handleAdminSettings () {
  String message = "\n\n";

  int flashSize = ESP.getFlashChipSize(); // returns the flash chip size, in bytes, as seen by the SDK (may be less than actual size).
  int flashFrequency = ESP.getFlashChipSpeed(); // returns the flash chip frequency, in Hz.
  int flashID = ESP.getFlashChipId();// returns the flash chip ID as a 32-bit integer.




  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>Current Settings</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "  <h2>Network Confguration</h1>\n";
  message += "  <br>\n";
  message += "    ssid : " + String(settings.ssid) + "<br>\n";
  message += "    ssidPassword : " + String(settings.ssidPassword) + "<br>\n";
  message += "    ipMode : " + String(settings.ipMode) + " (0 = Dynamic; 1 = Static)<br>\n";
  message += "    ipAddress : " + String(settings.ipAddress[0]) + "." + String(settings.ipAddress[1]) + "." + String(settings.ipAddress[2]) + "." + String(settings.ipAddress[3]) + "<br>\n";
  message += "    ipGateway : " + String(settings.ipGateway[0]) + "." + String(settings.ipGateway[1]) + "." + String(settings.ipGateway[2]) + "." + String(settings.ipGateway[3]) + "<br>\n";
  message += "    ipSubnet : " + String(settings.ipSubnet[0]) + "." + String(settings.ipSubnet[1]) + "." + String(settings.ipSubnet[2]) + "." + String(settings.ipSubnet[3]) + "<br>\n";
  message += "  <br>\n";
  message += "  <h2>Flash Statistics</h1>\n";
  message += "    getFlashChipSize : " + String(flashSize) + "<br>\n";
  message += "    getFlashChipSpeed : " + String(flashFrequency / 1000000) + "Mhz<br>\n";
  message += "    getFlashChipId : " + String(flashID) + "<br>\n";
  message += "  <br>\n";
  message += "  <a href=/>Main Menu</a><br>\n";
  message += "  <br>\n";
  message += "  Firmware: 1.0.0 Alpha 02<br>\n";
  message += "  <br>\n";
  message += "</body>\n";
  message += "</html>\n";

  server.send( 200, "text/html", message );
}


void handleAdminFrameset () {
  String message = "\n\n";

  message += "<html>\n";
  message += "<frameset cols=\"120,100%\">\n";
  message += "<frame name=left src=\"/leftnav\" />\n";
  message += "<frame name=right src=\"about:blank\" />\n";
  message += "</frameset>\n";

  server.send( 200, "text/html", message );
}
