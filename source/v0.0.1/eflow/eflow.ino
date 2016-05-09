
/***************************************************
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include <PID_v1.h>
#include "Jm_MAX31855.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <EEPROM.h>
#include "EEPROMAnything.h"

// Configuration Start

// These buttons are exposed on the nodemcu dev board
const int key_user = 16; // What can we do with this button?
const int key_flash = 0; // If pressed within 5 seconds of power on, enter admin mode
// End Pin Assignment


// This structure should not grow larger than 1024 bytes.
struct settings_t
{
  uint8_t initialized;       // If not "1", then we have not yet initialized with defaults
  char ssid[33];         // One more byte than required; String needs to be null terminated
  char ssidPassword[65]; // One more byte than required; String needs to be null terminated
  uint8_t ipMode; // 0 = Dynamic, 1 = Static
  uint8_t ipAddress[4]; // 255.255.255.255
  uint8_t ipGateway[4]; // 255.255.255.255
  uint8_t ipSubnet[4];  // 255.255.255.255
} settings;

int requestTTL = 120;

const byte DNS_PORT = 53;
ESP8266WebServer server ( 80 );
DNSServer dnsServer;

boolean deviceAdmin = 0;

// Define the LED state for ledHTTP
//   This is used for blinking the LED with a non-blocking method
boolean ledHTTPState = LOW;
unsigned long    ledHTTPStateMills = 0;
long    ledHTTPStateInterval = 250; // How fast to blink the LED

unsigned long secretRandNumber; // We will generate a new secret on startup.



// Pins for thermocouples
#define DO         4
#define CS_A       12
#define CS_B       14
#define CLK        5

#define SSR_OUTPUT 13

Jm_MAX31855 thermocouple_A(CLK, CS_A, DO);
Jm_MAX31855 thermocouple_B(CLK, CS_B, DO);

const int numReadings = 5;
int readIndex_A = 0;                // the index of the current reading
int readIndex_B = 0;                // the index of the current reading

//Input: The variable we're trying to control (double)
//Output: The variable that will be adjusted by the pid (double)
//Setpoint: The value we want to Input to maintain (double)
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
//double Kp = 300, Ki = 0.05, Kd = 20;
//double Kp = 100, Ki = 0.01, Kd = 0;
//double Kp = 30.0, Ki = 0.1, Kd = 14; // This works. There's some overshoot, but it works.
double Kp = 40.0, Ki = 0.01, Kd = 5;

double Kp_agressive = 999.0, Ki_agressive = 0.01, Kd_agressive = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

uint16_t startup_sec = 90; // Default 90
uint16_t startup_temp = 80;



int WindowSize = 1000; //
unsigned long windowStartTime;


float readings_A[numReadings];      // the readings from the analog input
float readings_B[numReadings];      // the readings from the analog input

float sensorA = 0;
float sensorB = 0;

float sensorTemperature = 0;

unsigned long previousMillis1000 = 0;
unsigned long previousMillis100 = 0;

bool heaterDuty[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int8_t heaterDutyIndex = -1;

/*
 * 0 = Nothing going on
 * 1 = Init
 * 2 = In progress
 */
uint8_t processEnable = 0;

uint16_t safeTemperature = 50; // Don't allow oven to be enabled unless it first cools to this temperature

struct reflowStatsProfile_t
{
  uint16_t sensorA;  // Reserved
  uint16_t sensorB;   // Reserved
  uint16_t Setpoint;   // Reserved
  uint16_t time;   // Reserved
  uint16_t reflowTime;   // Time since start of reflow process
};

const uint16_t reflowStatsProfileLength = 500;
struct reflowStats_t
{
  uint8_t run; // 0 = Unexecuted, 1 = Completed, 2, In Progress, 3 = Aborted, 4 = Abnormal Error
  uint8_t reflowProfilePrevious; // What reflow profile was selected?
  uint8_t reflowProfileNext; // What reflow profile is selected?
  reflowStatsProfile_t profile[reflowStatsProfileLength]; // 900 positions to save up to 1200 seconds (15 minutes). uInt for each temerature sensor, Input and Setpoint.
} ;

reflowStats_t reflowStats;

const uint8_t reflowProfileNameLength = 50;

struct reflowProfile_t
{
  char name[reflowProfileNameLength];                 // Name of profile
  uint16_t sort;                 // Sort index
  uint16_t profileRamp[2];       // Time / Temperature
  uint16_t profilePreheat[2];    // Time / Temperature
  uint16_t profileRampToPeak[2]; // Time / Temperature
  uint16_t profileReflow[2];     // Time / Temperature
  uint16_t profileCooling[2];    // Time / Temperature
  uint16_t profileFinishing[2];  // Time / Temperature -- Ramp down to temperature that would be safe to touch the board.
};

reflowProfile_t reflowProfile[4];

String systemMessage = "";

