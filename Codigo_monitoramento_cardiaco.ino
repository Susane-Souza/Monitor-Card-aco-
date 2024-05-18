#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Parâmetros de conexão com wifi
const char *ssid = "Meu wi-fi Zé ";
const char *password = "naoentranao";

// Parâmetros de conexão com canal MQTT
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *topic = "iotteste/matheus";
const char *mqtt_user = "";
const char *mqtt_password = "";

WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis do MQTT
bool mqtt_status = 0;

// Variáveis do sensor
int sensor = A0;
int interval = 600;
int signal;

bool connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      client.subscribe(topic);
    } else {
      delay(5000);
    }
  }
}

bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  do {
    String client_id = "iotteste-";
    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", client_id.c_str());
    } else {
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }

    tentativa++;

  } while (!client.connected() && tentativa < 5);

  if (tentativa < 5) {
    // publish and subscribe
    client.publish(topic, "{teste123,113007042022}");
    client.subscribe(topic);
    return 1;
  } else {
    Serial.println("Não conectado");
    return 0;
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("STATUS: " + String(WiFi.status()));
  }

  Serial.println(WiFi.localIP());

  // Configuração do MQTT
  mqtt_status = connectMQTT();
}

void loop() {
  static long long pooling = 0;

  if (mqtt_status) {
    client.loop();
  }

  // sensor value
  signal = analogRead(sensor);

  int value = signal * (3.3 / 1023.0) * 100;

  Serial.println(value);

  String bpmStr = String(value);

  client.publish(topic, bpmStr.c_str());

  delay(300);
}
