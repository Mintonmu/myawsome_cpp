#ifndef AC768F20_CBFD_487D_B356_2EE693038A7A
#define AC768F20_CBFD_487D_B356_2EE693038A7A
#include <iostream>

// class Customer {
// private:
//   std::string first;
//   std::string last;
//   long val;

// public:
//   Customer(std::string f, std::string l, long v)
//       : first(std::move(f)), last(std::move(l)), val(v) {}
//   std::string getFirst() const { return first; }
//   std::string getLast() const { return last; }
//   long getValue() const { return val; }
// };
class Customer {
private:
  std::string first;
  std::string last;
  long val;

public:
  Customer(std::string f, std::string l, long v)
      : first(std::move(f)), last(std::move(l)), val(v) {}
  const std::string &firstname() const { return first; }
  std::string &firstname() { return first; }
  const std::string &lastname() const { return last; }
  std::string &lastname() { return last; }
  long value() const { return val; }
  long &value() { return val; }
};

template <> struct std::tuple_size<Customer> {
  static constexpr int value = 3;
};
template <> struct std::tuple_element<2, Customer> {
  using type = long;
};

template <std::size_t Idx> struct std::tuple_element<Idx, Customer> {
  using type = std::string;
};
// template <std::size_t> auto get(const Customer &c);
// template <> auto get<0>(const Customer &c) { return c.getFirst(); }
// template <> auto get<1>(const Customer &c) { return c.getLast(); }
// template <> auto get<2>(const Customer &c) { return c.getValue(); }
// define specific getters:
// template <std::size_t I> auto get(const Customer &c) {
//   static_assert(I < 3, "");
//   if constexpr (I == 0) {
//     return c.getFirst();
//   } else if constexpr (I == 1) {
//     return c.getLast();
//   } else { // I == 2
//     return c.getValue();
//   }
// }
template <std::size_t I> decltype(auto) get(Customer &c) {
  static_assert(I < 3);
  if constexpr (I == 0) {
    return c.firstname();
  } else if constexpr (I == 1) {
    return c.lastname();
  } else { // I == 2
    return c.value();
  }
}
template <std::size_t I> decltype(auto) get(const Customer &c) {
  static_assert(I < 3);
  if constexpr (I == 0) {
    return c.firstname();
  } else if constexpr (I == 1) {
    return c.lastname();
  } else { // I == 2
    return c.value();
  }
}
template <std::size_t I> decltype(auto) get(Customer &&c) {
  static_assert(I < 3, "");
  if constexpr (I == 0) {
    return std::move(c.firstname());
  } else if constexpr (I == 1) {
    return std::move(c.lastname());
  } else { // I == 2
    return c.value();
  }
}
// 支持非const对象
template <std::size_t> decltype(auto) get(Customer &c);
template <> decltype(auto) get<0>(Customer &c) { return c.firstname(); }
template <> decltype(auto) get<1>(Customer &c) { return c.lastname(); }
template <> decltype(auto) get<2>(Customer &c) { return c.value(); }
// 支持const对象
template <std::size_t> auto get(const Customer &c);
template <> auto get<0>(const Customer &c) { return c.firstname(); }
template <> auto get<1>(const Customer &c) { return c.lastname(); }
template <> auto get<2>(const Customer &c) { return c.value(); }

// 支持移动对象
template <std::size_t> decltype(auto) get(Customer &&c);
template <> decltype(auto) get<0>(Customer &&c) {
  return std::move(c.firstname());
}
template <> decltype(auto) get<1>(Customer &&c) {
  return std::move(c.lastname());
}
template <> decltype(auto) get<2>(Customer &&c) { return std::move(c.value()); }

#endif /* AC768F20_CBFD_487D_B356_2EE693038A7A */
