void handleAlarme(AdafruitIO_Data *data) {
  String valor = data->toString();

  Serial.print(F("Valor Recebido do Feed: "));
  Serial.println(valor);

  if (valor == "true") {
    alarmeAtivo = true;
    Serial.println(F("Alarme ativado e pronto para disparar."));
  } else {
    alarmeAtivo = false;
    Serial.println(F("Alarme desativado."));
  }
}

void ativarAlerta() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_VME_ALARME, HIGH);
  digitalWrite(LED_AMA_ALARME, LOW);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_VME_ALARME, LOW);
  delay(500);
  distancia = sonar.ping_cm();
  if (distancia != 0 && distancia != velhaDist) {
    // só envia distancias válidas e novas
    distanciaultrassom->save(distancia);
    velhaDist = distancia;
  }
}

void desligarAlerta() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_VME_ALARME, LOW);
  digitalWrite(LED_AMA_ALARME, HIGH);
  delay(500);
}