#include <iostream>

int main(int argc, char *argv[]) {
  int teste[10] = {0};
  for (int i = 0; i < 10; i++) {
    std::cout << teste[i] << ",";
  }
  std::cout << "\n";
  int *teste2 = teste;
  for (int i = 0; i < 10; i++) {
    std::cout << teste2[i] << ",";
  }
  return 0;
}
