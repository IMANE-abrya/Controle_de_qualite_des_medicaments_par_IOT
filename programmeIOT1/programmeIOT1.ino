#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "THEAL1";
const char* password = "1L340FGH";
const char* mqtt_server = "mqtt.thingspeak.com";
const int mqtt_port = 1883;
const char* mqtt_channel = "HCH1234445J";
const char* mqtt_write_api_key = "L01H324445J";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connexion au réseau Wi-Fi : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Wi-Fi connecté !");
  Serial.println("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion à MQTT...");
    
    if (client.connect("ESP32Client", mqtt_channel, mqtt_write_api_key)) {
      Serial.println("connecté");
    } else {
      Serial.print("Échec, rc=");
      Serial.print(client.state());
      Serial.println(" ; nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Échec de lecture du capteur DHT !");
    return;
  }
  
  String payload = "field1=";
  payload += String(t);
  payload += "&field2=";
  payload += String(h);
  
  String topic = "channels/";
  topic += HKH127Z5876;
  topic += "/publish/";
  topic += mqtt_write_api_key;
  
  char attributes[100];
  payload.toCharArray(attributes, 100);

  if (client.publish(topic.c_str(), attributes)) {
    Serial.println("Données publiées avec succès !");
    Serial.print("Température : ");
    Serial.println(t);
    Serial.print("°C, Humidité : ");
    Serial.print(h);
    Serial.println(" %");
  } else {
    Serial.println("Échec de la publication des données");
  }

  // Délai entre les publications
  delay(20000);
}

