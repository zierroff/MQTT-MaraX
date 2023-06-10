#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>


WiFiClient WIFI_CLIENT;
//Define hardware connections 
//First number is GPIO 12 
//Second number is GPIO 13
//Third number is for inverted serial 
SoftwareSerial swSer(12, 13, 1);       

// MQTT
PubSubClient MQTT_CLIENT;

//Space for the serial Port 
const byte numChars = 32;
char receivedChars[numChars];
static byte ndx = 0;
char endMarker = '\n';
char rc;

//Names for the MQTT Server
char softwareVersion[32];
char targetSteamTemp[32];
char steamTemp[32];
char heatExchangeTemp[32];
char heatingMode[32];
char heatingElement[32];
char flag[32];


//Pin for the Pump
int BUTTON_PIN = 14;
long lastMsg = 0;
char msg[50];


void setup() {
  Serial.begin(9600);
  swSer.begin(9600);    

   // Enter here your SSID and Your Password for the Wifi
  WiFi.begin("Your SSID", "Your Password");

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
  }

}

// This function connects to the MQTT broker
void reconnect() {
  // Set our MQTT broker address and port
  MQTT_CLIENT.setServer("192.168.3.21", 1883);
  MQTT_CLIENT.setClient(WIFI_CLIENT);

  while (!MQTT_CLIENT.connected()) {
 //   Serial.println("Attempt to connect to MQTT broker");
    MQTT_CLIENT.connect("<your_random_device_client_id>");

    // Wait some time to space out connection requests
    delay(3000);
  }

//  Serial.println("MQTT connected");
}


//Get the Machine Input
void getMachineInput() {
  while (swSer.available() ) {
    rc = swSer.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';
      ndx = 0;
    }
  }
  // Split the Machine Input for the MQTT
strcpy(softwareVersion,receivedChars);
softwareVersion[5] = '\0';
strcpy(steamTemp,receivedChars+6);
steamTemp[3] = '\0';
strcpy(targetSteamTemp,receivedChars+10);
targetSteamTemp[3] = '\0';
strcpy(heatExchangeTemp,receivedChars+14);
heatExchangeTemp[3] = '\0';
strcpy(heatingMode,receivedChars+18);
heatingMode[4] = '\0';
strcpy(heatingElement,receivedChars+23);
heatingElement[1] = '\0';
strcpy(flag,receivedChars+25);
flag[1] = '\0';

}

// Loop this and send to MQTT
void loop() {
//   Check if we're connected to the MQTT broker
  if (!MQTT_CLIENT.connected()) {
 //    If we're not, attempt to reconnect
    reconnect();
  }

getMachineInput();

long now = millis();
int status;
  if (now - lastMsg > 100) {
     lastMsg = now;
     status=digitalRead(BUTTON_PIN);
     String msg="";
     if(status==HIGH )
     {
      msg= "1";
       char message[58];
       msg.toCharArray(message,58);
       //publish sensor data to MQTT broker
      MQTT_CLIENT.publish("coffee/softwareVersion", softwareVersion);
      MQTT_CLIENT.publish("coffee/steamTemp", steamTemp);
      MQTT_CLIENT.publish("coffee/targetSteamTemp", targetSteamTemp);
      MQTT_CLIENT.publish("coffee/heatExchangeTemp", heatExchangeTemp);
      MQTT_CLIENT.publish("coffee/heatingMode", heatingMode);
      MQTT_CLIENT.publish("coffee/heatingElement", heatingElement);
      MQTT_CLIENT.publish("coffee/flag", flag);
      MQTT_CLIENT.publish("coffee/pump", message);
       }
     else
     {
      msg= "0";
       char message[58];
       msg.toCharArray(message,58);
       //publish sensor data to MQTT broker
      MQTT_CLIENT.publish("coffee/softwareVersion", softwareVersion);
      MQTT_CLIENT.publish("coffee/steamTemp", steamTemp);
      MQTT_CLIENT.publish("coffee/targetSteamTemp", targetSteamTemp); 
      MQTT_CLIENT.publish("coffee/heatExchangeTemp", heatExchangeTemp);
      MQTT_CLIENT.publish("coffee/heatingMode", heatingMode);
      MQTT_CLIENT.publish("coffee/heatingElement", heatingElement);
      MQTT_CLIENT.publish("coffee/flag", flag);
      MQTT_CLIENT.publish("coffee/pump", message);
     }
    }


   }


