#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Jon";
const char* password = "Reefreef";

const char* mqttServer = "10.216.187.116"; // IP do seu servidor MQTT
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.println(".");    
    delay(250);
  }
  Serial.println("Conectado ao WiFi");

  client.setServer(mqttServer, mqttPort);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32_Client")) {
      Serial.println("Tentando conectar ao MQTT...");
      delay(1000);
    }
    Serial.println("Conectado ao MQTT");
  }

  // Enviar dados
  String payload = "{\"sensor\": \"temperatura\", \"valor\": 25.5}";
  client.publish("iot/esp32", payload.c_str());

  delay(5000);
}