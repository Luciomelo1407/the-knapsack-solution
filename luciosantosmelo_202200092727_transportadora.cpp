#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class Vehicle {
public:
  string car_plate;
  int weight_capacity;
  int volume_capacity;
};

class Product {
public:
  string code;
  float value;
  int weight;
  int volume;
};

void loadVehicle(vector<Vehicle> &vehicles, ifstream &input) {
  for (int i = 0; i < vehicles.size(); i++) {
    input >> vehicles[i].car_plate;
    input >> vehicles[i].weight_capacity;
    input >> vehicles[i].volume_capacity;
  }
}

void loadProducts(list<Product> &products, ifstream &input,
                  int product_quantity) {
  Product product;
  for (int i = 0; i < product_quantity; i++) {
    input >> product.code;
    input >> product.value;
    input >> product.weight;
    input >> product.volume;
    products.push_back(product);
  }
}

int main(int argc, char *argv[]) {
  ifstream input(argv[1]);
  int transport_qauntity;
  input >> transport_qauntity;
  vector<Vehicle> veihicles(transport_qauntity);
  loadVehicle(veihicles, input);
  int product_quantity;
  input >> product_quantity;
  list<Product> products;
  loadProducts(products, input, product_quantity);

  return 0;
}
