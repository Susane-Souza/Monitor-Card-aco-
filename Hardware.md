# Componentes de Hardware

## NodeMCU ESP8266
O NodeMCU é um microcontrolador baseado no ESP8266 que possui conectividade Wi-Fi integrada. Ele é ideal para projetos de IoT devido ao seu baixo custo e facilidade de uso.

## Sensor de Batimentos Cardíacos KY-039
O sensor KY-039 é um sensor óptico utilizado para medir os batimentos cardíacos. Ele detecta a variação da intensidade de luz causada pela pulsação do sangue.

## Display LCD
O display LCD é utilizado para exibir as leituras dos batimentos cardíacos em tempo real. Ele oferece uma interface visual clara e fácil de entender.

## Protoboard 400 Pontos
Para montagem do circuito utilizamos uma protoboard de 400 pontos e cabos jumper macho para macho, macho para fêmea e fêmea para fêmea.

# Comunicação e Protocolos

## MQTT
Utilizamos o protocolo MQTT para enviar as leituras dos batimentos cardíacos para um servidor na nuvem. O protocolo MQTT é leve e eficiente, ideal para dispositivos IoT com recursos limitados.

## Configuração do MQTT
- **Broker MQTT:** Utilizamos um broker público como o HiveMQ.
- **Tópico MQTT:** As leituras são publicadas no tópico `home/heart_rate`.
- **Cliente MQTT:** O NodeMCU ESP8266 atua como cliente MQTT, publicando as leituras dos batimentos cardíacos.

  # Instruções de Montagem e Uso

## Montagem do Hardware
1. **NodeMCU ESP8266:**
   - Conecte o pino de alimentação (3V3) à protoboard.
   - Conecte o pino GND à protoboard.
2. **Sensor KY-039:**
   - Conecte o pino de saída analógica ao pino A0 do NodeMCU.
   - Conecte o pino de alimentação (VCC) ao trilho positivo da protoboard.
   - Conecte o pino GND ao trilho negativo da protoboard.
3. **Display LCD:**
   - Conecte os pinos SDA e SCL aos pinos correspondentes do NodeMCU.
   - Conecte o pino VCC ao trilho positivo da protoboard.
   - Conecte o pino GND ao trilho negativo da protoboard.
  
     ## Diagrama de montagem
![image](https://github.com/Susane-Souza/Monitor-Cardiaco/assets/160166243/a7c67144-4c35-4b9b-9682-760327ab5a12)


