
//char tempArray[5000];

void handleExternalScriptJS() {
  digitalWrite ( ledHTTP, 1 );


  String externJavascriptString = F("\n"
                                  "function validateForm () { \n"
                                  "  var x = document.forms['myForm']['password'].value;\n"
                                  "  if (x == null || x == '') {\n"
                                  "      alert('Password must be filled');\n"
                                  "      return false;\n"
                                  "  }\n"
                                  "  var requestPassword = CryptoJS.SHA1(document.forms['myForm']['password'].value + document.forms['myForm']['serverDigest'].value);\n"
                                  "  document.forms['myForm']['password'].value = '';\n"
                                  "  document.forms['myForm']['requestPassword'].value = requestPassword;\n"
                                  "  return true; \n"
                                  "}\n"
                                  "/*CryptoJS v3.1.2\n"
                                  "code.google.com/p/crypto-js\n"
                                  "(c) 2009-2013 by Jeff Mott. All rights reserved.\n"
                                  "code.google.com/p/crypto-js/wiki/License\n"
                                  "*/\n"
                                  "var CryptoJS=CryptoJS||function(e,m){var p={},j=p.lib={},l=function(){},f=j.Base={extend:function(a){l.prototype=this;var c=new l;a&&c.mixIn(a);c.hasOwnProperty(\"init\")||(c.init=function(){c.$super.init.apply(this,arguments)});c.init.prototype=c;c.$super=this;return c},create:function(){var a=this.extend();a.init.apply(a,arguments);return a},init:function(){},mixIn:function(a){for(var c in a)a.hasOwnProperty(c)&&(this[c]=a[c]);a.hasOwnProperty(\"toString\")&&(this.toString=a.toString)},clone:function(){return this.init.prototype.extend(this)}},\n"
                                  "n=j.WordArray=f.extend({init:function(a,c){a=this.words=a||[];this.sigBytes=c!=m?c:4*a.length},toString:function(a){return(a||h).stringify(this)},concat:function(a){var c=this.words,q=a.words,d=this.sigBytes;a=a.sigBytes;this.clamp();if(d%4)for(var b=0;b<a;b++)c[d+b>>>2]|=(q[b>>>2]>>>24-8*(b%4)&255)<<24-8*((d+b)%4);else if(65535<q.length)for(b=0;b<a;b+=4)c[d+b>>>2]=q[b>>>2];else c.push.apply(c,q);this.sigBytes+=a;return this},clamp:function(){var a=this.words,c=this.sigBytes;a[c>>>2]&=4294967295<<\n"
                                  "32-8*(c%4);a.length=e.ceil(c/4)},clone:function(){var a=f.clone.call(this);a.words=this.words.slice(0);return a},random:function(a){for(var c=[],b=0;b<a;b+=4)c.push(4294967296*e.random()|0);return new n.init(c,a)}}),b=p.enc={},h=b.Hex={stringify:function(a){var c=a.words;a=a.sigBytes;for(var b=[],d=0;d<a;d++){var f=c[d>>>2]>>>24-8*(d%4)&255;b.push((f>>>4).toString(16));b.push((f&15).toString(16))}return b.join(\"\")},parse:function(a){for(var c=a.length,b=[],d=0;d<c;d+=2)b[d>>>3]|=parseInt(a.substr(d,\n"
                                  "2),16)<<24-4*(d%8);return new n.init(b,c/2)}},g=b.Latin1={stringify:function(a){var c=a.words;a=a.sigBytes;for(var b=[],d=0;d<a;d++)b.push(String.fromCharCode(c[d>>>2]>>>24-8*(d%4)&255));return b.join(\"\")},parse:function(a){for(var c=a.length,b=[],d=0;d<c;d++)b[d>>>2]|=(a.charCodeAt(d)&255)<<24-8*(d%4);return new n.init(b,c)}},r=b.Utf8={stringify:function(a){try{return decodeURIComponent(escape(g.stringify(a)))}catch(c){throw Error(\"Malformed UTF-8 data\");}},parse:function(a){return g.parse(unescape(encodeURIComponent(a)))}},\n"
                                  "k=j.BufferedBlockAlgorithm=f.extend({reset:function(){this._data=new n.init;this._nDataBytes=0},_append:function(a){\"string\"==typeof a&&(a=r.parse(a));this._data.concat(a);this._nDataBytes+=a.sigBytes},_process:function(a){var c=this._data,b=c.words,d=c.sigBytes,f=this.blockSize,h=d/(4*f),h=a?e.ceil(h):e.max((h|0)-this._minBufferSize,0);a=h*f;d=e.min(4*a,d);if(a){for(var g=0;g<a;g+=f)this._doProcessBlock(b,g);g=b.splice(0,a);c.sigBytes-=d}return new n.init(g,d)},clone:function(){var a=f.clone.call(this);\n"
                                  "a._data=this._data.clone();return a},_minBufferSize:0});j.Hasher=k.extend({cfg:f.extend(),init:function(a){this.cfg=this.cfg.extend(a);this.reset()},reset:function(){k.reset.call(this);this._doReset()},update:function(a){this._append(a);this._process();return this},finalize:function(a){a&&this._append(a);return this._doFinalize()},blockSize:16,_createHelper:function(a){return function(c,b){return(new a.init(b)).finalize(c)}},_createHmacHelper:function(a){return function(b,f){return(new s.HMAC.init(a,\n"
                                  "f)).finalize(b)}}});var s=p.algo={};return p}(Math);\n"
                                  "(function(){var e=CryptoJS,m=e.lib,p=m.WordArray,j=m.Hasher,l=[],m=e.algo.SHA1=j.extend({_doReset:function(){this._hash=new p.init([1732584193,4023233417,2562383102,271733878,3285377520])},_doProcessBlock:function(f,n){for(var b=this._hash.words,h=b[0],g=b[1],e=b[2],k=b[3],j=b[4],a=0;80>a;a++){if(16>a)l[a]=f[n+a]|0;else{var c=l[a-3]^l[a-8]^l[a-14]^l[a-16];l[a]=c<<1|c>>>31}c=(h<<5|h>>>27)+j+l[a];c=20>a?c+((g&e|~g&k)+1518500249):40>a?c+((g^e^k)+1859775393):60>a?c+((g&e|g&k|e&k)-1894007588):c+((g^e^\n"
                                  "k)-899497514);j=k;k=e;e=g<<30|g>>>2;g=h;h=c}b[0]=b[0]+h|0;b[1]=b[1]+g|0;b[2]=b[2]+e|0;b[3]=b[3]+k|0;b[4]=b[4]+j|0},_doFinalize:function(){var f=this._data,e=f.words,b=8*this._nDataBytes,h=8*f.sigBytes;e[h>>>5]|=128<<24-h%32;e[(h+64>>>9<<4)+14]=Math.floor(b/4294967296);e[(h+64>>>9<<4)+15]=b;f.sigBytes=4*e.length;this._process();return this._hash},clone:function(){var e=j.clone.call(this);e._hash=this._hash.clone();return e}});e.SHA1=j._createHelper(m);e.HmacSHA1=j._createHmacHelper(m)})();");



  if (0) {
    // TODO: If we recieve a If-None-Match header and it matches the Etag we defined, then
    //       return a  HTTP 304 Not Modified header with no content.
    //       -- See: http://en.wikipedia.org/wiki/HTTP_ETag for protocol details
  } else {


    // Define header to encourage browsers to cache this page.
    server.sendHeader ( "ETag", "CacheThisForever", 0 );
    server.sendHeader ( "Expires", "Mon, 08 Jun 2035 00:19:36 GMT", 0 );
    server.sendHeader ( "Cache-Control", "public, max-age=31536000", 0 ); // 31536000 = 1 year
    server.send ( 200, "text/plain", externJavascriptString );
  }

  digitalWrite ( ledHTTP, 0 );
}



