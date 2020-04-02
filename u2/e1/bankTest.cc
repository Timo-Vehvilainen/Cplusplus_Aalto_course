#include "bank.hh"
#include <string>
#include <iostream>

using namespace std;

int main() {

	string name1 = "Pekka";
	string number1 = "123456";

	BankAccount account1(name1, number1, 500);

	BankAccount account2("Aaro", "098765");

	account1.deposit(1000);

	transfer(account1, account2, 800);

	account1.print();
	account2.print();
	return 0;
}
