#include <math.h>
#include "AdafruitIO_WiFi.h"
#include "NewPing.h"


#define BUZZER_PIN 27
#define LED_VME_ALARME 13
#define LED_AMA_ALARME 2
#define LED_VDE_ALARME 4
#define BOTAO_FISICO 26
#define TRIG_PIN 12
#define ECHO_PIN 14

// Configuração do ultrassonico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Configurações da rede WIFI
#define WIFI_SSID ""
#define WIFI_PASS ""

// Autenticação Adafruit IO
#define IO_USERNAME ""
#define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinLed 14  //Pino do LED

AdafruitIO_Feed *botaoalarme = io.feed("botaoalarme");
AdafruitIO_Feed *distanciaultrassom = io.feed("distanciaultrassom");

// Variáveis de controle
bool alarmeAtivo = false;
unsigned int distancia = 0;
int LIMITE_DISTANCIA = 15;


void setup() {
  // pinMode(pinLed, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_VME_ALARME, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);

  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Adafruit Conectado!");

  // Vincula a função callback ao feed
  botaoalarme->onMessage(handleAlarme);

  Serial.println();
  Serial.println(io.statusText());

  // Configuração do callack, quando o feed receber(atualizar) um valor
  // botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado
}

void loop() {

  // // Manter a conexão com o Adafruit IO ativa
  io.run();

  //leitura do botão físico
  if (digitalRead(BOTAO_FISICO) == 1) {
    delay(200);  // debounce simples
    alarmeAtivo = !alarmeAtivo;

    botaoalarme->save(String(alarmeAtivo ? "true" : "false"));
    Serial.println(alarmeAtivo ? F("Alarme ARMADO pelo botao fisico") : F("Alarme DESARMADO pelo botao fisico"));
  }

  distancia = sonar.ping_cm();
  Serial.print("Distancia lida: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if(distancia != 0){
    // só envia distancias válidas
  distanciaultrassom -> save(distancia);
  }

  //ativação ou desativação do alarme
  if(alarmeAtivo && distancia > 0 && distancia < LIMITE_DISTANCIA) {
    ativarAlerta();
  } else {
    desligarAlerta();
  }

  // Chamada da função publish
  // publicacao();

  // Serial.print(F("Distancia Lida: "));
  // Serial.println(sonar.ping_cm());
  // delay(500);

  delay(3000); // intervalo ideal para a Adafruit
}