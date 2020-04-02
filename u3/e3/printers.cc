#include "printers.hh"
#include <stdexcept>

using namespace std;

Printers::Printers() {}

    /* Copy construct a Printers object */
Printers::Printers(Printers const &printers) {
}

    /* Free all memory associated with the Printers object */
Printers::~Printers() {
	map<string, StringPrinter*>::iterator iter;
	for (iter = index.begin(); iter != index.end(); iter++) {
		delete (iter->second);
	}
}

    /* Adds a new StringPrinter to the Printers object
     * Creates the association of name to StringPrinter*
     * Throws:
     *  std::invalid_argument if an association for the name already exists
     *  std::invalid_argument if the pointer is null
     * Note: THe Printers object takes ownership of the pointer and is
     *  therefore responsible for eventually calling delete on the pointer
     */
void Printers::add(const std::string& str, StringPrinter* printer) {
	if (index.find(str) != index.end() || printer == NULL)
		throw invalid_argument ("Failed to add a new printer!");
	index[str] = printer;
	return;
}

    /* Retrieves a StringPrinter from the Printers object
     * The StringPrinter is obtained based on the association on the name
     * Returns:
     *  a reference to the StringPrinter object
     * Throws:
     *  std::invalid_argument if an association does not exist
     */
StringPrinter& Printers::operator[](const std::string& str) {
	if (index.find(str) == index.end())
		throw invalid_argument ("Failed to use the []-operator!");
	return (*(index[str]));
}

    /* Assign a Printers object */
Printers& Printers::operator=(const Printers& printers) {
}
