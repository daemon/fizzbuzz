// Compile-time fizzbuzz.
// g++ -std=c++11 [-DFIZZBUZZ_N=x] [-ftemplate-depth=x+2] fizzbuzz.cpp
// Fizzbuzzes from 1 to FIZZBUZZ_N, which defaults to 100.
#include <iostream>
#include <type_traits>

template<int A, int B>
struct greater_than
{
  static constexpr bool value = A > B;
};

template <int A, int B>
struct divides
{
  static constexpr bool value = A % B == 0;
};

template <int A, int B>
struct not_divides
{
  static constexpr bool value = A % B != 0;
};

template<int N, int n, typename E = void>
struct fizzbuzz_helper
{
  static inline constexpr void run()
  {
    std::cout << n << std::endl;
    fizzbuzz_helper<N, n + 1>::run();
  }
};

template<int N, int n>
struct fizzbuzz_helper<N, n, typename std::enable_if<std::conditional<greater_than<n, N>::value,
  std::true_type, std::false_type>::type::value>::type>
{
  static inline constexpr void run()
  {
    return;
  }
};

template<int N, int n>
struct fizzbuzz_helper<N, n, typename std::enable_if<std::conditional<divides<n, 3>::value && 
  divides<n, 5>::value && greater_than<N, n - 1>::value, std::true_type, std::false_type>::type::value>::type>
{
  static inline constexpr void run()
  {
    std::cout << "FizzBuzz" << std::endl;
    fizzbuzz_helper<N, n + 1>::run();
  }
};

template<int N, int n>
struct fizzbuzz_helper<N, n, typename std::enable_if<std::conditional<divides<n, 3>::value && 
   not_divides<n, 5>::value && greater_than<N, n - 1>::value, std::true_type, std::false_type>::type::value>::type>
{
  static inline constexpr void run()
  {
    std::cout << "Fizz" << std::endl;
    fizzbuzz_helper<N, n + 1>::run();
  }
};

template<int N, int n>
struct fizzbuzz_helper<N, n, typename std::enable_if<std::conditional<divides<n, 5>::value &&
  not_divides<n, 3>::value && greater_than<N, n - 1>::value, std::true_type, std::false_type>::type::value>::type>
{
  static inline constexpr void run()
  {
    std::cout << "Buzz" << std::endl;
    fizzbuzz_helper<N, n + 1>::run();
  }
};

template<int N, typename = void>
struct fizzbuzz;

template<int N>
struct fizzbuzz<N, typename std::enable_if<greater_than<N, 0>::value>::type>
{
  static inline constexpr void run()
  {
    fizzbuzz_helper<N, 1>::run();
  }
};

int main()
{
#ifndef FIZZBUZZ_N
#define FIZZBUZZ_N 100
#endif
  fizzbuzz<FIZZBUZZ_N>::run();
  return 0;
}