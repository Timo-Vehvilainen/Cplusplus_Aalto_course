#include "series.hh"

using namespace std;

Fibonacci::Fibonacci(size_t n) : nMinusOne (0), nMinusTwo (0), n(0), index(0){
	for (size_t counter = 0; counter < n - 1; counter++)
		(*this)();
}

size_t Fibonacci::operator() () {
	if (index == 0) {
		n = 1;
	}
	
	size_t temp = n;
	
	n = nMinusOne + temp;
	nMinusTwo = nMinusOne;
	nMinusOne = temp;
	
	index++;
	return nMinusOne;
}

size_t Fibonacci::getIndex() const {
	return (index+1);
}

ostream& operator<< (ostream& out, Fibonacci fib) {
	out << (fib.nMinusOne);
	return out;
}

OEISA090000::OEISA090000(size_t number) : n(0), currentNumber(1) {
	for (size_t counter = 0; counter < number; counter++)
		(*this)();
}

size_t OEISA090000::getIndex() const {
	return (n);
}

size_t OEISA090000::operator() () {
		
		size_t prime = getNthPrime(n);
		string binary = toBinary(prime);
		currentNumber = findMostOnes(binary);

		n++;
		return currentNumber;
	}

ostream& operator<< (ostream& out, OEISA090000 oei) {
	out << oei.currentNumber;
	return out;
}
