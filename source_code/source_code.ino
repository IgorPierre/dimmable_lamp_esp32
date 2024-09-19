#define dimmer 5    // Pino escolhido para controlar o dimmer (GPIO 5)
#define potPin 36   // Pino de leitura do potenciômetro (GPIO 36 no ESP32)

volatile long lum = 0;

void setup() {
  Serial.begin(115200);
  pinMode(dimmer, OUTPUT);
  pinMode(potPin, INPUT);
  digitalWrite(dimmer, LOW);
}

void loop() {
  int potValue = analogRead(potPin);  // Leitura do potenciômetro (0 a 4095)
  
  lum = map(potValue, 0, 4095, 0, 255); // Escala o valor para controle de PWM

  analogWrite(dimmer, lum);
  
  Serial.print("Valor do potenciômetro: ");
  Serial.println(potValue);
  Serial.print("Luminosidade ajustada: ");
  Serial.println(lum);

  delay(100);
}
