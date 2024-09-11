const int ldrPin = 36;

void setup() {
  Serial.begin(115200);
  
  pinMode(ldrPin, INPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  Serial.print("Valor do LDR: ");
  Serial.println(ldrValue);

  delay(500);
}