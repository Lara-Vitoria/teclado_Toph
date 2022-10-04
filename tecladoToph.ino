#include "Keypad.h"

const byte linhas = 3;
const byte colunas = 3;
const byte colunasAux = 2;

char Teclas[linhas][colunas] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
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
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  Serial.begin(9600);
}

void loop() {

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
        limpa();
        break;
      case '4':
        aux[1][0] = '1';
        break;
      case '5':
        aux[1][1] = '1';
        break;
      case '6':
        auxStg += "|";
        palavra += "|";
        Serial.println(auxStg);
        break;
      case '7':
        aux[2][0] = '1';
        break;
      case '8':
        aux[2][1] = '1';
        break;
      case '9':
        for (int i = 0; i < linhas; i++) {
          for (int j = 0; j < colunasAux; j++) {
            auxStg += aux[i][j];
          }
        }
        Serial.println(auxStg);  //Exibe letra completa
        Serial.println(retorno());
        Serial.println(palavra);
        limpa();
        break;
    }
  }
}

String retorno() {
  if (auxStg == "100000") {
    palavra += "a";
    return "a";
  }
  if (auxStg == "101000") {
    palavra += "b";
    return "b";
  }
  if (auxStg == "110000") {
    palavra += "c";
    return "c";
  }
  if (auxStg == "110100") {
    palavra += "d";
    return "d";
  }
  if (auxStg == "100100") {
    palavra += "e";
    return "e";
  }
  if (auxStg == "111000") {
    palavra += "f";
    return "f";
  }
  if (auxStg == "111100") {
    palavra += "g";
    return "g";
  }
  if (auxStg == "101100") {
    palavra += "h";
    return "h";
  }
  if (auxStg == "011000") {
    palavra += "i";
    return "i";
  }
  if (auxStg == "011100") {
    palavra += "j";
    return "j";
  }
  if (auxStg == "100100") {
    palavra += "k";
    return "k";
  }
  if (auxStg == "101010") {
    palavra += "l";
  }
  if (auxStg == "110010") {
    palavra += "m";
  }
  if (auxStg == "110110") {
    palavra += "n";
  }
  if (auxStg == "100110") {
    palavra += "o";
  }
  if (auxStg == "111010") {
    palavra += "p";
  }
  if (auxStg == "111110") {
    palavra += "q";
  }
  if (auxStg == "101110") {
    palavra += "r";
  }
  if (auxStg == "011010") {
    palavra += "s";
  }
  if (auxStg == "011110") {
    palavra += "t";
  }
  if (auxStg == "100011") {
    palavra += "u";
  }
  if (auxStg == "101011") {
    palavra += "v";
  }
  if (auxStg == "011101") {
    palavra += "w";
  }
  if (auxStg == "110011") {
    palavra += "x";
  }
  if (auxStg == "110111") {
    palavra += "y";
  }
  if (auxStg == "100111") {
    palavra += "z";
  } else {
    return "invalido";
  }
}

void limpa() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunasAux; j++) {
      aux[i][j] = '0';
    }
  }
  auxStg = "";
}