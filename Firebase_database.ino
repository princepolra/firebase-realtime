//ArduinoJson 5.13.5

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "" //change with your host
#define FIREBASE_AUTH "" //change with your auth token
#define WIFI_SSID "" //change with your SSID
#define WIFI_PASSWORD "" ////change with your password

FirebaseData firebaseData;


WiFiClient client;

const char* host = "www.google.com";
const int httpPort = 80;
bool hasInternet = false;

void setup() {
  Serial.begin(115200);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt(firebaseData,"/Connected",0);
  Firebase.reconnectWiFi(true);
}
int p0 = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int connectionStatus = 0; 
void loop() {
  
  if (client.connect(host, httpPort)) {
   Serial.println("Connection success!!!");
   hasInternet=true;
   connectionStatus = 1;
     }


        if (connectionStatus == 1) 
        {
          delay(5000);
            Firebase.setInt(firebaseData,"/Connected",1);
            Serial.print("Connected to Internet: ");
            Serial.println(connectionStatus);
        }
        else
        {
          Firebase.setInt(firebaseData,"/Connected",0);
            Serial.print("Not connected to Internet : ");
            Serial.println(connectionStatus);
        }

  
 if(Firebase.getInt(firebaseData,"/D0_STATUS"))
 {
  p0 = firebaseData.intData();
        if (p0 == 1) 
        {
            Serial.print("DEVICE 1 ON : ");
            Serial.println(p0);
            digitalWrite(D0,LOW);  
        }
        else
        {
            Serial.print("DEVICE 1 OFF: ");
            Serial.println(p0);
            digitalWrite(D0,HIGH);  
        }
 } 

if(Firebase.getInt(firebaseData,"/D1_STATUS"))
 {
  p1 = firebaseData.intData();
        if (p1 == 1) 
        {
            Serial.print("DEVICE 2 ON : ");
            Serial.println(p1);
            digitalWrite(D1,LOW);  
        }
        else
        {
            Serial.print("DEVICE 2 OFF: ");
            Serial.println(p1);
            digitalWrite(D1,HIGH);  
        }
 } 

 if(Firebase.getInt(firebaseData,"/D2_STATUS"))
 {
  p2 = firebaseData.intData();
        if (p2 == 1) 
        {
            Serial.print("DEVICE 3 ON : ");
            Serial.println(p2);
            digitalWrite(D2,LOW);  
        }
        else
        {
            Serial.print("DEVICE 3 OFF: ");
            Serial.println(p2);
            digitalWrite(D2,HIGH);  
        }
 } 

 if(Firebase.getInt(firebaseData,"/D3_STATUS"))
 {
  p3 = firebaseData.intData();
        if (p3 == 1) 
        {
            Serial.print("DEVICE 4 ON : ");
            Serial.println(p3);
            digitalWrite(D3,LOW);  
        }
        else
        {
            Serial.print("DEVICE 4 OFF: ");
            Serial.println(p3);
            digitalWrite(D3,HIGH);  
        }
 } 
 
 else
 {
        Serial.println(firebaseData.errorReason());
 }
}
