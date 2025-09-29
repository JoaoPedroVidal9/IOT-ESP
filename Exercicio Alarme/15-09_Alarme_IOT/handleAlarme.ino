void handleAlarme(AdafruitIO_Data *data) {
  String valor = data -> toString();

  Serial.print(F("Valor Recebido do Feed: "));
  Serial.println(valor);

  if(valor == "true") {
    alarmeAtivo = true;
    Serial.println(F("Alarme ativado e pronto para disparar."));
  }else{
    alarmeAtivo = false;
    Serial.println(F("Alarme desativado."));
  }
  
}

void ativarAlerta(){
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_VME_ALARME, HIGH);
  digitalWrite(LED_AMA_ALARME, LOW);
  delay(500);
}

void desligarAlerta(){
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_VME_ALARME, LOW);
  digitalWrite(LED_AMA_ALARME, HIGH);
  delay(500);
}