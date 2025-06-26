/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <string.h>
#include <WiFiClientSecureBearSSL.h>

#define ONE_SECOND 1000
const char fingerprint_sni_cloudflaressl_com [] PROGMEM = "5D ED 5B 16 EA F6 52 87 A1 F2 6D 3B 45 C3 65 C2 1B 0A 4B 59";

enum Estados_Temoestato { _IDLE_ ,_INITIALIZATE_, _GET_TOKEN_, _GET_TEMPERATURE_ , _GET_CURRENT_TIME_ , _TAKE_DECISION_,_SPENDING_TIME_};
enum Estados_Temoestato { _IDLE_ ,_INITIALIZATE_, _GET_TOKEN_, _GET_TEMPERATURE_ , _GET_CURRENT_TIME_ , _TAKE_DECISION_,_SPENDING_TIME_};

Estados_Temoestato estado_termostato = _IDLE_;
const char login_meteomatics [] PROGMEM = "bXljb19hY29zdGFfY2FybG9zOktDQlR1NTA5eXY=";
//String login_meteomatics = "bXljb19hY29zdGFfY2FybG9zOktDQlR1NTA5eXY=";


ESP8266WiFiMulti WiFiMulti;

#ifndef STASSID
#define STASSID "acosta 2.4"
//#define STASSID "acosta 5.8"
#define STAPSK "casatonta01"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
int ledStatus = HIGH;
double temperature;
String currentTime;
String token;

void setup() {
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}


int printJsonKey(String *jsonString, String keyValue, String &returnValue){
  JSONVar myObject = JSON.parse(*jsonString);
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return 0;
  }
  JSONVar value = myObject[keyValue];
  Serial.println(value);
  returnValue = (String)value;
  return 1;
}

void printJson(String *jsonString){
  JSONVar myObject = JSON.parse(*jsonString);
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  
  JSONVar keys = myObject.keys();

  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObject[keys[i]];

    Serial.print("JSON.typeof(myObject[");
    Serial.print(keys[i]);
    Serial.print("]) = ");
    Serial.println(value);
  }

}

int getCurrentTime(String *time) {
    WiFiClient client;
    int result = 0;
    //String time = "";

    HTTPClient http;    
    if (http.begin(client,"http://worldtimeapi.org/api/timezone/America/Argentina/Salta")) {  // HTTP

      Serial.print("[HTTP] GET TIME...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          String bulkTime ="";
          if(printJsonKey(&payload, "datetime",bulkTime))
            result = 1;
          // "datetime":"2024-08-03T01:02:59.316944-03:00"
                       //2024-08-02T05:03:15Z
          *time = bulkTime.substring(0, 19);
          *time += "Z";
          Serial.println(*time);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
    return result;
}


int getData(String *_time, String *token, String *returnValue) {
  int result = 0;
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  client->setFingerprint(fingerprint_sni_cloudflaressl_com);
  // Or, if you happy to ignore the SSL certificate, then use the following line instead:

  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
  String url = "/";
  url += *_time;
  url += "/t_2m:C/-34.396944,-58.694444/json?access_token=";
  url += *token;
  if (https.begin(*client, "api.meteomatics.com",443,url,true)) {  // HTTP
    Serial.print("[HTTPS] GET TEMPERATURE...\n");
    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        *returnValue = https.getString();
        result =1;
        Serial.println(*returnValue);
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s [%d]\n", https.errorToString(httpCode).c_str(),httpCode);
    }

    https.end();
  }
  return result;
}
  
int getTemperatureField(String &data, int &result){
  JSONVar myObject = JSON.parse(data);
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return 0;
  }
  JSONVar resultJSONVar = myObject["data"];
  JSONVar myObject1 = resultJSONVar[0];
  resultJSONVar = myObject1["coordinates"];
  JSONVar myObject2 = resultJSONVar[0];
  JSONVar resultJSONVar2 = myObject2["dates"];
  myObject1 = resultJSONVar2[0];
  Serial.println("Extracting value");
  Serial.println(myObject1);
  result = myObject1["value"];
  Serial.println(result);
  return 1;

}

