//Inclusão de Bibliotecas
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>

// Parâmetros de conexão com wifi
const char *ssid = "Meu wi-fi Zé ";
const char *password = "naoentranao";

// Parâmetros de conexão com canal MQTT
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *topic = "iotteste/matheus";
const char *mqtt_user = "";
const char *mqtt_password = "";

//Inicialização de Objetos e Variáveis Globais
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal lcd(D2, D3, D4, D5, D6, D7);

// Variáveis do MQTT
bool mqtt_status = 0;

// Variáveis do sensor
int sensor = A0;
int interval = 600;
int signal;

//Tenta conectar ao broker MQTT até 5 vezes.
//Configura o servidor e callback MQTT.
//Gera um client_id único usando o endereço MAC do ESP8266.
//Publica uma mensagem inicial e se inscreve no tópico especificado.
  
bool connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);

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
//Função chamada quando uma mensagem chega ao tópico inscrito, imprimindo o tópico e o conteúdo da mensagem.
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

  // Inicialização do Display LCD
  lcd.begin(16, 2);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("STATUS: " + String(WiFi.status()));
  }

  Serial.println(WiFi.localIP());

  // Configuração do MQTT
  mqtt_status = connectMQTT();

  lcd.print("Connecting...");
}

//Chama client.loop() para manter a comunicação MQTT ativa
//Lê o valor do sensor no pino analógico A0.
//Converte o valor lido para uma escala de 0 a 100.
//Exibe o valor no display LCD.
//Publica o valor no tópico MQTT a cada 300 ms.
  
void loop() {
  static long long pooling = 0;

  if (mqtt_status) {
    client.loop();
  }

  // sensor value
  signal = analogRead(sensor);

  int value = signal * (3.3 / 1023.0) * 100;
  
  String bpmStr = String(value);

  Serial.println(value);

  lcd.clear();
  lcd.print("BPM: ");
  lcd.print(bpmStr);

  client.publish(topic, bpmStr.c_str());

  delay(300);
}
