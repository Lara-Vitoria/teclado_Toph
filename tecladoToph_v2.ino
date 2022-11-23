#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#include "Keypad.h"

//conexao wifi
const char* ssid = "alo galera de cowboy";
const char* password = "alogaleradepiao";

//url api
String serverName = "http://192.168.29.112:3000";

String idUsuario = "";
String idDado = "";

const byte linhas = 3;
const byte colunas = 3;
const byte colunasAux = 2;

char Teclas[linhas][colunas] = {
  { '1', '2' },
  { '3', '4' },
  { '5', '6' },
};

//mapeamento do teclado auxiliar
char aux[linhas][colunasAux] = {
  { '0', '0' },
  { '0', '0' },
  { '0', '0' }
};

String auxStg = "";
String palavra = "";

byte pinosLinhas[linhas] = { D0, D1, D2 };
byte pinosColunas[colunas] = { D3, D4, D5 };

Keypad teclado = Keypad(makeKeymap(Teclas), pinosLinhas, pinosColunas, linhas, colunas);

void setup() {
  //botoes de envio, espaço e apagar
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  Serial.begin(9600);

  //configuraçoes do wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("tentando conexao");
  }
  Serial.println("");
  Serial.print("Conectado no IP: ");
  Serial.print(WiFi.localIP());
  Serial.print("Conexão efetuada com sucesso!");

  pegaUsuario();
}

void loop() {

  char teclaClicada = teclado.getKey();

  if (teclaClicada) {  //Se alguma tecla for pressionada
    switch (teclaClicada) {
      case '1':
        aux[0][0] = '1'; break;
      case '2':
        aux[0][1] = '1'; break;
      case '3':
        aux[1][0] = '1'; break;
      case '4':
        aux[1][1] = '1'; break;
      case '5':
        aux[2][0] = '1'; break;
      case '6':
        aux[2][1] = '1'; break;
    }
  }

  if (digitalRead(D5) == LOW) {
    
    for (int i = 0; i < linhas; i++) {
      for (int j = 0; j < colunasAux; j++) {
        auxStg += aux[i][j];
      }
    }

    delay(3000);
    retorno();

    delay(3000);
    enviaDados();

    limpaAux();
  }

  if (digitalRead(D6) == LOW) {
    delay(3000);
    palavra += " ";
    delay(3000);
  }

  if (digitalRead(D7) == LOW) {
    limpa();
  }
}

void pegaUsuario() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName + "/v1/usuarios";

    http.begin(client, serverPath.c_str());

    // realiza o get
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String usuarios = http.getString();
      idUsuario = usuarios.substring(7, 8);
      Serial.print(idUsuario);
      Serial.print(http.getString());
    } else {
      Serial.print(http.getString());
      Serial.print("Erro: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void pegaIdDado() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName + "/v1/dados";

    http.begin(client, serverPath.c_str());

    // realiza o get
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String dados = http.getString();
      int ultimoId = dados.lastIndexOf("id");
      idDado = dados.substring(ultimoId + 4, ultimoId + 5);
    } else {
      Serial.print("Erro: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void atualizaDados() {
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    pegaIdDado();
    String serverPath = serverName + "/v1/dados/" + idDado;

    http.begin(client, serverPath);

    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT("{\"dados\":{ \"dados\": \"" + palavra + "\"}}");

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void enviaDados() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName + "/v1/dados";

    http.begin(client, serverPath);

    // envia letra digitada
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = 0;

    if (palavra.length() == 1) {  //cria nova frase
      httpResponseCode = http.POST("{\"dados\":{ \"usuarioId\":" + idUsuario + ",\"dados\": \"" + palavra + "\"}}");
    } else {  //atualiza frase
      atualizaDados();
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void retorno() {
  if (auxStg == "100000") palavra += "a"; 
  if (auxStg == "101000") palavra += "b";
  if (auxStg == "110000") palavra += "c";
  if (auxStg == "110100") palavra += "d";
  if (auxStg == "100100") palavra += "e";
  if (auxStg == "111000") palavra += "f";
  if (auxStg == "111100") palavra += "g";
  if (auxStg == "101100") palavra += "h";
  if (auxStg == "011000") palavra += "i";
  if (auxStg == "011100") palavra += "j";
  if (auxStg == "100100") palavra += "k";
  if (auxStg == "101010") palavra += "l";
  if (auxStg == "110010") palavra += "m";
  if (auxStg == "110110") palavra += "n";
  if (auxStg == "100110") palavra += "o";
  if (auxStg == "111010") palavra += "p";
  if (auxStg == "111110") palavra += "q";
  if (auxStg == "101110") palavra += "r";
  if (auxStg == "011010") palavra += "s";
  if (auxStg == "011110") palavra += "t";
  if (auxStg == "100011") palavra += "u";
  if (auxStg == "101011") palavra += "v";
  if (auxStg == "011101") palavra += "w";
  if (auxStg == "110011") palavra += "x";
  if (auxStg == "110111") palavra += "y";
  if (auxStg == "100111") palavra += "z"; 
}

void limpa() {
  palavra = "";
}

void limpaAux() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunasAux; j++) {
      aux[i][j] = '0';
    }
  }
  auxStg = "";
}