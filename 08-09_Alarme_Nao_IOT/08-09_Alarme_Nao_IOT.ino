#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

#define WIFI_SSID "..."
#define WIFI_PASS "..."

// Autenticação Adafruit IO
#define IO_USERNAME  "..."
#define IO_KEY       "..."

// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// --- Configuração de hardware ---
#define pinBuzzer 27  // Pino do Buzzer                (OUTPUT)
#define pinLed 13  // Pino do LED                      (OUTPUT)
#define pinButton 26 // Pino do Botão (PushDown)       (INPUT)
#define pinTrig 12 // Pino Trig do Sensor Ultrassônico (OUTPUT)
#define pinEcho 14 // Pino Echo do Sensor Ultrassônico (INPUT)

// Configuração do ultrassônico
#define MAX_DISTANCE 100
NewPing sonar(pinTrig, pinEcho, MAX_DISTANCE);

// Variável / Ponteiro para referenciar o feed 
// AdafruitIO_Feed *nomedofeed = io.feed("nomedofeed");

void setup() {
  //Modo do pin
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinButton, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(115200);  // Inicializa comunicação serial

  while (!Serial)
    ;

  // Serial.print("Conectando ao Adafruit IO");
  // io.connect();

  // while (io.status() < AIO_CONNECTED) {
  //   Serial.print(".");
  //   delay(750);
  // }

  // Serial.println("");
  // Serial.println(io.statusText());

  // Configuração do callback, quando o feed receber(atualizar) um valor
  // nomedofeed -> onMessage(handleNomedofeed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado

  delay(1000);
}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  // io.run();

  // publicacao(); // Chamada da função publish

  // testeBuzzer();

  testeLed(); 

  testeBotao(pinButton);

  Serial.print(F("Distancia lida: "));
  Serial.println(sonar.ping_cm());

  delay(1000);  // espera antes de repetir
}