#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Keypad.h"

//conexao wifi
const char* ssid = "BEST FAMILY_EXT";
const char* password = "pedroasafe";

//web server
ESP8266WebServer server(80);

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
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("tentando conexao");
  }
  Serial.println("");
  Serial.print("Conectado no IP: " );
  Serial.print(WiFi.localIP());
  Serial.print("Conexão efetuada com sucesso!");

  //inicia web server
  server.begin();
  Serial.println("web server iniciado");
  delay(500);
  Serial.println("acesse o endereço pelo: ");
  Serial.print(WiFi.localIP());

  server.on("/", [](){
    server.send(200, "req", "servidor do nodemcu");
  });

  server.on("/dados", [](){
    server.send(200, "cabeçalho", palavra);
  });
}

void loop() {

  server.handleClient();

  char teclaClicada = teclado.getKey();

  if (teclaClicada) {  //Se alguma tecla for pressionada
    switch (teclaClicada) {
      case '1':
        aux[0][0] = '1';
        break;
      case '2':
        aux[0][1] = '1';
        break;
      case '3':
        aux[1][0] = '1';
        break;
      case '4':
        aux[1][1] = '1';
        break;
      case '5':
        aux[2][0] = '1';
        break;
      case '6':
        aux[2][1] = '1';
        break;
    }
  }

  if(digitalRead(D5)==LOW)
  {
    for (int i = 0; i < linhas; i++) {
      for (int j = 0; j < colunasAux; j++) {
          auxStg += aux[i][j];
        }
    }
    Serial.println(auxStg);  //Exibe letra completa
    Serial.println(retorno());
    Serial.println(palavra);
    limpa();
  }

  if(digitalRead(D6)==LOW)
  {
    auxStg += "|";
    palavra += "|";
    Serial.println(auxStg);
  }

  if(digitalRead(D7)==LOW)
  {
    limpa();
  }
}

String retorno() {
  if(auxStg == "100000"){palavra += "a"; return "a";}
  if(auxStg == "101000"){palavra += "b";return "b";}
  if(auxStg == "110000"){palavra += "c";return "c";}
  if(auxStg == "110100"){palavra += "d";return "d";}
  if(auxStg == "100100"){palavra += "e";return "e";}
  if(auxStg == "111000"){palavra += "f";return "f";}
  if(auxStg == "111100"){palavra += "g";return "g";}
  if(auxStg == "101100"){palavra += "h";return "h";}
  if(auxStg == "011000"){palavra += "i";return "i";}
  if(auxStg == "011100"){palavra += "j";return "j";}
  if(auxStg == "100100"){palavra += "k";return "k";}
  if(auxStg == "101010"){palavra += "l";return "l";}
  if(auxStg == "110010"){palavra += "m";return "m";}
  if(auxStg == "110110"){palavra += "n";return "n";}
  if(auxStg == "100110"){palavra += "o";return "o";}
  if(auxStg == "111010"){palavra += "p";return "p";}
  if(auxStg == "111110"){palavra += "q";return "q";}
  if(auxStg == "101110"){palavra += "r";return "r";}
  if(auxStg == "011010"){palavra += "s";return "s";}
  if(auxStg == "011110"){palavra += "t";return "t";}
  if(auxStg == "100011"){palavra += "u";return "u";}
  if(auxStg == "101011"){palavra += "v";return "v";}
  if(auxStg == "011101"){palavra += "w";return "w";}
  if(auxStg == "110011"){palavra += "x";return "x";}
  if(auxStg == "110111"){palavra += "y";return "y";}
  if(auxStg == "100111"){palavra += "z";return "z";}
  else{return "invalido";}
}

void limpa() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunasAux; j++) {
      aux[i][j] = '0';
    }
  }
  auxStg = "";
}