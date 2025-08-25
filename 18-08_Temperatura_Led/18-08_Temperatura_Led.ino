#include <math.h>  // Necessário para usar a função log()
#include "AdafruitIO_WiFi.h"

#define WIFI_SSID "..."
#define WIFI_PASS "..."

// Autenticação Adafruit IO
#define IO_USERNAME  "..."
#define IO_KEY       "..."

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// --- Configuração de hardware ---
#define pinNTC 34  // Pino ADC onde o NTC está conectado (ESP32: 32, 33, 34, 35, 36, 39)
#define pinLed 14  // Pino do LED

// Controle de envio de dados
float tempAtual = 0;
float tempAnterior = -1;

// Variável / Ponteiro para referenciar o feed Temperatura
AdafruitIO_Feed *temperatura = io.feed("Temperatura");

// --- Constantes do NTC ---
const float Rfixo = 10000.0;     // Resistor fixo do divisor de tensão (ohms)
const float Beta = 3950.0;       // Constante Beta do NTC (fornecida pelo fabricante)
const float R0 = 10000.0;        // Resistência nominal do NTC a 25°C (ohms)
const float T0_kelvin = 298.15;  // 25°C em Kelvin
const float Vcc = 3.3;           // Tensão de alimentação do divisor (ESP32 = 3,3V)

void setup() {
  //Modo do pino
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(115200);  // Inicializa comunicação serial

  while (!Serial)
    ;

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(750);
  }

  Serial.println("");
  Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber(atualizar) um valor
  temperatura -> onMessage(handleTemperatura);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  io.run();

  // publicacao(); // Chamada da função publish



  delay(7000);  // espera 2 segundos antes de repetir
}