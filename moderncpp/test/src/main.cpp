#include <iostream>
#include <string>
template <decltype(auto) N> void f() { std::cout << N << std::endl; }

template <class T> void show_type(T tparam) {
  std::cout << typeid(tparam).name() << std::endl;
}

template <class T> void normal_forwarding(T &&tparam) {
  // show_type(static_cast<T &&>(tparam));
  show_type(std::forward<T>(tparam));
}
class X {
public:
  X() { std::cout << "X ctor" << std::endl; }
  X(const X &xxx) { std::cout << "X copy ctor" << std::endl; }
  ~X() { std::cout << "X dtor" << std::endl; }
  void show() { std::cout << "show X" << std::endl; }
};

struct type {
  type(long long) {}
  explicit type(long) = delete;
};
void foo(type) {}

auto make_x() -> X {
  X x1x;
  return x1x;
}

auto main(int argc, char **argv) -> int {
  // foo(type(58));
  foo(type(static_cast<long long>(58)));
  foo(58);

  // std::string str = "hello world";
  // normal_forwarding(str);
  // X &&x2x = make_x();
  // x2x.show();
  // //! &“hello world” 是一个左值 并非是一个右值
  // //*
  // 编译器会将字符串字面量存储到程序的数据段中，程序加载的时候也会为其开辟内存空间，所以我们可以使用取地址符&来获取字符串字面量的内存地址
  // auto p_str = &"hello world";

  return 0;
}
