#include <SPI.h>
#include "DHT.h"
#include <WiFi.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

/* FIREBASE START */
// FIREBASE HEADER
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h" // Provide the token generation processinfo.
#include "addons/RTDBHelper.h" // Provide the RTDB payload printing info and other helper functions.
// FIREBASE SETUP
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
/* 1. Define the WiFi credentials */
#define WIFI_SSID "WIFI_USERNAME"
#define WIFI_PASSWORD "WIFI_PASSWORD"
/* 2. Define the API Key */
#define API_KEY "API KEY"
/* 3. Define the RTDB URL */
#define DATABASE_URL "DATABASE URL"
// Function List


void firebaseSetFloat(String, float);
/* FIREBASE END */

void setup()
{
Serial.begin(115200);
Serial.println("DHT11 Test");
dht.begin();
/* WIFI START */
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();
/* WIFI END */
/* FIREBASE START */
Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
config.api_key = API_KEY; // Assign RTDB API Key
/*For anonymous account: Sign up */
if (Firebase.signUp(&config, &auth, "", ""))
{
Serial.println("Firebase success");
digitalWrite(LED_BUILTIN, LOW);
signupOK = true;
}
else
{
String firebaseErrorMessage =
config.signer.signupError.message.c_str();
Serial.printf("%s\n", firebaseErrorMessage);
}
config.database_url = DATABASE_URL; // Assign rtdb url
config.token_status_callback = tokenStatusCallback; // Set callback
Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);
/* FIREBASE END */
}

int n=0;


void loop()
{
  delay(2000);
  float t = dht.readTemperature();
  if (isnan(t)){
    Serial.println("Failed to read sensor..");
    return;
  }
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.println(" *C ");
  Firebase.RTDB.setFloat("Suhu",t);
  if(Firebase.RTDB.failed()){
    Serial.print("setting/ Number Failed");
    Serial.println(Firebase.RTDB.error());
    return
  }
  delay(1000);
  Serial.println("Data sukses terkirim");
  delay(1000);
}
