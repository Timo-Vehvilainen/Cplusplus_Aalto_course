#include "rational.hh"

using namespace std;

int Rational::getNumerator() const {
	return numerator;
}

int Rational::getDenominator() const{
	return denominator;
}
  Rational Rational::operator+= (int number) {
	numerator += (number*(denominator));
	normalize(*this);
	return (*this);
  }

  Rational Rational::operator-= (int number) {
	numerator -= (number*denominator);
	normalize(*this);
	return (*this);
  }

  Rational Rational::operator+= (Rational rat) {
	numerator *= rat.getDenominator();	
	numerator += (denominator * rat.getNumerator());
	denominator *= rat.getDenominator();
	normalize(*this);
	return (*this);
  }

  Rational Rational::operator-= (Rational rat) {
	numerator *= rat.getDenominator();	
	numerator -= (denominator * rat.getNumerator());
	denominator *= rat.getDenominator();
	normalize(*this);
	return (*this);
  }
 
  bool Rational::operator< (Rational r) {
	if (((this->numerator) / ((double)(this->denominator))) < ((r.getNumerator())/((double)r.getDenominator())))
		return true;
	return false;
  }

  bool Rational::operator<= (Rational r) {
	if ((numerator / ((double)denominator)) <= ((r.getNumerator())/((double)r.getDenominator())))
		return true;
	return false;
 }

  bool Rational::operator== (Rational r) {
	if ((this->numerator == r.numerator) && (this->denominator == r.denominator))
		return true;
	return false;
}

  bool Rational::operator >= (Rational r) {
	if (((this->numerator) / ((double)(this->denominator))) >= ((r.getNumerator())/((double)r.getDenominator())))
		return true;
	return false;
  }

  bool Rational::operator > (Rational r) {
	if (((this->numerator) / ((double)(this->denominator))) > ((r.getNumerator())/((double)r.getDenominator())))
		return true;
	return false;
  }

  bool Rational::operator!= (Rational r) {
	if (((this->numerator) / ((double)(this->denominator))) != ((r.getNumerator())/((double)r.getDenominator())))
		return true;
	return false;
  }

  istream& operator>> (istream& in, Rational& r) {
	int num1;
	int num2;
	in >> num1;
	in >> num2;
	if (!in.fail()) {
		r.setNumerator(num1);
		r.setDenominator(num2);
	}	
	return in;
  }

  ostream& operator<< (ostream& out, Rational r) {
	out << r.getNumerator() << " " << r.getDenominator();
	return out;
  }

  Rational operator+ (Rational l, Rational r) {
	return (l += r);
  }
  Rational operator- (Rational l, Rational r) {
	return (l -= r);
  }
  Rational operator- (Rational rat) {
	rat.numerator *= -1;
	return rat;
  }

  