void handleRoot() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "Welcome to eFlow\n";

  server.send ( 200, "text/html", message );
  digitalWrite ( ledHTTP, 0 );

}


void handleProcessStart() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "<meta http-equiv=\"refresh\" content=\"1; url=/process/chart\">\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "Reflow process has been initiated... This page will refresh\n";

  server.send ( 200, "text/html", message );
  digitalWrite ( ledHTTP, 0 );
  systemMessage = "eFlow Initiated";

  processGo();

}


void handleProcessConfigure() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "<html xmlns='http://www.w3.org/1999/xhtml'>\n";
  message += "<head>\n";
  message += "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />\n";
  message += "<title>eFlow Process Configuration</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
/*
  message += "<form action='' method='post' name='form1' target='_self' id='form1'>\n";
  message += "  <h1>Configure Profile</h2>\n";
  message += "  <h2>Select Solder Compounde</h2>\n";
  message += "  <p>\n";
  message += "    <label for='select'></label>\n";
  message += "    <select name='select' size='4' id='select'>\n";
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
     message += "      <option value='1234' selected>" + String(reflowProfile[i].name) + "</option>\n";
     
    } else {
      message += "      <option value='1234'>" + String(reflowProfile[i].name) + "</option>\n";
    }
  }
  message += "    </select>\n";
  message += "  </p>\n";
  message += "  <h2>Modify Profile</h2>\n";
  message += "  <table width='100%' border='1' cellspacing='0' cellpadding='0'>\n";
  message += "    <tr>\n";
  message += "      <td align='center'>Initial Ramp</td>\n";
  message += "      <td align='center'>Pre Heat</td>\n";
  message += "      <td align='center'>Ramp to Peak</td>\n";
  message += "      <td align='center'>Reflow</td>\n";
  message += "      <td align='center'>Cooling</td>\n";
  message += "      <td align='center'>Finish</td>\n";
  message += "    </tr>\n";
  message += "    <tr>\n";
  message += "      <td><label for='ramp_sec'></label>\n";
  message += "      <input name='ramp_sec' type='text' id='ramp_sec' size='3' maxlength='3' />\n";
  message += "      Sec <input name='ramp_temp' type='text' id='ramp_temp' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "      <td><input name='pre_sec' type='text' id='pre_sec' size='3' maxlength='3' /> Sec\n";
  message += "  <input name='pre_temp' type='text' id='textfield4' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "      <td><input name='ramppeak_sec' type='text' id='textfield5' size='3' maxlength='3' /> Sec\n";
  message += "  <input name='ramppeak_temp' type='text' id='textfield6' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "      <td><input name='reflow_sec' type='text' id='textfield7' size='3' maxlength='3' /> Sec\n";
  message += "  <input name='reflow_temp' type='text' id='textfield8' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "      <td><input name='cool_sec' type='text' id='textfield9' size='3' maxlength='3' /> Sec\n";
  message += "  <input name='cool_temp' type='text' id='textfield10' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "      <td><input name='finish_sec' type='text' id='textfield11' size='3' maxlength='3' /> Sec\n";
  message += "  <input name='finish_temp' type='text' id='textfield12' size='3' maxlength='3' /> &deg;Celsius </td>\n";
  message += "    </tr>\n";
  message += "  </table>\n";
  message += "  <p>\n";
  message += "    Reset Form\n";
  message += "    <input type='reset' name='Reset' id='Reset' value='Reset' />\n";
//  message += "</p>\n";
  message += "  Save for this session\n";
  message += "    <input type='submit' name='Save' id='button' value='Save' />\n";
//  message += "  </p>\n";
  message += "  Save for as process defaults\n";
  message += "    <input type='submit' name='button' id='button2' value='Apply' />\n";
  message += "  </p>\n";
  message += "</form>\n";
*/

  message += "<form action='/process/conf/save/global' method='post' name='form1' target='_self' id='form1'>\n";
  message += "  <h1>Configure System</h2>\n";
  message += "  <h2>Set Global PID Values</h2>\n";
  message += "  <p>Kp\n";
  message += "    <input name='Kp' type='text' id='textfield13' size='5' maxlength='5' value='" + String(Kp) + "'/>\n";
  message += "  </p>\n";
  message += "  <p>Ki\n";
  message += "    <input name='Ki' type='text' id='textfield16' size='5' maxlength='5' value='" + String(Ki) + "'/>\n";
  message += "  </p>\n";
  message += "  <p>Kd\n";
  message += "    <input name='Kd' type='text' id='textfield14' size='5' maxlength='5' value='" + String(Kd) + "'/>\n";
  message += "  </p>\n";
  message += "  <p>For more information, see the Wikipedia article on <a href='https://en.wikipedia.org/wiki/PID_controller' target='new'>PID Controller</a>.</p>\n";
  message += "  <h2>Set Oven Start Point</h2>\n";
  message += "  <p>\n";
  message += "    <input name='startup_sec' type='text' id='textfield15' size='3' maxlength='3' value=" + String(startup_sec) + " /> Sec\n";
  message += "<input name='startup_temp' type='text' id='textfield17' size='3' maxlength='3' value=" + String(startup_temp) + " />\n";
  message += "&deg;Celsius </p>\n";
  message += "  <p>Before beginning the reflow profile, heat the oven to a known start point and maintain it for a few seconds. This allows you to monitor the oven's performance prior to extreme temepratures. If the oven is unable to maintain the start temperature, the process will be aborted.</p>\n";
