#define pinZC 2
#define pinDIM 4  
#define pinLDR 7
#define intervaloLeitura 1000
#define periodo 8333

#define luminosidadeIdeal 500
#define iMin 20
#define iMax 90
#define difMin 0
#define difMax 200

volatile int intensidade = 0;
unsigned long controleTempo;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinDIM, OUTPUT);
  pinMode(pinLDR, INPUT);
  pinMode(pinZC, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinZC), sinalZC, RISING);

  controleTempo = millis();
  Serial.println("Sistema de lâmpada dimerizável iniciado com KY-018 LDR.");
}

void loop() {
  if (millis() - controleTempo > intervaloLeitura) {
    Serial.println("Lendo luminosidade...");
    
    int luminosidade = analogRead(pinLDR);
    float difLuminosidade = luminosidadeIdeal - luminosidade;
    
    Serial.print("Luminosidade: ");
    Serial.println(luminosidade);
  
    Serial.println("Calculando intensidade...");
    
    if (difLuminosidade > difMax) intensidade = iMax;
    else if (difLuminosidade < difMin) intensidade = 0;
    else {
      intensidade = map(int(difLuminosidade), int(difMin), int(difMax), iMin, iMax);
    }
    
    Serial.print("Intensidade: ");
    Serial.println(intensidade);

    controleTempo += intervaloLeitura;
  }
}

void sinalZC() {
  if (intensidade < iMin) return;
  if (intensidade > iMax) intensidade = iMax;

  int delayInt = periodo - (intensidade * (periodo / 100));

  delayMicroseconds(delayInt);
  digitalWrite(pinDIM, HIGH);
  delayMicroseconds(6);
  digitalWrite(pinDIM, LOW);
}
