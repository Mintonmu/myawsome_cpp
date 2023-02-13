#include <iostream>

template <decltype(auto) N> void f() { std::cout << N << std::endl; }

auto main(int argc, char **argv) -> int {

  std::cout << "hello world!" << std::endl;
  return 0;
}
