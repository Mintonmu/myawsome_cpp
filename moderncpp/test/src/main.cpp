#include <array>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

class IntIter {
public:
  IntIter(int *p) : p_(p) {}
  auto operator!=(const IntIter &other) -> bool { return (p_ != other.p_); }
  auto operator++() -> const IntIter & {
    p_++;
    return *this;
  }
  auto operator*() const -> int { return *p_; }

private:
  int *p_;
};

template <unsigned int fix_size> class FixIntVector {
public:
  FixIntVector(std::initializer_list<int> init_list) {
    int *cur = data_.data();
    for (auto e : init_list) {
      *cur = e;
      cur++;
    }
  }
  auto begin() -> IntIter {
    return IntIter(data_.data());
    ;
  }

  auto end() -> IntIter { return IntIter(data_.data() + fix_size); }

private:
  std::array<int, fix_size> data_{0};
};

struct BindTest {

  int a = 42;
  std::string b = "hello structured binding";
};
using std::cout, std::endl;
class MyString : public std::string {};

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

const auto &y_var = [](const auto &f_fun) {
  return [&](const auto &x_var) {
    return x(x_var);
  }([&](const auto &x_var) -> std::function<int(int)> {
    return f_fun([&](const int &n) { return x(x_var)(n); });
  });
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

  FixIntVector<10> fix_int_vector{1, 3, 5, 7, 9};
  for (auto e : fix_int_vector) {
    std::cout << e << std::endl;
  }
  std::vector<BindTest> bt{{11, "hello"}, {7, "c++"}};
  for (const auto &[x, y] : bt) {
    std::cout << "x=" << x << " y=" << y << std::endl;
  }
  // BindTest bt;
  // const auto [x, y] = bt;
  // std::cout << "&bt.a=" << &bt.a << " &x=" << &x << std::endl;
  // std::cout << "&bt.b=" << &bt.b << " &y=" << &y << std::endl;
  // std::cout << "std::is_same_v<const int, decltype(x)>="
  //           << std::is_same_v<const int, decltype(x)> << std::endl;
  // std::cout << "std::is_same_v<const std::string, decltype(y)>="
  //           << std::is_same_v<const std::string, decltype(y)> << std::endl;

  // cout << std::boolalpha;
  // int i_var = 123;
  // int &ri_var = i_var;

  // typedef std::add_pointer_t<decltype(i_var)> IntPtr1;
  // typedef std::add_pointer_t<decltype(ri_var)> IntPtr2;

  // IntPtr1 pi_var = &i_var;
  // cout << "i = " << i_var << "\n";
  // cout << "*pi = " << *pi_var << "\n";

  // static_assert(std::is_pointer<IntPtr1>::value, "IntPtr should be a
  // pointer"); static_assert(std::is_same<IntPtr1, int *>::value,
  //               "IntPtr should be a pointer to int");
  // static_assert(std::is_same<IntPtr2, IntPtr1>::value,
  //               "IntPtr2 should be equal to IntPtr");

  // foo(type(58));
  // foo(type(static_cast<long long>(58)));
  // foo(58);

  // std::string str = "hello world";
  // normal_forwarding(str);
  // X &&x2x = make_x();
  // x2x.show();
  // //! &“hello world” 是一个左值 并非是一个右值
  // //*
  // 编译器会将字符串字面量存储到程序的数据段中，程序加载的时候也会为其开辟内存空间，所以我们可以使用取地址符&来获取字符串字面量的内存地址
  // auto p_str = &"hello world";
  // cout << "std::is_aggregate_v<std::string> = "
  //      << std::is_aggregate_v<std::string> << endl;
  // cout << "std::is_aggregate_v<MyString> = "
  //      << std::is_aggregate_v<MyString> << endl;
  return 0;
}