void setup() {

  Serial.begin(115200);

  EEPROM.begin(1024); // 512 bytes should be more than enough (famous last words)
  loadSettings();

  pinMode( SSR_OUTPUT, OUTPUT);
  pinMode( key_flash, INPUT_PULLUP );

  //-- Start PID Setup
  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 1;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);
  //-- END PID Setup

  //turn the PID on
  myPID.SetMode(AUTOMATIC);


  delay(5000);
  // Set deviceAdmin to one if key_flash is depressed. Otherwise, use defaults.
  if (digitalRead( key_flash ) == 0) {
    deviceAdmin = 1;
    pinMode( key_flash, OUTPUT );
  } else {
    pinMode( key_flash, OUTPUT );
  }

  
  if (deviceAdmin) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("eflow_admin", "eflow_admin");
    //WiFi.mode(WIFI_AP);
    WiFi.config ( IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0)) ;
    delay(10);

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));

    //WiFi.printDiag(Serial);
    Serial.println ( "Entering admin mode." );

    Serial.print ( "IP address: " );
    Serial.println ( WiFi.softAPIP() );
    printAPMacAddress();

    if ( MDNS.begin ( "eflow" ) ) {
      Serial.println ( "MDNS responder started" );
    }

    // We are using the amount of time required to connect to the AP as the seed to a random number generator.
    //   We should look for other ways to improve the seed. This should be "good enough" for now.

    server.on ( "/", handleAdminFrameset );
    server.on ( "/leftnav", handleAdminNav );
    server.on ( "/conf/wifi", handleAdminConfWifi );
    server.on ( "/conf/network", handleAdminConfNetwork );
    server.on ( "/conf/accounts", handleAdminConfAccounts );
    server.on ( "/conf/sensors", handleAdminConfSensors );
    server.on ( "/system/defaults", handleAdminDefaults );
    server.on ( "/system/settings", handleAdminSettings );
    server.on ( "/system/restart", handleAdminRestart);
    server.on ( "/system/apply", handleAdminApply);
    server.on ( "/eflow.css", handleCSS);

    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );

  } else {

    Serial.print("Connecting to SSID : ");
    Serial.println (settings.ssid);
    
    WiFi.begin ( settings.ssid, settings.ssidPassword );
    WiFi.mode ( WIFI_STA );



    // Documentation says this is supposed to come before WiFi.begin, but when it is there -- it doesn't work. WHY?!?!?!
    if (settings.ipMode == 1) { // 0 = Dynamic, 1 = Static
      WiFi.config ( settings.ipAddress, settings.ipGateway, settings.ipSubnet) ;
    }

    //Serial.println ( "" );

    //EEPROM_readAnything(0, settings);

    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    //digitalWrite ( ledCONNECTED, 1 );

    WiFi.printDiag(Serial);

    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
    printMacAddress();

    if ( MDNS.begin ( "eflow" ) ) {
      Serial.println ( "MDNS responder started" );
    }

    // We are using the amount of time required to connect to the AP as the seed to a random number generator.
    //   We should look for other ways to improve the seed. This should be "good enough" for now.
    randomSeed(micros());
    secretRandNumber = random(2147483646); // Full range of long 2147483647
    Serial.println("Secret: " + String(secretRandNumber));

    //server.on ( "/", handleRoot );
    server.on ( "/", handleReflowFrameset );
    server.on ( "/topnav", handleReflowNav );
    server.on ( "/process/start", handleProcessStart );
    server.on ( "/process/stop", handleProcessStop );
    server.on ( "/process/conf", handleProcessConfigure );
    server.on ( "/process/conf/save/global", handleProcessConfigureSaveGlobal );
    server.on ( "/process/chart", handleReflowChart );
    server.on ( "/process/data.csv", handleProcessData );
    server.on ( "/restart", handleSystemRestart );
    
    server.on ( "/externalScript.js", handleExternalScriptJS );
    server.on ( "/json/sensors", handleJSONSensors );
    server.on ( "/eflow.css", handleCSS);
    server.on ( "/blank.html", handleBlank);

    server.onNotFound ( handleNotFound );
    server.begin();
    Serial.println ( "HTTP server started" );
  }

}

void handleRoot2() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void loop() {

  updateSensors();

  // Call the timer dispatchers
  dispatchers();

  
  //processGo();

  // Start Pid Control
  Input = (sensorA + sensorB) / 2;

  myPID.Compute();

  // Handle TCP Server
  server.handleClient();
  dnsServer.processNextRequest();

  
  //delay(1);





}

void dispatchers ( void ) {
  // Call dispatchSecond once a second
  unsigned long currentMillis1000 = millis();
  if (currentMillis1000 - previousMillis1000 >= 1000) {
    previousMillis1000 = currentMillis1000;

    dispatchSecond();
    dispatchProcessPerSecond();
  }

  // Call dispatch100ms every 100ms (1/10 sec)
  unsigned long currentMillis100 = millis();
  if (currentMillis100 - previousMillis100 >= 100) {
    previousMillis100 = currentMillis100;

    dispatch100ms();
  }
}



void dispatchSecond( void ) {
  // We may use this for debug output

}



