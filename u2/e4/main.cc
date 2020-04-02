#include "series.hh"
#include <iostream>

int main(void) {
  std::cout << "*** Testing the Fibonacci series with 10 first numbers.." << std::endl;
  Fibonacci f;
  for (size_t i = 0; i < 10; i++)
    std::cout << f() << " ";
  std::cout << f.getIndex() << std::endl;
	Fibonacci fib = Fibonacci(43);
  std::cout << "*** Testing the Fibonacci series with the number in index 42.." << std::endl;
  std::cout << "The number with the index " << fib.getIndex() << " in the Fibonacci series is: " << fib << std::endl;

  std::cout << "*** Testing the OEISA090000 series with 10 first numbers.." << std::endl;
  OEISA090000 o;
  for (size_t i = 0; i < 10; i++)
    std::cout << o() << " ";
  std::cout << std::endl;

  std::cout << "*** Testing the OEISA090000 series with the number in index 90.." << std::endl;
  std::cout << "The number with the index 90 in the OEISA090000 series is: " << OEISA090000(91) << std::endl;

  std::cout << "*** All done, exiting.." << std::endl;

  return 0;
}
