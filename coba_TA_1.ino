#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <DHT.h>
#include <Wire.h> 

#define WIFI_SSID "OPPO A15s"
#define WIFI_PASSWORD "luki2002"
#define API_KEY "AIzaSyCjR3gsUiyKxcXq94zB4-HM5wvj6aHJY4I"
#define DATABASE_URL "https://dalamnamabapaputrarohkud-d470b-default-rtdb.asia-southeast1.firebasedatabase.app/"

//DHT dht_sensor(21, DHT11);

//#define ph_sensor 32

#define moist_sensor_1 34
//#define moist_sensor_2 35
//#define moist_sensor_3 36
//#define moist_sensor_4 39

/*#define relay_0 23 // pompa siraman
#define relay_1 22 // kipas
#define relay_2 1  // pompa pupuk
#define relay_3 3 //pompa pestisida

#define relay_4 16 // selenoid_siraman
#define relay_5 17 // selenoid_pupuk
#define relay_6 18 // selenoid_pestisida
#define relay_7 19*/

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

//Sensor ph
//int sensor_ph = 0;        
//float output_ph = 0.0;

//Sensor Moist 1
int output_moisture_1,sensor_moist_1;

//Sensor Moist 2
//int output_moisture_2,sensor_moist_2;

//Sensor Moist 3
//int output_moisture_3,sensor_moist_3;

//Sensor Moist 4
//int output_moisture_4,sensor_moist_4;

//int output_moist_total;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() !- WL_CONNECTED){
    Serial.print("."); delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("signUp OK");
    signupOK = true;
  } else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallBack;
  Firebase.begin(&config, &auth);
  Firebase.reconnecWiFi(true);
  /*pinMode(relay_0 ,OUTPUT);
  pinMode(relay_1 ,OUTPUT);
  pinMode(relay_2 ,OUTPUT);
  pinMode(relay_3 ,OUTPUT);
  pinMode(relay_4 ,OUTPUT);
  pinMode(relay_5 ,OUTPUT);
  pinMode(relay_6 ,OUTPUT);
  pinMode(relay_7 ,OUTPUT);
  pinMode(relay_0 ,OUTPUT);
  pinMode(relay_1 ,OUTPUT);
  pinMode(relay_2 ,OUTPUT);
  pinMode(relay_3 ,OUTPUT);
  pinMode(relay_4 ,OUTPUT);
  pinMode(relay_5 ,OUTPUT);
  pinMode(relay_6 ,OUTPUT);
  pinMode(relay_7 ,OUTPUT);

  pinMode(relay_0 ,LOW);
  pinMode(relay_1 ,LOW);
  pinMode(relay_2 ,LOW);
  pinMode(relay_3 ,LOW);
  pinMode(relay_4 ,LOW);
  pinMode(relay_5 ,LOW);
  pinMode(relay_6 ,LOW);
  pinMode(relay_7 ,LOW);*/

  //dht_sensor.begin();
}

void loop() {
  if(Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || SendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    sensor_moist_1 = analogRead(moist_sensor_1); //put Sensor insert into soil
    if(Firebase.RTDB.setInt(&fbdo, "Sensor/data", sensor_moist)){
      Serial.println(); Serial.print(sensor_moist_1);
      Serial.print(" - succesfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ")");
    } else{
      Serial.println("FAILED: "+ fbdo.errorReason());
    }
  
  }
  
/*
  //Program Kelembaban Tanah
  sensor_moist_1 = analogRead(moist_sensor_1); //put Sensor insert into soil
  Serial.println(); Serial.print(sensor_moist_1);
  Serial.print(" - succesfully saved to: " + fbdo.dataPath());
  Serial.println(" (" + fbdo.dataType() + ")");
  /*sensor_moist_2 = analogRead(moist_sensor_2);
  sensor_moist_3 = analogRead(moist_sensor_3);
  sensor_moist_4 = analogRead(moist_sensor_4);*/

  /*output_moisture_1 = ( 100 - ( (sensor_moist_1/4095.00) * 100 ) );
  /*output_moisture_2 = ( 100 - ( (sensor_moist_2/4095.00) * 100 ) );
  output_moisture_3 = ( 100 - ( (sensor_moist_3/4095.00) * 100 ) );
  output_moisture_4 = ( 100 - ( (sensor_moist_4/4095.00) * 100 ) );*/

  /*
  output_moist_total = output_moisture_1 //+ output_moisture_2 + output_moisture_3 + output_moisture_4) / 4;
  Serial.print("Moisture = ");
  Serial.print(output_moist_total);  /* Print Temperature on the serial window */
  /*Serial.println("%");
  
  if (output_moist_total >= 60)
  {
  Serial.print(output_moist_total);
  Serial.println("%");
  Serial.println("Tanaman Kenyang");
  digitalWrite(relay_0, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  }
  else if(soilmoisturepercent <=0)
  {
  Serial.print(output_moist_total);
  Serial.println("%");
  Serial.println("Tanaman Butuh Air");
  digitalWrite(relay_0, LOW);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, LOW);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  }
  else if(soilmoisturepercent > 50 && soilmoisturepercent < 60)
  {
  Serial.print(output_moist_total);
  Serial.println("%");
  Serial.println("Tanaman Tercukupi");
  digitalWrite(relay_0, HIGH);
   digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  }
  delay(250);

  //Program Suhu
  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float suhu = dht_sensor.readTemperature();

  if (suhu >= 30) {
  digitalWrite(relay_1, LOW);
  Serial.print(" Temp: ");
  Serial.print(suhu);
  Serial.println(" Suhu Panas");
  delay(1000);
  }

  if (suhu < 30) {
  digitalWrite(relay_1, HIGH);
  Serial.print(" Temp: ");
  Serial.print(suhu);
  Serial.println(" Suhu Normal");
  delay(1000);
  }

  //Program pH
  sensor_ph= analogRead(analogInPin);
  delay(500);
  //rumus didapat berdasarkan datasheet 
  output_ph = (-0.0139*sensor_ph)+7.7851;

  if (output_ph >= 6.5) {
  Serial.print(" pH: ");
  Serial.print(output_ph);
  Serial.println(" pH Cukup");
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_0, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, LOW);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  delay(1000);
  }

  if (output_ph < 6.5) {
  Serial.print(" pH: ");
  Serial.print(output_ph);
  Serial.println(" Suhu Normal");
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_0, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  delay(1000);
  }
  
  Serial.print("adc= ");
  Serial.print(sensor_ph);
  Serial.print("pH = ");
  Serial.println(output_ph);*/

}
