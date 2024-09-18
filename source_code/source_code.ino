#define dimmer 5    // Pino escolhido para controlar o dimmer (GPIO 5)
#define potPin 36   // Pino de leitura do potenciômetro (GPIO 36 no ESP32, que é A0)

// Variáveis para controle da luminosidade
volatile long lum = 0;

void zeroCross() {
  if (lum > 100) lum = 100;
  if (lum < 0) lum = 0;

  long t1 = 8200L * (100L - lum) / 100L;
  delayMicroseconds(t1);
  digitalWrite(dimmer, HIGH);
  delayMicroseconds(10);
  digitalWrite(dimmer, LOW);
}

void setup() {
  Serial.begin(115200);   // Inicializa o monitor serial para debug
  pinMode(dimmer, OUTPUT);
  pinMode(potPin, INPUT); // Configura o pino do potenciômetro como entrada

  // Configura o pino para interrupção de cruzamento por zero
  attachInterrupt(digitalPinToInterrupt(4), zeroCross, RISING);  // Supondo que o cruzamento por zero esteja no GPIO 4
}

void loop() {
  int potValue = analogRead(potPin);  // Leitura do potenciômetro (0 a 4095)
  lum = map(potValue, 0, 4095, 10, 90); // Mapeia o valor do potenciômetro para a intensidade desejada
  
  // Loga o valor do potenciômetro e a luminosidade ajustada
  Serial.print("Valor do potenciômetro: ");
  Serial.println(potValue);
  Serial.print("Luminosidade ajustada: ");
  Serial.println(lum);

  delay(100); // Ajuste conforme necessário para suavizar as leituras
}
