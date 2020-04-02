#ifndef PRINTER_HH
#define PRINTER_HH

#include <iostream>
#include <string>

/* Implement the abstract base class StringPrinter here
 *
 * The base class contains a constructor that takes one parameter:
 *   std::ostream& with the default value std::cout
 * The base class contains the following pure virtual member functions
 *  A clone() function that copies the object and returns StringPrinter*
 *  Function call operator overload, i.e. this base class is a function object
 *   that takes one one std::string argument.
 *   Returns a reference to the StringPrinter object meaning that this
 *   function call operation can be "chained", e.g.
 *   object("First")("Second")("Third");
 *
 * The base class contains the following protected member:
 *  An std::ostream reference which is the output stream
 *
 * Implement the class accordingly and do not forget the virtual destructor..
 */

class StringPrinter 
{
public:
	StringPrinter(std::ostream &out = std::cout) : os(out) {}

	virtual StringPrinter* clone() const = 0;

	virtual StringPrinter& operator() (const std::string& str) = 0;

	//~StringPrinter() {}
protected:
	std::ostream &os;
	StringPrinter(const StringPrinter&);
	StringPrinter& operator= (const StringPrinter&);
};

#endif
