
//dht11
#include "DHT.h"
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//higrômetro
 #define pino_sinal_analogico A0
int valor_analogico;

//motor1
const int acti = 4;           // Pino de controle do motor 1
const int motor1_Pin1 = 2;    // Pino 6 do L293
const int motor1_Pin2 = 3;    // Pino 7 do L293
bool motor1Ligado = false;    // Estado motor 1

//motor2
const int acti2 = 5;          // Pino de controle do motor 2
const int motor2_Pin1 = 6;   // Pino 10 do L293
const int motor2_Pin2 = 7;   // Pino 11 do L293
bool motor2Ligado = false;    // Estado motor 2

//botôes
const int botao1 = 8;        // Pino do botão 1
const int botao2 = 9;        // Pino do botão 2
const int botao3 = 10;        // Pino do botão 3
const int botao4 = 11;        // Pino do botão 4

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  //dht11
  dht.begin();
  //higrômetro
  pinMode(pino_sinal_analogico, INPUT);

  //motor 1
    pinMode(acti, OUTPUT);
    pinMode(motor1_Pin1, OUTPUT);
    pinMode(motor1_Pin2, OUTPUT);

  //motor 2
    pinMode(acti2, OUTPUT);
    pinMode(motor2_Pin1, OUTPUT);
    pinMode(motor2_Pin2, OUTPUT);
  
  //botões
    pinMode(botao1, INPUT);
    pinMode(botao2, INPUT);
    pinMode(botao3, INPUT);
    pinMode(botao4, INPUT);
}
 
void loop() 
{
  componentes()
}

void componentes()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else 
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    delay(100);
  }
  //higrômetro
  valor_analogico = analogRead(pino_sinal_analogico);
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);

  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: Solo umido");
  }
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
  }
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: Solo seco");
  }
  delay(200);
}

void movimento()
{
    int ultimoEstado1 = LOW;
    int ultimoEstado2 = LOW;
    int ultimoEstado3 = LOW;
    int ultimoEstado4 = LOW;

    int leitura1 = digitalRead(botao1);
    int leitura2 = digitalRead(botao2);
    int leitura3 = digitalRead(botao3);
    int leitura4 = digitalRead(botao4);

  // motor gira pra frente
    if (leitura1 == HIGH && ultimoEstado1 == LOW) {
        motor1Ligado = !motor1Ligado;
        motor2Ligado = !motor2Ligado;
        if (motor1Ligado && motor2Ligado) {
            digitalWrite(motor1_Pin1, LOW);
            digitalWrite(motor1_Pin2, HIGH); // direção motor 1
            digitalWrite(motor2_Pin1, LOW);
            digitalWrite(motor2_Pin2, HIGH); // direção motor 2
            digitalWrite(acti, HIGH);
            digitalWrite(acti2, HIGH);  // ligado
        } else {
            digitalWrite(motor1_Pin1, LOW);
            digitalWrite(motor1_Pin2, LOW);
            digitalWrite(motor2_Pin1, LOW);
            digitalWrite(motor2_Pin2, LOW);
            digitalWrite(acti, LOW);
            digitalWrite(acti2, LOW);  // desligado
        }
        delay(200); // debounce
    }
    ultimoEstado1 = leitura1;

    // motor gira pra trás
    if (leitura2 == HIGH && ultimoEstado2 == LOW) {
        motor2Ligado = !motor2Ligado;
        motor1Ligado = !motor1Ligado;
        if (motor2Ligado && motor1Ligado) {
            digitalWrite(motor2_Pin1, HIGH);
            digitalWrite(motor2_Pin2, LOW);  // sentido oposto motor 2
            digitalWrite(motor1_Pin1, HIGH);
            digitalWrite(motor1_Pin2, LOW); // sentido oposto motor 2
            digitalWrite(acti, HIGH);
            digitalWrite(acti2, HIGH); // ligado
        } else {
            digitalWrite(motor2_Pin1, LOW);
            digitalWrite(motor2_Pin2, LOW);
            digitalWrite(motor1_Pin1, LOW);
            digitalWrite(motor1_Pin2, LOW);
            digitalWrite(acti, LOW);
            digitalWrite(acti2, LOW); // desligado
        }
        delay(200); // debounce
    }
    ultimoEstado2 = leitura2;

  // motor gira pra direita
    if (leitura3 == HIGH && ultimoEstado3 == LOW) {
        motor1Ligado = !motor1Ligado;
        if (motor1Ligado) {
            digitalWrite(motor1_Pin1, LOW);
            digitalWrite(motor1_Pin2, HIGH);  // direção motor 1
            digitalWrite(acti, HIGH);  // ligado
        } else {
            digitalWrite(motor1_Pin1, LOW);
            digitalWrite(motor1_Pin2, LOW);
            digitalWrite(acti, LOW);  // desligado
        }
        delay(200); // debounce
    }
    ultimoEstado3 = leitura3;

  // motor gira pra esquerda
    if (leitura4 == HIGH && ultimoEstado4 == LOW) {
        motor2Ligado = !motor2Ligado;
        if (motor2Ligado) {
            digitalWrite(motor2_Pin1, LOW);
            digitalWrite(motor2_Pin2, HIGH);  // direção motor 1
            digitalWrite(acti2, HIGH);  // ligado
        } else {
            digitalWrite(motor2_Pin1, LOW);
            digitalWrite(motor2_Pin2, LOW);
            digitalWrite(acti2, LOW);  // desligado
        }
        delay(200); // debounce
    }
    ultimoEstado4 = leitura4; 
}