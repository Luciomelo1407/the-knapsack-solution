#include <fstream>
#include <iostream>
#include <stdbool.h>

typedef struct {
  char plate[8];
  int weight;
  int volume;
} Transport;

typedef struct {
  char code[14];
  float value;
  int weight;
  int volume;
  bool avalible;
} Products;

using namespace std;

Transport *loadTransport(int transport_quantity, ifstream &input,
                         ofstream &output) {
  Transport *transports =
      (Transport *)malloc(transport_quantity * sizeof(Transport));
  int biggestWeight = -1;
  int biggestVolume = -1;
  for (int i = 0; i < transport_quantity; i++) {
    input >> transports[i].plate;
    input >> transports[i].weight;
    input >> transports[i].volume;
    if (biggestWeight < transports[i].weight) {
      biggestWeight = transports[i].weight;
    }
    if (biggestVolume < transports[i].volume) {
      biggestVolume = transports[i].volume;
    }
  }
  cout << "Maior peso suportado: " << biggestWeight << "\n";
  cout << "Maior volume suportado: " << biggestVolume << "\n";

  output << "Maior peso suportado: " << biggestWeight << "\n";
  output << "Maior volume suportado: " << biggestVolume << "\n";
  return transports;
}

int main(int argc, char *argv[]) {
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int transport_quantity;
  input >> transport_quantity;

  Transport *transports = loadTransport(transport_quantity, input, output);

  int products_quantity;
  input >> products_quantity;

  cout << "quantidade de itens: " << products_quantity << "\n";
  output << "quantidade de itens: " << products_quantity << "\n";

  return 0;
}
