#ifndef pegandoApi_h
#define pegandoApi_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>


class Api
{
    public:
    String pedirParaClima(String codigoClima);
    void filtrandoExibicaoRespostas(String codigoJson, LiquidCrystal_I2C &lcd);

    private:
};



#endif