int getTemperature(String *_time, String *token , double *returnValue) {
  String result="";
  if (!getData(_time, token,&result)){
    return 0;
  }
  double temperature = 0;
  getTemperatureField(result,temperature);
  if (result == 1)
    returnValue = temperature;
  Serial.println(returnValue);
  return 1;
}

int getToken(String *token) {
  int result= 0;
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  client->setFingerprint(fingerprint_sni_cloudflaressl_com);
  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
  Serial.print("[HTTPS] headers OK.....\n");
  if (https.begin(*client, "login.meteomatics.com",443,"/api/v1/token",true)) {  // HTTP
  
    String kvalue = "Basic ";
    kvalue += login_meteomatics;
    Serial.print("[HTTPS] begin.....\n");
    https.addHeader("Authorization", kvalue);
  
    Serial.print("[HTTPS] GET TOKEN...\n");
    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
        //JSONVar myObject = JSON.parse(payload);
        String returnValue;
        if (printJsonKey(&payload, "access_token", returnValue))
        {
          *token = returnValue;
          result = 1;
        }
        Serial.println(returnValue);
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s [%d]\n", https.errorToString(httpCode).c_str(),httpCode);
    }
    https.end();
  }
  return result;
}

vpod evaluateTemperature(double temperature){
  if (temperature > 16){
    
  } else  if (temperature > 10){
    
  } else  if (temperature > 5){

  } else {

  }
}

void stateMachine(){
  int result ;
  String returnValue ;
  if ((WiFiMulti.run() != WL_CONNECTED)) {
    estado_termostato = _INITIALIZATE_;
    Serial.println("Wait 10s before next round...");
    delay(ONE_SECOND * 10);
  }
  switch (estado_termostato)
  {
    case _INITIALIZATE_:
      Serial.printf("_INITIALIZATE_\n");
      setup();
      estado_termostato = _IDLE_;
      break;
    case _IDLE_:
      Serial.printf("_IDLE_\n");
      if ((WiFiMulti.run() == WL_CONNECTED)) {
        estado_termostato = _GET_TOKEN_;
      }
      else {
        estado_termostato = _TAKE_DECISION_;
      }
      break;
    case _GET_TOKEN_:
      Serial.printf("_GET_TOKEN_\n");
      if (getToken(&returnValue)){
        token = returnValue;
        estado_termostato = _GET_CURRENT_TIME_;
      }
      break;
    case _GET_CURRENT_TIME_:
      Serial.printf("_GET_CURRENT_TIME_\n");
      estado_termostato = _GET_TEMPERATURE_;
      if (getCurrentTime(&returnValue)){
        currentTime = returnValue;   
      }
      break;
    case _GET_TEMPERATURE_:
      Serial.printf("_GET_TEMPERATURE_\n");
      estado_termostato = _TAKE_DECISION_;
      double returnTemperature=0.0;
      if (getTemperature(&currentTime,&token,&returnTemperature)){
        temperature = returnTemperature;
      }
      else{
        estado_termostato = _GET_TOKEN_;
        delay(ONE_SECOND * 120);
      }
      break;
    case  _TAKE_DECISION_:
      Serial.printf("_TAKE_DECISION_\n");
      evaluateTemperature(temperature);
      estado_termostato = _SPENDING_TIME_;
      break;
    case  _SPENDING_TIME_:
      Serial.printf("_SPENDING_TIME_\n");
      estado_termostato = _GET_CURRENT_TIME_;
      delay(ONE_SECOND * 120);
      break;
    default:
      estado_termostato = _IDLE_;
  }
  delay(ONE_SECOND * 30);
}

void loop() {
  
  digitalWrite(5, ledStatus);  // Turn the LED off by making the voltage HIGH
  digitalWrite(4, ledStatus);  // Turn the LED off by making the voltage HIGH
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    stateMachine();
  } 
  else {
    Serial.println("Wait 10s before next round...");
    delay(ONE_SECOND * 10);
  }
    
}