//  message += "  <hr />\n";
  message += "  <h2>Safe Temperature</h2>\n";
  message += "  <p>\n";
  message += "    <input name='safeTemperature' type='text' id='textfield15' size='3' maxlength='3' value=" + String(safeTemperature) + " /> Sec\n";
  message += "  The reflow process can't be started unless the oven is below the safe temperature.<p>\n";
  message += "  <h2>Process Agressiveness</h2>\n";
  message += "  <p>\n";
  message += "    <input name='processAgressiveness' type='text' id='textfield15' size='3' maxlength='3' value=" + String(processAgressiveness) + " /> Sec\n";
  message += "  At the start of each zone in the reflow profile, be agressive for a few seconds to get close to the upcoming setpoint.<p>\n";
  message += "  <h2>Process Temperature Hysteresis</h2>\n";
  message += "  <p>\n";
  message += "    <input name='processTempHysteresis' type='text' id='textfield15' size='3' maxlength='3' value=" + String(processTempHysteresis) + " /> Sec\n";
  message += "  Temeprature range below set point to accept zone completion.<p>\n";
  message += "  <p>\n";
  message += "    Reset Form\n";
  message += "    <input type='reset' name='Reset' id='Reset' value='Reset' />\n";
  message += "\n";
  message += "  Save for this session\n";
  message += "    <input type='submit' name='Save' id='button' value='Save' />\n";
  message += "\n";
  message += "  Save for as process defaults (wip)\n";
  message += "    <input type='submit' name='button' id='button2' value='Apply' />\n";
  message += "  </p>\n";
  message += "</form>\n";
  
  message += "<form action='/process/conf/save/global' method='post' name='form1' target='_self' id='form1'>\n";
  message += "  <h1>Reboot</h2>\n";
  message += "  <a href=/restart>Reboot eFlow</a>\n";
  message += "</form>\n";

  message += "</body>\n";
  message += "</html>\n";


  server.send ( 200, "text/html", message );
  digitalWrite ( ledHTTP, 0 );

  //processGo();

}

