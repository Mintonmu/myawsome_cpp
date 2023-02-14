#include <iostream>

template <decltype(auto) N> void f() { std::cout << N << std::endl; }

class X {
public:
  X() { std::cout << "X ctor" << std::endl; }
  X(const X &xxx) { std::cout << "X copy ctor" << std::endl; }
  ~X() { std::cout << "X dtor" << std::endl; }
  void show() { std::cout << "show X" << std::endl; }
};

auto make_x() -> X {
  X x1x;
  return x1x;
}

auto main(int argc, char **argv) -> int {

  X &&x2x = make_x();
  x2x.show();

  //! &“hello world” 是一个左值 并非是一个右值
  //* 编译器会将字符串字面量存储到程序的数据段中，程序加载的时候也会为其开辟内存空间，所以我们可以使用取地址符&来获取字符串字面量的内存地址
  auto p_str = &"hello world";

  return 0;
}
