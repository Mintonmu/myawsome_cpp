#include "class_tuple.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  Customer c("Tim", "Starr", 42);
  auto [f, l, v] = c;
  std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << '\n';
  // modify structured bindings via references:
  auto &&[f2, l2, v2] = c;
  std::string s = std::move(f2);
  f2 = "Ringo";
  v2 += 10;
  std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << '\n';
  std::cout << "c: " << c.firstname() << ' ' << c.lastname() << ' ' << c.value()
            << '\n';
  std::cout << "s: " << s << '\n';
  return 0;
}
