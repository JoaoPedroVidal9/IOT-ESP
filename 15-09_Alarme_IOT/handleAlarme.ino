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
  digitalWrite(pinBuzzer,HIGH);
  digitalWrite(pinLed,HIGH);
}

void desligarAlerta(){
  digitalWrite(pinBuzzer,LOW);
  digitalWrite(pinLed,LOW);
}