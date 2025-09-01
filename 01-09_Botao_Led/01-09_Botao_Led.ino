#include "AdafruitIO_WiFi.h"

#define WIFI_SSID ""
#define WIFI_PASS ""

// Autenticação Adafruit IO
#define IO_USERNAME  ""
#define IO_KEY       ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// --- Configuração de hardware ---
#define pinLed 14  // Pino do LED

// Variável / Ponteiro para referenciar o feed Temperatura
AdafruitIO_Feed *botao_led = io.feed("botao_led");

void setup() {
  //Modo do pino
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
  botao_led -> onMessage(handleBotaoLed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  io.run();

  delay(1000);  // espera 1 segundos antes de repetir
}