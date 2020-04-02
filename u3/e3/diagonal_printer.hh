#ifndef TKK_AS_CPP_DIAGONAL_HH
#define TKK_AS_CPP_DIAGONAL_HH

#include "printer.hh"

/* Implement the class DiagonalPrinter here
 * The class inherits (public inheritance) class StringPrinter
 *
 * DiagonalPrinter prints a string diagonally
 * l        -
 *  i       -
 *   k      -
 *    e     -
 *          -
 *      t   -
 *       h  -
 *        i -
 *         s-
 * Where the dash (-) indicates a newline character.
 * Additionally and optionally, this printer can print a special first and
 *  last line for its output. This functionality is disabled by default.
 *
 * The DiagonalPrinter is constructed with three parameters
 *  The first line - "" by default, i.e. it is not printed at all
 *  The last line  - "" by default, i.e. it is not printed at all either
 *  The output stream
 *
 * Note that the default print functionality does not suffice for this class
 *  and you will have to implement the print overload yourself.
 *
 * Implement the class accordingly.
 */

class DiagonalPrinter : public StringPrinter 
{
public:
	DiagonalPrinter(std::string first = "", std::string last = "", std::ostream& os = std::cout) 
	: StringPrinter(os), first(first), last(last) {}

	~DiagonalPrinter() {}

	DiagonalPrinter* clone() const {
		return (new DiagonalPrinter(first, last, os));		
	}

	virtual StringPrinter& operator() (const std::string& str) {
		size_t strLength = str.size();

		if (first != "") 
			os << first << std::endl;
		
		for (size_t row = 0; row < strLength ; row++) {
			for (size_t leftSpace = 0; leftSpace < row; leftSpace++) 
				os << " ";
			os << str[row];
			for (size_t rightSpace = 0; rightSpace <= (strLength - (row + 1)); rightSpace++)
				os << " ";
			os << std::endl;
		}

		if (last != "")
			os << last << std::endl;
		return (*this);
	}

private:
	std::string first;
	std::string last;
};
#endif
