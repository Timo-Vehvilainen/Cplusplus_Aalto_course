#ifndef SERIES_HH
#define SERIES_HH

#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

class Fibonacci {
public:

    Fibonacci() : nMinusOne (0), nMinusTwo (0), n(0), index(0) {index--;}

    Fibonacci(size_t input);

	size_t operator() ();

	size_t getIndex() const;

	friend std::ostream& operator<< (std::ostream& out, Fibonacci fib);
private:


    size_t nMinusOne;
    size_t nMinusTwo;
	size_t n;
	size_t index;
};





class OEISA090000 {
public:

	OEISA090000() : n(0), currentNumber(1) {}

	OEISA090000(size_t number);

	size_t getIndex() const;

	size_t operator() ();

	friend std::ostream& operator<< (std::ostream& out, OEISA090000 oei);

	void findMostOnesTester() {
	std::cout << "The first 10 primes are:\n";
	for (size_t i = 0; i < 10; i++)
		std::cout << getNthPrime(i) << " ";
	std::cout << std::endl;
	std::cout << "Their binary representations are: \n";
	for (size_t i = 0; i < 10; i++)
		std::cout << toBinary(getNthPrime(i)) << " ";
	std::cout << std::endl;
	std::cout << "Their OEISA090000 numbers are: \n";
	for (size_t i = 0; i < 10; i++)
		std::cout << findMostOnes(toBinary(getNthPrime(i))) << " ";
	std::cout << std::endl;
	return;
	}
private:

	size_t n;
	size_t currentNumber;

	bool isPrime(size_t testerNumber) {
		if (testerNumber == 3 || testerNumber == 5 || testerNumber == 7)
			return true;
		if (testerNumber % 2  == 0)
			return false;

		for (size_t counter = 2; counter <= sqrt(testerNumber); counter++){
			if (testerNumber % counter == 0)
				return false;
		}
		return true;
	}
	
	size_t getNthPrime(size_t s) {

		if (s == 0)
			return 2;
		s++;

		size_t primeCounter = 1;
		size_t testerNumber = 3;
		while (primeCounter < s) {
			if (isPrime(testerNumber)) {
				primeCounter++;
				testerNumber += 2;
			} else  {
				testerNumber += 2;
			}
		}
		return (testerNumber - 2);
	}

	std::string toBinary(size_t n){
		std::string ret = std::bitset<32>(n).to_string();
		return ret;
	}

 	size_t findMostOnes(std::string binary) {
		size_t longestSoFar = 0;
		size_t currentCount = 0;
		std::string::iterator Iter = binary.begin();
		while (Iter != binary.end()) {
			if (*Iter == '1') {
				currentCount++;
				Iter++;
			} else {
				if (currentCount > longestSoFar)
					longestSoFar = currentCount;
				currentCount = 0;
				Iter++;
			}
		}
		if (currentCount > longestSoFar)
			longestSoFar = currentCount;
		return longestSoFar;
 		}
 		

	
};
#endif
