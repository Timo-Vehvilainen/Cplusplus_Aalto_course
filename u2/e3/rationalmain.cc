

#include "rational.hh"
#include <iostream>
#include <sstream>
int main() {
  
  using std::cout; using std::endl;
  
  // Test construction

  cout << "--- testing constructors and operator << ---" << endl;
  cout << "1 2 == " << Rational(1, 2) << endl; // 1 2
  cout << "5 1 == " << Rational(5) << endl;
  cout << "3 4 == " << Rational(Rational(3, 4)) << endl;
  // Test normalization
  cout << "--- testing normalization ---" << endl;
  cout << "1 2 == " << Rational(2, 4) << endl;
  cout << "-1 3 == " << Rational(-2, 6) << endl;
  
  // Test operator +=, -=
  cout << "--- testing operators += and -= ---" << endl;
  
  {  
    Rational r(1, 1);
    r += 5;
    cout << "6 1 == " << r << endl;
    r -= Rational(1, 2);
    cout << "11 2 == " << r << endl;
  }
  cout << "--- testing operators + and - ---" << endl;

  std::cout << "7 3 == " << (Rational(4, 3) + 1) << endl;
  std::cout << "1 1 == " << (Rational(4, 3) - Rational(1, 3)) << endl;
  std::cout << "7 3 == " << (1 + Rational(4, 3)) << endl;

  cout << "--- testing relational operators (==, !=, <, >) ---" << endl;

  cout << "1 == " << (Rational(1, 2) == Rational(2, 4)) << endl;
  cout << "0 == " << (Rational(1, 2) == Rational(2, 3)) << endl;
  cout << "1 == " << (Rational(1, 2) != Rational(2, 3)) << endl;
  cout << "1 == " << (Rational(1, 2) < Rational(2, 3)) << endl;
  cout << "1 == " << (Rational(2, 3) > Rational(1, 2)) << endl;
  
  cout << "--- testing the input operator (>>) ---" << endl;
  std::istringstream is("1 5"); Rational r(1, 1); is >> r;
  cout << "1 5 == " << r << endl;;

  is.clear(); is.str("5 foobar");
  is >> r; // does not modify r, does not throw exceptions.
           // is.fail() becomes true.
  cout << "1 5 == " << r << endl;;
  

  cout << "--- testing unary - ---" << endl;
  cout << "-1 2 == " << -Rational(1, 2) << endl;
  

}
