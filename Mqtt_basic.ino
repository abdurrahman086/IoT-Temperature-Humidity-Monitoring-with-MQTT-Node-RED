#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
 
const char* ssid = "Wokwi-GUEST";
const char* password = "";

float temperature;
float humidity;
char bufferTemp[5];
char bufferHum[5];
unsigned long prevMillis;

const char* mqtt_server = "broker.emqx.io";
const char* TOPIC_LED = "bdur/led";
const char* TOPIC_TEMP = "bdur/temperature";
const char* TOPIC_HUMID = "bdur/humidity";
const char* TOPIC_JSON = "bdur/dht";
int intervalPengiriman = 5; // satuan detik


#define LED 2
#define DHTPIN 14
#define DHTTYPE DHT22

WiFiClient espClient;
PubSubClient mqtt(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Terhubung");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan Masuk dari topic [");
  Serial.print(topic);
  Serial.print("] :");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(LED, HIGH);
    Serial.println("LED ON");
  } 
  else if((char)payload[0] == '0') {
    digitalWrite(LED, LOW);
    Serial.println("LED OFF");
  }

}

void reconnect() {
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (mqtt.connect(clientId.c_str())) {
      Serial.println("connected!");
      mqtt.subscribe(TOPIC_LED);
      Serial.println("Subscribe ke topic: " + String(TOPIC_LED));
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqtt.state());
      Serial.println("Reconnect dalam 5 detik");
      delay(5000);
    }
  }
}

void publish_data() {
  sprintf(bufferTemp, "%.1f", temperature);
  mqtt.publish(TOPIC_TEMP, bufferTemp);

  sprintf(bufferHum, "%.1f", humidity);
  mqtt.publish(TOPIC_HUMID, bufferHum);
}

void publish_json() {

  char json[256];
  JsonDocument doc;

  sprintf(bufferTemp, "%.1f", temperature);
  sprintf(bufferHum, "%.1f", humidity);

  doc["temperature"] = bufferTemp;
  doc["humidity"] = bufferHum;

  serializeJson(doc, json);
  mqtt.publish(TOPIC_JSON, json);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  dht.begin();
  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(callback);
}

void loop() {

  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();

  if (millis() - prevMillis >= intervalPengiriman*1000) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    Serial.println("temperature: " + String(temperature));
    Serial.println("Humidity" + String(humidity));
    Serial.println();

    publish_json();
    publish_data();
    prevMillis = millis();
  }
  delay(5);

}