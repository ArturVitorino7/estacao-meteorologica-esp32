Estação meteorológica IoT desenvolvida em C++ para ESP32, consumindo dados em tempo real da API Open-Meteo e exibindo as informações em um display LCD I2C.

## 🚀 O que o projeto faz?
* **Conexão Wi-Fi:** Conecta o ESP32 à rede local.
* **Requisição HTTP:** Faz requisições GET dinâmicas para a API da Open-Meteo com base em coordenadas informadas via Serial.
* **Filtro de JSON otimizado:** Usa a biblioteca `ArduinoJson` com filtros para economizar memória RAM, capturando apenas o que importa (`temperature_2m`, `relative_humidity_2m` e `apparent_temperature`).
* **Display LCD 20x4:** Atualiza a tela com os dados formatados (incluindo o símbolo de graus).

## 🛠️ Tecnologias
* ESP32
* C++ (Arduino Framework / PlatformIO)
* Bibliotecas: `HTTPClient`, `ArduinoJson`, `LiquidCrystal_I2C`

## ⚙️ Como rodar
1. Clone o repositório.
2. Abra no VS Code com o PlatformIO.
3. Coloque o nome e a senha do seu Wi-Fi no `main.cpp`.
4. Compile, envie para o ESP32 e digite as coordenadas no Monitor Serial (115200 baud).
