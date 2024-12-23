#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Definições de pinos
#define ONE_WIRE_BUS 4

// Configuração do OneWire e DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Configuração da Tela LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variável para armazenar a temperatura
float temperature = 0.0;

// Definições de Wi-Fi
const char* ssid = "julio"; // Substitua pelo nome da sua rede Wi-Fi
const char* password = "#Julio310705"; // Substitua pela senha da sua rede Wi-Fi

// Endereço do Broker MQTT
const char* mqtt_server = "mqtt.eclipseprojects.io";

// Tópico MQTT
const char* mqtt_topic = "topico/temperatura";

// Cliente Wi-Fi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis de tempo para controlar os intervalos de atualização
unsigned long previousMillisLCD = 0;
unsigned long previousMillisMQTT = 0;
const long intervalLCD = 1000;  // Intervalo de atualização do LCD (1 segundo)
const long intervalMQTT = 5000;  // Intervalo de publicação no MQTT (5 segundos)

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop até conseguir se conectar ao broker MQTT
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Inicializando a tela LCD
  lcd.init();
  lcd.backlight();
  lcd.print("ESP32 - Projeto");
  delay(2000); // Atraso para exibir a mensagem inicial

  // Inicializando o sensor DS18B20
  sensors.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Solicita a temperatura do sensor
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  // Verifica se o sensor está conectado
  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Erro: Sensor de temperatura desconectado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro: Sensor");
    lcd.setCursor(0, 1);
    lcd.print("desconectado");
    return;
  }

  // Atualiza a tela LCD
  if (currentMillis - previousMillisLCD >= intervalLCD) {
    previousMillisLCD = currentMillis;
    lcd.setCursor(0, 0);
    lcd.print("Temperatura:");
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" C");
  }

  // Publica a temperatura no broker MQTT
  if (currentMillis - previousMillisMQTT >= intervalMQTT) {
    previousMillisMQTT = currentMillis;

    // Formata a temperatura para JSON
    char msg[50];
    snprintf(msg, 50, "{\"temperature\": \"%f\"}", temperature);

    // Publica a mensagem no tópico MQTT
    client.publish(mqtt_topic, msg);

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" C");
  }
}
