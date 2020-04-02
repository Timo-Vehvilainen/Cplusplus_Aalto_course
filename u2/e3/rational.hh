#ifndef RATIONAL_HH
#define RATIONAL_HH

#include <utility>
#include <iostream>
#include <algorithm>
#include <cstdlib>

class Rational {
public:
  
  // CONSTRUCTOR:
  //
  // If the denominator is 0, the behaviour is undefined
  // (you can do whatever you want).
  //
  // You do not need to do any error handling in the constructor.
  Rational(int num, int den) : numerator(num), denominator(den){
	normalize(*this);
  }
  
  // CONSTRUCTOR:
  //
  // This creates a rational number which is equal to the integer "num"
  //
  // You do not need to do any error handling in the constructor.
  Rational(int num) : numerator(num), denominator(1) {}

  Rational(const Rational& orig) {
	numerator = orig.getNumerator();
	denominator = orig.getDenominator();
  }
  
  
  // accessors
  int getNumerator() const;
  int getDenominator() const;

  void setNumerator(int num) {
	numerator = num;
	return;
  }
  void setDenominator(int num) {
	denominator = num;
	return;
  }

  

  // You must implement these operators:
  //
  // +=, -=
  // Relational operators
  // <, <=, ==, >=, >, !=
  //
  // Binary operators +, -
  //
  // NOTE: The binary operators + and - should not be members. If they were 
  //       declared as class members, the expression 1 + Rational(1, 2) would 
  //       not work.
  //
  // Unary operator -
  //
  // Input and output operators << and >>
  // so the class can be streamed to and streamed from.
  // The rational number is formatted like this:
  // <numerator> <denominator>
  // For example if numerator is 4 and denominator is 5, the output is
  // 4 5
  // 
  // The output stream operators "normalize" the rational number.
  // For example, 2/4 is written to output as "1 2",
  // 1/-2 is written to output as "-1 2" and -2/-4 is written as
  // "1 2".
  //
  // You can implement these operators either as member functions,
  // or nonmember functions in the namespace scope.  
  Rational operator+= (int number);
  Rational operator-= (int number);
  Rational operator+= (Rational r);
  Rational operator-= (Rational r);
  bool operator< (Rational r);
  bool operator<= (Rational r);
  bool operator== (Rational r);
  bool operator >= (Rational r);
  bool operator > (Rational r);
  bool operator!= (Rational r);


  friend std::istream& operator>> (std::istream& in, Rational& r);
  friend std::ostream& operator<< (std::ostream& out, Rational r);

  friend Rational operator+ (Rational l, Rational r);
  friend Rational operator- (Rational l, Rational r);
  friend Rational operator- (Rational rat);
	
  
private:


  
  int numerator;
  int denominator;
  // This function returns the greatest common divisor
  // for a and b. It is useful for normalizing a rational number.
  //
  // For example 6/9, gcd(6, 9) == 3 so we can divide
  // both the numerator and denominator by 3 to get 2/3.

  Rational normalize(Rational& rat)
  {
    int divisor = gcd(rat.numerator, rat.denominator);
    rat.numerator /= divisor;
    rat.denominator /= divisor;
    return rat;
  }

  static int gcd(int a, int b)
  {
    using std::swap;
    a = std::abs(a);
    b = std::abs(b);
    if (a>b) swap(a,b);
    while (a)
    {
      	b %= a;
      	swap(a,b);
    }
    return b;
  }
  
  
  
};

#endif
