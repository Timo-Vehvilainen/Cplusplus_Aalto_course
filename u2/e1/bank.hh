#ifndef ELEC_AS_BANK_HH
#define ELEC_AS_BANK_HH

#include <string>

class BankAccount {

private:
	std::string owner;
	std::string accountNumber;
	double balance;
public:
	BankAccount (std::string const& owner, std::string const& number, double balance = 0) :
		owner(owner), accountNumber(number), balance(balance) { }

	std::string getOwner() const;
	std::string getNumber() const;
	double getBalance() const;

	void deposit(double amount);
	bool withdraw(double amount);
	
	void print() const;
};

bool transfer (BankAccount& l, BankAccount& r, double amount);

#endif
