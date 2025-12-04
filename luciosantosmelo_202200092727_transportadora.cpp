

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdbool.h>
using namespace std;

// TODO: remamber to use that in the finished project;
//  #define MAX_WEIGHT 100
//  #define MAX_VOLUME 100
#define MAX_WEIGHT 2000
#define MAX_VOLUME 12000

const int MAX_weight = MAX_WEIGHT;
const int MAX_volume = MAX_VOLUME;

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
} Product;

Transport *loadTransport(int transport_quantity, ifstream &input) {
  Transport *transports =
      (Transport *)malloc(transport_quantity * sizeof(Transport));
  for (int i = 0; i < transport_quantity; i++) {
    input >> transports[i].plate;
    input >> transports[i].weight;
    input >> transports[i].volume;
  }
  return transports;
}

Product *loadProducts(int products_quantity, ifstream &input) {
  Product *products = (Product *)malloc(products_quantity * sizeof(Product));
  for (int i = 0; i < 13; i++) {
    products[0].code[i] = '0';
  }
  products[0].code[13] = '\0';
  products[0].value = 0;
  products[0].weight = 0;
  products[0].volume = 0;
  products[0].avalible = false;
  for (int i = 1; i < products_quantity; i++) {
    input >> products[i].code;
    input >> products[i].value;
    input >> products[i].weight;
    input >> products[i].volume;
    products[i].avalible = true;
  }
  return products;
}

void showProduct(Product product) {
  cout << product.code << " " << product.value << " " << product.weight << " "
       << product.volume << " " << product.avalible << "\n";
}

void showProducts(Product *products, int products_quantity) {
  for (int i = 0; i < products_quantity; i++) {
    showProduct(products[i]);
  }
}

void showTransport(Transport transport) {
  cout << transport.plate << " " << transport.weight << " " << transport.volume
       << "\n";
}

void showTransports(Transport *transports, int transport_quantity) {
  for (int i = 0; i < transport_quantity; i++) {
    showTransport(transports[i]);
  }
}

float max(float v1, float v2) {
  if (v1 > v2) {
    return v1;
  }
  return v2;
}

void buildMatrix(float ***values, int products_quantity, Product *products);

void backTrack(float ***values, int products_quantity, Product *products,
               Transport transport, ofstream &output) {
  int limit = 100;
  Product *products_filled = (Product *)malloc(limit * sizeof(Product));
  int products_filled_size = 0;
  int weight_filled = 0;
  int volume_filled = 0;
  float totalValue = 0;
  int w = transport.weight;
  int v = transport.volume;
  for (int p = products_quantity - 1; p > 0; p--) {
    if ((values[p][w][v] > values[p - 1][w][v]) && products[p].avalible) {
      products[p].avalible = false;
      if (products_filled_size == limit - 1) {
        cout << "Cabou o espaço para itens dentro do buffer" << "\n";
        break;
      }
      products_filled[products_filled_size] = products[p];
      products_filled_size++;
      weight_filled += products[p].weight;
      volume_filled += products[p].volume;
      totalValue += products[p].value;

      w -= products[p].weight;
      v -= products[p].volume;
    }
  }
  output << '[' << transport.plate << "]R$" << totalValue << ','
         << weight_filled << "KG("
         << round(((double)weight_filled / (double)transport.weight) * 100)
         << "%)," << volume_filled << "L("
         << round(((double)volume_filled / (double)transport.volume) * 100)
         << "%)->";
  for (int i = products_filled_size - 1; i >= 0; i--) {
    output << products_filled[i].code;
    if (i > 0) {
      output << ",";
    }
  }
  output << "\n";
  free(products_filled);
}

int main(int argc, char *argv[]) {
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int transport_quantity;
  input >> transport_quantity;

  Transport *transports = loadTransport(transport_quantity, input);

  int products_quantity;
  input >> products_quantity;
  products_quantity++;

  Product *products = loadProducts(products_quantity, input);

  float ***valueMatrix =
      (float ***)malloc(products_quantity * sizeof(float **));
  if (valueMatrix == NULL) {
    cerr << "Erro: Memoria insuficiente para a matriz." << endl;
    return 1;
  }
  for (int i = 0; i < products_quantity; i++) {
    valueMatrix[i] = (float **)malloc((MAX_WEIGHT + 1) * sizeof(float *));
    for (int w = 0; w <= MAX_WEIGHT; w++) {
      valueMatrix[i][w] = (float *)malloc((MAX_VOLUME + 1) * sizeof(float));
    }
  }

  for (int i = 0; i < transport_quantity; i++) {
    buildMatrix(valueMatrix, products_quantity, products);
    backTrack(valueMatrix, products_quantity, products, transports[i], output);
  }

  float rest_value = 0;
  int rest_weight = 0;
  int rest_volume = 0;
  for (int i = 0; i < products_quantity; i++) {
    if (products[i].avalible) {
      rest_value += products[i].value;
      rest_weight += products[i].weight;
      rest_volume += products[i].volume;
    }
  }
  output << "PENDENTE:R$" << rest_value << "," << rest_weight << "KG,"
         << rest_volume << "L->";

  for (int i = 0; i < products_quantity; i++) {
    if (products[i].avalible) {
      output << products[i].code << ",";
    }
  }
  return 0;
}

void buildMatrix(float ***values, int products_quantity, Product *products) {
  for (int p = 0; p < products_quantity; p++) {
    for (int w = 0; w <= MAX_weight; w++) {
      for (int v = 0; v <= MAX_volume; v++) {
        if (p == 0 || w == 0 || v == 0) {
          values[p][w][v] = 0;
        } else {
          if ((w - products[p].weight < 0) || (v - products[p].volume < 0) ||
              !products[p].avalible) {
            values[p][w][v] = values[p - 1][w][v];
          } else {
            values[p][w][v] = max(
                values[p - 1][w][v],
                values[p - 1][w - products[p].weight][v - products[p].volume] +
                    products[p].value);
          }
        }
      }
    }
  }
}
