# Projeto sensor_de_temperatura_em_nuvem.

Bem-vindo ao projeto sensor_de_temperatura_em_nuvem! Este repositório contém o código-fonte e a documentação para o projeto baseado no microcontrolador ESP32.

## Visão Geral

Este projeto foi desenvolvido para uma Hamburgueria com a finalidade de medir a temperatura de uma pista fria e armazenar ela em nuvem utilizando os serviços da siemens. Usamos o ESP32 devido à sua versatilidade e recursos, incluindo conectividade Wi-Fi e Bluetooth integrados.

## Funcionalidades

- Conexão Wi-Fi para enviar os dados á um broker MQTT
- Integração com NODE-RED para ouvir a temperatura e trata-la para a nuvem.
- Integração com sensor de temperatura DS18B20
- Interface web para da Siemens para monitorar a temperatura

## Requisitos

- **ESP32**: Qualquer modelo compatível.
  
- **OUTROS COMPONENTES**: Sensor de Temperatura DS18B20, Protoboard 400 Pontos, Placa Shield Expansão Esp32 Esp 30 Pinos Micro Usb E Usb-c, Display Tela Lcd 16x2 Backlight Azul Arduino C Interface I2c,
- Jumper Fio Macho/fêmea e apenas Macho também, Cabo Micro Usb 30cm Azul Arduino Leonardo Yún Micro Due Esp.

- **IDE**: Arduino IDE.
  
- **Bibliotecas**: <OneWire.h>, <DallasTemperature.h>, <Wire.h>, <LiquidCrystal_I2C.h>, <WiFi.h>, <PubSubClient.h>.
