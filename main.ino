//dht11
// baixar bibilioteca dht11
#include "DHT.h"
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//higrômetro
 #define pino_sinal_analogico A0
int valor_analogico;

//BMP280
//baixar biblioteca adafruit BMP280 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp;

//motores
//Baixar a biblioteca dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
  
#define INT1 2
#define INT2 3
#define INT3 4
#define INT4 5

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  //dht11
  dht.begin();
  //higrômetro
  pinMode(pino_sinal_analogico, INPUT);

  //motores
  Dabble.begin(9600,7,6);  
  pinMode(INT1,OUTPUT);
  pinMode(INT2,OUTPUT);
  pinMode(INT3,OUTPUT);                                                                    
  pinMode(INT4,OUTPUT);
  Stop();

  //BMP280
  Serial.begin(9600);
  while ( !Serial ) delay(100);   
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
 
void loop() 
{
 Dabble.processInput();          
if(GamePad.isUpPressed())
{
 forward(); 
}
else if(GamePad.isDownPressed())
{
 backward(); 
}
else if(GamePad.isLeftPressed())
{
 left(); 
}
else if(GamePad.isRightPressed())
{
 right(); 
}
else
{
 Stop(); 
}
  bmp280();
  higrometro();
  DHt11();
}

void bmp280(){
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
}

void higrometro()
{
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

void DHt11(){
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
}

void forward() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,HIGH);
  digitalWrite(INT3,HIGH);
  digitalWrite(INT4,LOW);
}
     
void backward() {
  digitalWrite(INT1,HIGH);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,HIGH);
}
     
void left() {
  digitalWrite(INT1,HIGH);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,HIGH);
  digitalWrite(INT4,LOW);    
}
     
void right() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,HIGH);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,HIGH);  
}
     
void Stop() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,LOW);  

}
