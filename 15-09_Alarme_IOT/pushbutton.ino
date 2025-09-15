void testeBotao(int pinoBotao){
  Serial.print(F("Saída do Botão: "));
  Serial.println(digitalRead(pinoBotao));
  delay(500);
}