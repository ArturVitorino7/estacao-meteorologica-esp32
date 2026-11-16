#include <Arduino.h>
#include <WiFi.h>
#include "pegandoApi.h"
#include <LiquidCrystal_I2C.h>

void processarRespostas();

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* nomeRede = "Vivo Will_EXT";
const char* senhaRede = "Will@98219";

Api minhaApi;

void setup() 
{
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  WiFi.begin(nomeRede, senhaRede);
  
  Serial.print("Conectando ao WiFi:");

  lcd.setCursor(0,0);
  lcd.print("Conectando ao WiFi");

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

}

void loop() 
{
  Serial.println("\n--- Digite a Latitude (ex: -23.66): ---");
  while (Serial.available() == 0) { delay(10); }
  String latitude = Serial.readStringUntil('\n');
  latitude.trim();

  Serial.println("--- Digite a Longitude (ex: -46.53): ---");
  while (Serial.available() == 0) { delay(10); }
  String longitude = Serial.readStringUntil('\n');
  longitude.trim();

  String parametrosClima = "?latitude=" + latitude + "&longitude=" + longitude + "&current=temperature_2m,relative_humidity_2m,apparent_temperature";

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Buscando dados...");

  String jsonRecebido = minhaApi.pedirParaClima(parametrosClima);

  if (jsonRecebido.length() > 0) 
  {
    minhaApi.filtrandoExibicaoRespostas(jsonRecebido, lcd);
  } 
  else 
  {
    Serial.println("Falha ao obter o JSON da API.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro na requisicao!");
  }

  while (Serial.available() > 0) {
    Serial.read();
  }
  
  delay(10000); 
}