void handleProcessConfigureSaveGlobal() {

  String inputKp = server.arg("Kp");
  String inputKi = server.arg("Ki");
  String inputKd = server.arg("Kd");
  String inputStartupSec = server.arg("startup_sec");
  String inputStartupTemp = server.arg("startup_temp");
  String inputProcessAgressiveness = server.arg("processAgressiveness");
  String inputProcessTempHysteresis = server.arg("processTempHysteresis");
  String inputSafeTemperature = server.arg("safeTemperature");

  Kp = inputKp.toFloat();
  Ki = inputKi.toFloat();
  Kd = inputKd.toFloat();

  startup_sec = inputStartupSec.toInt();
  startup_temp = inputStartupTemp.toInt();
  processTempHysteresis = inputProcessTempHysteresis.toInt();
  safeTemperature = inputSafeTemperature.toInt();

  String message = "";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "<meta http-equiv=\"refresh\" content=\"1; url=/process/conf\">\n";
  message += "Settings saved... This page will refresh\n";

  server.send ( 200, "text/html", message );
}

void handleProcessStop() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "<meta http-equiv=\"refresh\" content=\"1; url=/process/chart\">\n";
  message += "Process aborted... This page will refresh\n";

  server.send ( 200, "text/html", message );
  digitalWrite ( ledHTTP, 0 );

  systemMessage = "eFlow Aborted";

  processStop();
  digitalWrite ( ledHTTP, 0 );

}


void handleSystemRestart() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "<meta http-equiv=\"refresh\" content=\"10; url=/blank.html\">\n";
  message += "Rebooting... This page will refresh in 10 seconds\n";

  server.send ( 200, "text/html", message );

  processStop();

  delay(5000);
  digitalWrite ( ledHTTP, 0 );

  ESP.restart(); // For some reason the restart function isn't working.
  //while (1) { };   // Let's force the watchdog to restart eFlow.


}


