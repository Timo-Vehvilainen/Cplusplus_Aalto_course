#include "printers.hh"
#include "diagonal_printer.hh"
#include "standard_printer.hh"
#include <iostream>
#include <string>

int main() {
	DiagonalPrinter diag;
	diag("Ohh yeah!");
	Printers printers;
	printers.add("Diagonal", &diag);
	(printers["Diagonal"])("Diagonal string yeah!");
	
	return 0;
}
