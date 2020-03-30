/* IoT ZM1350 Display, 18 March 2020 ESP32 FEATHER
 * mahdi07@msn.com (404)771-3315 
 * mahdialhusseini.com 
 * 
 * This source code is for an ESP32 and customized ZM1350 eight-panaplex display, with the corresponding html/php/CSS/SQL/JS/XML code
 * 
 * notes:
 * note that Serial is being reserved for wireless transmission to hardware. set diagnosisFlag to true to troubleshoot in Serial Monitor
 * BAUD rate of 9600 critical to interface with PIC direct-drivers firmware
 * If you enter INFINITE SCROLL mode, the only way to exist is by submitting a new request that is NOT INFINITE SCROLL. From then, the default will reengage
 *  */

/* library information*/
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <SyRenSimplified.h>

/* WiFi information*/
/*
const char* ssid = "Boldly Going";  // Enter SSID here
const char* password = "generalgeorge";  //Enter Password here

/* initializing and defining global variables */
String instance;
String formatted;

#define RXD2 16
#define TXD2 17

bool infiniteScroll = true; 
bool defaultFlag = true;
bool diagnosisFlag = true;

char* submission = "DUSTOFF";
char* style = "static";
char* rate = "fast";
char* uniqueID = "0";
char uniqueRes[] = "0";

// default conditions
char* defaultSubmission = "DUSTOFF";
char* defaultStyle = "static";
char* defaultRate = "fast";

// root certificate specific to mahdial-husseini.com
static const char root_ca[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/
MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT
DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow
PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD
Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB
AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O
rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq
OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b
xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw
7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD
aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV
HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG
SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69
ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr
AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz
R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5
JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo
Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ
-----END CERTIFICATE-----
)EOF";

void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.println("$B7F0<cr>");
  Serial2.println("$B7E0<cr>");
  Serial2.println("$B7S0<cr>");
  Serial2.println("$B7MA<cr>");
  
  Serial.begin(9600);
  delay(1000);

  connectToNetwork();
  establishOTA();
}
 
void loop() {
  ArduinoOTA.handle();
 
  if ((WiFi.status() == WL_CONNECTED)) {
 
    HTTPClient http;
 
    http.begin("https://www.mahdial-husseini.com/ZM1350-view.php", root_ca); //Specify the URL and certificate
    http.addHeader("Content-Type", "text/plain");             //Specify content-type header
    int httpCode = http.POST("POSTING from ESP32");                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();

      // parse time
      char * pch;                     // pointer to tokens        
      char copy[300];
      int counter = 0;
      
      payload.toCharArray(copy, 300);
      pch = strtok (copy,"|");         // get first token
      
      while (pch != NULL)
        {
        if (counter == 1) {
          submission = pch;
        }
        else if (counter == 2) {
          style = pch;
        }
        else if (counter == 3) {
          uniqueID = pch;
        }
        else if (counter == 4) {
          rate = pch;
        }
        
        pch = strtok (NULL, "|");     // get next token
        counter++;
       }  

       if (diagnosisFlag) {
          Serial.println();
          Serial.print("submission found: ");
          Serial.println(submission);
          Serial.print("style found: ");
          Serial.println(style);
          Serial.print("ID found: ");
          Serial.println(uniqueID);
          Serial.print("rate found: ");
          Serial.println(rate);
          Serial.print("httpCode: ");
          Serial.println(httpCode);
       }
    }
 
    else {
      if (diagnosisFlag) {
        Serial.println("Error on HTTP request");
      }
    }
 
    http.end(); //Free the resources
  }

  // if new, original request (as determined by request ID)
  Serial.println(uniqueRes);
  Serial.println(uniqueID);
  
  if(strcmp(uniqueRes, uniqueID) != 0) {
    Serial.println(">> New Original Request Recieved! <<");
    defaultFlag = false;
    textSubmission(submission, style, rate);   
  } else if (infiniteScroll == false) {
    defaultFlag = true;
    textSubmission(defaultSubmission, defaultStyle, defaultRate);
  }

  strcpy (uniqueRes, uniqueID); // reset ID for following iterations
  
  if (infiniteScroll == true and defaultFlag == false){
    // infinite scroll not a publicly available option! restrict appropriately
    scroll(submission, rate);
  }
 
  delay(1000);
}


void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();

  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
 
  }
}

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void connectToNetwork() {
  if (diagnosisFlag) {
    // scanNetworks(); // optional
    Serial.print("Connecting to WiFi..");
  }

  WiFi.begin(ssid, password); 
  // WiFi.mode(WIFI_STA);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    if (diagnosisFlag) {
      Serial.print(".");
    }
  }

  if (diagnosisFlag) {
    Serial.println("Connected to the WiFi network");
  }
}

void establishOTA() {
  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      // Serial.println("Start updating " + type);
    });
    
    if (diagnosisFlag) {
      ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      }); 
    }

  ArduinoOTA.begin();

  if (diagnosisFlag) {
    Serial.println("OTA Up and Running");
  }
}

/* takes text parsed from server-side html and submits to ZM1350s. utilizes String object; don't @ me */
void textSubmission(char* text, char* style, char* rate) {
  if (strcmp(style, "scroll") == 0) {
    infiniteScroll = false;
    scroll(text, rate);
  }
  else if (strcmp(style, "static") == 0){
    infiniteScroll = false;
    String malleable = text; // conversion to String object for static text
    
    // clear out buffer first, initialize formatted, if default flag is false (otherwise consecutive similar requests will blink)
    if (defaultFlag == false) {
      formatted = "$B7M        <cr>";
      Serial2.println(formatted); 
    }

    malleable.toUpperCase();
    formatted = "$B7M" + malleable + "<cr>";
    Serial2.println(formatted); 
    if (defaultFlag == false) {
      delay(5000); // allow static requests (not the default) to stick around for at least five seconds
    }
  }
  // if infiniteScroll, don't scroll here
  else if (strcmp(style, "infiniteScroll") == 0){
    infiniteScroll = true;
  }
}

/* Scroll text across ZM1350s. utilizes String object; don't @ me */
void scroll(char* text, char* rate) {
  // transform data character array to String object for formatting and submission
  String malleable = text;
  // Uppercase the input string
  malleable = "       " + malleable + "       ";
  malleable.toUpperCase();
  
  for (int x = 0; x < malleable.length() - 6; x++) {
    instance = malleable.substring(x, x+7);
    formatted = "$B7M" + instance + "<cr>";
    Serial2.println(formatted); // submit properly formatted request to hardware
    
    // Adjust delay speed for fast or slow scroll
    if (strcmp(rate, "slow") == 0){
      delay(700);
    } 
    else if (strcmp(rate, "fast") == 0){
      delay(500);
    }
    else if (strcmp(rate, "ultrafast") == 0){
      delay(300);
    }
  }
}
