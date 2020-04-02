#ifndef TKK_AS_CPP_PRINTERS_HH
#define TKK_AS_CPP_PRINTERS_HH

#include <string>
#include <map>

#include "printer.hh"

/* Class Printers
 * A storage for StringPrinters pointers - has ownership of the objects
 * Maintains an association of name to StringPrinter pointer
 * Note:
 *  Some functions can throw exceptions - this is specified for each function
 */
class Printers
{
public:
    /* Construct an empty Printers object */
    Printers();

    /* Copy construct a Printers object */
    Printers(const Printers&);

    /* Free all memory associated with the Printers object */
    ~Printers();

    /* Adds a new StringPrinter to the Printers object
     * Creates the association of name to StringPrinter*
     * Throws:
     *  std::invalid_argument if an association for the name already exists
     *  std::invalid_argument if the pointer is null
     * Note: THe Printers object takes ownership of the pointer and is
     *  therefore responsible for eventually calling delete on the pointer
     */
    void add(const std::string&, StringPrinter*);

    /* Retrieves a StringPrinter from the Printers object
     * The StringPrinter is obtained based on the association on the name
     * Returns:
     *  a reference to the StringPrinter object
     * Throws:
     *  std::invalid_argument if an association does not exist
     */
    StringPrinter& operator[](const std::string&);

    /* Assign a Printers object */
    Printers& operator=(const Printers&);

private:
    /* Internal representation of Printers
     * Associates std::string to StringPrinter*
     * Note: Due to the pointer content, this does not copy nicely
     */
    std::map<std::string, StringPrinter*> index;
};

#endif

