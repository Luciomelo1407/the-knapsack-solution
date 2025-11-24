#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
// #include <list>

using namespace std;

template <typename T> class list {
private:
  struct Node {
    T *data;
    Node *next;
    Node *previous;
  };
  Node *node, *head, *tail;
  int size;

public:
  list() : size(), node(), head(), tail() {
    size = 0;
    node = nullptr;
    head = nullptr;
    tail = nullptr;
  }

  void push_back(T *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = nullptr;
    new_node->data = data;
    if (size > 0) {
      new_node->previous = node;
      node->next = new_node;
    } else {
      new_node->previous = nullptr;
      head = new_node;
    }
    tail = new_node;
    node = new_node;
    size++;
  }

  void pop() {
    Node *swap = node;
    if (size > 0) {
      node = node->previous;
      node->next = swap->next;
    }
    size--;
    free(swap);
  }

  void forward() {
    if (node->next) {
      node = node->next;
    }
  }

  void back() {
    if (node->previous) {
      node = node->previous;
    }
  }
  void begin() {
    while (node->previous) {
      node = node->previous;
    }
  }
  void end() {
    while (node->next) {
      node = node->next;
    }
  }
};

typedef struct {
  char car_plate[8];
  int weight_capacity;
  int volume_capacity;

} Vehicle;

typedef struct {
  string code;
  float value;
  int weight;
  int volume;
} Product;

void loadVehicle(Vehicle *vehicles, int size, ifstream &input) {
  for (int i = 0; i < size; i++) {
    input >> vehicles[i].car_plate;
    input >> vehicles[i].weight_capacity;
    input >> vehicles[i].volume_capacity;
  }
}

void loadProducts(list<Product> &products, ifstream &input,
                  int product_quantity) {
  for (int i = 0; i < product_quantity; i++) {
    Product *product = (Product *)malloc(sizeof(Product));
    input >> product->code;
    input >> product->value;
    input >> product->weight;
    input >> product->volume;
    products.push_back(product);
  }
}

int main(int argc, char *argv[]) {
  ifstream input(argv[1]);
  int transport_qauntity;
  input >> transport_qauntity;
  Vehicle *vehicles = (Vehicle *)malloc(transport_qauntity * sizeof(Vehicle));
  loadVehicle(vehicles, transport_qauntity, input);
  for (int i = 0; i < transport_qauntity; i++) {
    cout << vehicles[i].car_plate << " ";
    cout << vehicles[i].weight_capacity << " ";
    cout << vehicles[i].volume_capacity << "\n";
  }

  int product_quantity;
  input >> product_quantity;
  int *teste = nullptr;
  list<Product> products;
  loadProducts(products, input, product_quantity);

  return 0;
}
