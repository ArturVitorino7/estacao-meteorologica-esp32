#include "pegandoApi.h"

String Api::pedirParaClima(String codigo)
{
    HTTPClient httpClima;

    String enderecoUrl = "https://api.open-meteo.com/v1/forecast";
    String enderecoCompletoURL = enderecoUrl + codigo;

    httpClima.useHTTP10(true);

    httpClima.begin(enderecoCompletoURL);

    Serial.print("URL requisitada: ");
    Serial.println(enderecoCompletoURL);

    int codigoHTTP = httpClima.GET();
    String respostaHTTP = "";

    if(codigoHTTP != 200)
    {
        Serial.printf("Erro. Codigo:%d", codigoHTTP);
        httpClima.end();
        return respostaHTTP;
    }

    respostaHTTP = httpClima.getString();

    Serial.println("JSON Bruto recebido:");
    Serial.println(respostaHTTP);

    httpClima.end();
    return respostaHTTP;
}


void Api::filtrandoExibicaoRespostas(String codigoJson, LiquidCrystal_I2C &lcd)
{
    JsonDocument filtroClima;
    JsonDocument docClima;

    filtroClima["current"]["temperature_2m"] = true;
    filtroClima["current"]["relative_humidity_2m"] = true;
    filtroClima["current"]["apparent_temperature"] = true;

    DeserializationError errorClima = deserializeJson(docClima, codigoJson, DeserializationOption::Filter(filtroClima));

    switch (errorClima.code())
  {
  case DeserializationError::Ok:
    break;
  case DeserializationError::InvalidInput:
    Serial.println("JSON com Sintaxe invalida");
    return;
  case DeserializationError::EmptyInput:
    Serial.println("JSON vazio ou expirou o tempo");
    return;
  case DeserializationError::IncompleteInput:
    Serial.println("JSON incompleto");
    return;
  case DeserializationError::NoMemory:
    Serial.println("JSON sem memória");
    return;
  case DeserializationError::TooDeep:
    Serial.println("Aninhamento acima do limite da função");
    return;
  default:
    Serial.println(errorClima.c_str());
    return;
  }


    float temperatura = docClima["current"]["temperature_2m"]  | -1.0f ;
    float umidade = docClima["current"]["relative_humidity_2m"]  | -1.0f;
    float sensacaoTermica = docClima["current"]["apparent_temperature"]  | -1.0f;

    Serial.printf("Temperatura: %.2f C\n", temperatura);
    Serial.printf("Umidade: %.2f %%\n", umidade);
    Serial.printf("Sensacao Termica: %.2f C\n", sensacaoTermica);

    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223); 
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");

    lcd.setCursor(0, 2);
    lcd.print("Sens.T: ");
    lcd.print(sensacaoTermica);
    lcd.print((char)223);
    lcd.print("C");
   
}