void handleProcessData() {
  digitalWrite ( ledHTTP, 1 );

  String message = "";

  message += "\"Time\",\"Temperature\",\"Set Point\"\n";

  for (int i=0; i < reflowStatsProfileLength; i = i+2){
    
    float temperature = 0;
    

    if (reflowStats.profile[i].sensorA == 0 || reflowStats.profile[i].sensorB == 0) {
      temperature = 0; 
    } else {
      temperature = ( float(reflowStats.profile[i].sensorA + reflowStats.profile[i].sensorB) / 100 / 2 ) ;
    }
    
//    message += String(i) + "," + "," + String(reflowStats.profile[i].reflowTime) + "," + String(temperature) + "," + String(reflowStats.profile[i].Setpoint) + "\n";
    message += String(i) + "," + String(temperature) + "," + String(reflowStats.profile[i].Setpoint) + "\n";
  } 

//    reflowStats.profile[processTimer].time = processTimer;
//    reflowStats.profile[processTimer].sensorA= sensorA;
//    reflowStats.profile[processTimer].sensorB = sensorB;
//    reflowStats.profile[processTimer].Setpoint = Setpoint;

  server.send ( 200, "text/csv", message );
  digitalWrite ( ledHTTP, 0 );

}

void handleNotFound() {
  digitalWrite ( ledHTTP, 1 );

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }


  server.send ( 404, "text/plain", message );
  digitalWrite ( ledHTTP, 1 );
}

