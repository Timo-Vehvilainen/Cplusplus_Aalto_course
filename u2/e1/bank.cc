#include "bank.hh"
#include <iostream>

using namespace std;

string BankAccount::getOwner() const {

	return owner;
}

string BankAccount::getNumber() const {

	return accountNumber;
}

double BankAccount::getBalance() const {

	return balance;
}

void BankAccount::deposit(double amount) {

	balance += amount;
	return;
}

bool BankAccount::withdraw(double amount) {

	if (amount <= balance) {
		balance -= amount;
		return true;
	}
	return false;
}

void BankAccount::print() const {

	cout << "Account num: " << accountNumber << ", owned by: " << owner \
	     << ", balance: " << balance << " eur" << endl; 
	return;
}

bool transfer (BankAccount& l, BankAccount& r, double amount) {

	if (l.getBalance() >= amount) {
		r.deposit(amount);
		l.withdraw(amount);
		return true;
	}
	return false;
}