void handleCSS () {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += F("@charset \"UTF-8\";\n");
  message += F("body {\n");
  message += F("background-color: #FFFFCC;\n");
  message += F("font-family: Arial, Helvetica, sans-serif;\n");
  message += F("font-size: 12px;\n");
  message += F("line-height: 24px;\n");
  message += F("color: #333333;\n");
  message += F("}\n");
  message += F("td, th {\n");
  message += F("font-family: Arial, Helvetica, sans-serif;\n");
  message += F("font-size: 12px;\n");
  message += F("line-height: 24px;\n");
  message += F("color: #330000;\n");
  message += F("}\n");
  message += F("a {\n");
  message += F("color: #330000;\n");
  message += F("}\n");
  message += F("form {\n");
  message += F("background-color: #CCCC99;\n");
  message += F("}\n");
  message += F(".title {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 18px;\n");
  message += F("line-height: 30px;\n");
  message += F("background-color: #990000; color: #FFFF66;\n");
  message += F("}\n");
  message += F(".subtitle {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 16px;\n");
  message += F("line-height: 20px;\n");
  message += F("font-weight: bold;\n");
  message += F("color: #660000; font-style: oblique;\n");
  message += F("}\n");
  message += F(".header {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 24px;\n");
  message += F("background-color: #990000;\n");
  message += F("color: #FFFF66;\n");
  message += F("}\n");
  message += F(".nav {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 12px;\n");
  message += F("font-weight: bold;\n");
  message += F("background-color: #CCCC66;\n");
  message += F("}\n");
  message += F(".navLink {\n");
  message += F("font-family: Arial, Helvetica, sans-serif;\n");
  message += F("font-size: 14px;\n");
  message += F("font-weight: bold;\n");
  message += F("background-color: #DEDECA;\n");
  message += F("}\n");
  message += F("a:hover {\n");
  message += F("color: #DEDECA;\n");
  message += F("background-color: #330000;\n");
  message += F("}\n");
  message += F(".sidebar {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 12px;\n");
  message += F("line-height: 18px;\n");
  message += F("padding: 3px;\n");
  message += F("background-color: #FFFF99;\n");
  message += F("}\n");
  message += F(".sidebarHeader {\n");
  message += F("font-family: Georgia, \"Times New Roman\", Times, serif;\n");
  message += F("font-size: 14px;\n");
  message += F("line-height: 18px;\n");
  message += F("color: #FFFF99;\n");
  message += F("background-color: #999933;\n");
  message += F("font-weight: bold;\n");

  server.sendHeader ( "ETag", "CacheThisForever", 0 );
  server.sendHeader ( "Expires", "Mon, 08 Jun 2035 00:19:36 GMT", 0 );
  server.sendHeader ( "Cache-Control", "public, max-age=31536000", 0 ); // 31536000 = 1 year

  server.send ( 200, "text/css", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleReflowNav() {
  digitalWrite ( ledHTTP, 1 );

  String message = F("\n\n");
  message += F("<html>\n");
  message += F(" <head>\n");
  message += F("  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n");
  message += F("  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n");
  message += F("  <title>eFlow -- Main Menu</title>\n");
  message += F("  <link rel=\"stylesheet\" href=\"/eflow.css\">\n");
  message += F("</head>\n");
  message += F("<body>\n");

  message += F("  <table width='100%' height='100%' border='0' cellspacing='0' cellpadding='0'><tr><td width=200><font size=+3><b>eFlow v0.01</b></font></td><td align='center' valign='middle'>\n");
  message += F("  <font size=+3>\n");
  message += F("  <a href=/process/conf target=bottom>Setup</a> | \n");
  message += F("  <a href=/process/start target=bottom>Start</a> | \n");
  message += F("  <a href=/process/stop target=bottom>Abort</a> | \n");
  message += F("  <a href=/process/chart target=bottom>Monitor Progress</a> | \n");
  message += F("  <a href=/process/data.csv target=bottom>Raw Data</a>\n");
  
  message += F("  </font>\n");
  message += F("  </td></tr></table>\n");
  message += F("</body>\n");
  message += F("</html>\n");


  server.send( 200, "text/html", message );
  digitalWrite ( ledHTTP, 0 );
}


void handleBlank() {
  digitalWrite ( ledHTTP, 1 );

  String message = "\n\n";
  message += "<html>\n";
  message += " <head>\n";
  message += "  <meta name='viewport' content='initial-scale=1.5, user-scalable=no'>\n";
  message += "  <link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">\n";
  message += "  <title>eFlow</title>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";
  message += "</head>\n";
  message += "<body>\n";
  message += "<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>eFlow v0.0.1 (c) 2016 by Jm Casler\n";

  message += "</body>\n";
  message += "</html>\n";


  server.send( 200, "text/html", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleReflowFrameset () {
  digitalWrite ( ledHTTP, 1 );

  String message = "\n\n";

  message += "<html>\n";
  message += "<title>eFlow - Reflow Oven Web Interface</title>";
  message += "<meta name='apple-mobile-web-app-capable' content='yes' />";
  message += "<frameset rows=\"70,100%\">\n";
  message += "<frame name=top src=\"/topnav\" />\n";
  message += "<frame name=bottom src=\"/blank.html\" />\n";
  message += "</frameset>\n";

  server.send( 200, "text/html", message );

  digitalWrite ( ledHTTP, 0 );
}

void handleJSONSensors () {
  digitalWrite ( ledHTTP, 1 );

  String message = "";
  message += "{\n";
  message += "  \"data\" : {\n";
  message += "    \"sensorA\" : " + String(float(sensorA)) + ",\n";
  message += "    \"sensorB\" : " + String(float(sensorB)) + ",\n";
  message += "    \"processTimer\" : " + String(processTimer) + ",\n";
  message += "    \"processReflowTimer\" : " + String(processReflowTimer) + ",\n";
  message += "    \"Setpoint\" : " + String(Setpoint) + ",\n";
  message += "    \"Kp\" : " + String(Kp) + ",\n";
  message += "    \"Ki\" : " + String(Ki) + ",\n";
  message += "    \"Kd\" : " + String(Kd) + ",\n";
  message += "    \"systemMessage\" : \"" + String(systemMessage) + "\"\n";
  message += "  },\n";
  message += " \"status\" : \"ok\"\n";
  message += "}\n";

  server.send ( 200, "application/json", message );

  digitalWrite ( ledHTTP, 0 );

}

void handleReflowChart() {
  digitalWrite ( ledHTTP, 1 );

  String message = "\n\n";
  message += "<html>\n";
  message += "<head>\n";
  message += "<script src=\"http://cdnjs.cloudflare.com/ajax/libs/dygraph/1.1.1/dygraph-combined.js\"></script>\n";
  message += "  <link rel=\"stylesheet\" href=\"/eflow.css\">\n";

  message += "<script>\n";
  message += "function getJSON(){\n";
  message += "var xmlhttp;\n";
  message += "xmlhttp=((window.XMLHttpRequest)?new XMLHttpRequest():new ActiveXObject('Microsoft.XMLHTTP'));\n";
  message += "xmlhttp.onreadystatechange=function() {\n";
  message += "  if (xmlhttp.readyState==4 && xmlhttp.status==200) {\n";
  message += "    var res=xmlhttp.responseText;\n";
  message += "    res=JSON.parse(res);\n";
  message += "    if(res.status=='ok'){\n";
  message += "    document.chartForm.sensorA.value = res.data.sensorA;\n";
  message += "    document.chartForm.sensorB.value = res.data.sensorB;\n";
  message += "    document.chartForm.Setpoint.value = res.data.Setpoint;\n";
  message += "    document.chartForm.processTimer.value = res.data.processTimer;\n";
  message += "    document.chartForm.processReflowTimer.value = res.data.processReflowTimer;\n";
  message += "    document.chartForm.Kp.value = res.data.Kp;\n";
  message += "    document.chartForm.Ki.value = res.data.Ki;\n";
  message += "    document.chartForm.Kd.value = res.data.Kd;\n";
  message += "    document.chartForm.systemMessage.value = res.data.systemMessage;\n";
  message += "    }\n";
  message += "  }\n";
  message += "}\n";
  message += "xmlhttp.open('GET','/json/sensors',true);\n";
  message += "xmlhttp.send();\n";
  message += "}\n";
  message += "</script>\n";

  message += "</head>\n";
  message += "<body>\n";
  message += "<form action='' method='post' name='chartForm' target='_self' id='chartForm'>\n";
  message += "  SensorA  <input name='sensorA' type='text' id='textfield13' size='5' maxlength='5' value=''/>\n";
  message += "  SensorB  <input name='sensorB' type='text' id='textfield13' size='5' maxlength='5' value=''/>\n";
  message += "  Set Point  <input name='Setpoint' type='text' id='textfield13' size='3' maxlength='3' value=''/>\n";
  message += "  Process Timer  <input name='processTimer' type='text' id='textfield13' size='4' maxlength='4' value=''/>\n";
  message += "  Reflow Timer  <input name='processReflowTimer' type='text' id='textfield13' size='4' maxlength='4' value=''/><br>\n";
  message += "  Kp  <input name='Kp' type='text' id='textfield13' size='5' maxlength='5' value='" + String(Kp) + "'/>\n";
  message += "  Ki  <input name='Ki' type='text' id='textfield13' size='5' maxlength='5' value='" + String(Ki) + "'/>\n";
  message += "  Kd  <input name='Kd' type='text' id='textfield13' size='5' maxlength='5' value='" + String(Kd) + "'/>\n";
  message += "  Agressive Seconds  <input name='processAgressiveness' type='text' id='textfield13' size='2' maxlength='2' value='" + String(processAgressiveness) + "'/>\n";
  message += "  Hysteresis  <input name='processTempHysteresis' type='text' id='textfield13' size='1' maxlength='1' value='" + String(processTempHysteresis) + "'/><br>\n";
  message += "  System Message <input name='systemMessage' type='text' id='textfield13' size='70' maxlength='70' value='" + String(systemMessage) + "'/>\n";
  message += "</form>\n";
  message += "<table width=100%>\n";
  message += "<tr>\n";
  message += "<td align=center>\n";
  message += "  <div id=\"graph_terrarium\"\n";
  message += "    style=\"width:100%; height:300px;\"></div>\n";
  message += "</td>\n";
  message += "</tr>\n";
  message += "</table>\n";

  message += "<script type=\"text/javascript\">\n";
  message += "g1 = new Dygraph(\n";
  message += "document.getElementById(\"graph_terrarium\"),\n";
  message += "\"/process/data.csv\",\n";
  message += "{\n";
  message += "legend: 'always',\n";
  message += "}\n";
  message += ");\n";
  message += "\n";
  message += "setInterval(function() {\n";
  message += "g1.updateOptions( { 'file': '/process/data.csv' } );\n";
  message += "}, 2000);\n";
  message += "setInterval(function() {\n";
  message += "getJSON();\n";
  message += "}, 1000);\n";


  message += "</script>\n";

  message += "</body>\n";
  message += "</html>\n";
  server.send( 200, "text/html", message );

  digitalWrite ( ledHTTP, 0 );
  
}

