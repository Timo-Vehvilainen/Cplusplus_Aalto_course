#ifndef AALTO_CPP_INTERFACE_HH
#define AALTO_CPP_INTERFACE_HH

#include <vector>
#include <algorithm>

#include "exception.hh"

class Card;

// Utility template
template <typename T>
T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss(str);
    iss >> var;
    return var;
}

namespace Interface
{
  // Class for selecting cards - contains a mutable member
  class CardSelection
  {
  private:

    struct Option
    {
      Option(const Card* card, size_t idx) : card(card), idx(idx), selected(false) {}

      const Card* card;
      size_t idx;
      mutable bool selected;
    };

  public:

    const enum SelectionOrigin
    {
      ORIGIN_HAND,
      ORIGIN_STORAGE,
      ORIGIN_OTHER
    } origin;

    CardSelection(enum SelectionOrigin origin = ORIGIN_HAND) : origin(origin) {}

    /* DESCRIPTION:
     * ------------
     * Adds a new option to the back of the options vector (see: class' private
     * members, and the struct Option above).
     *
     * PARAMETERS:
     * ------------
     * const Card* card: the card used to initialize the new Option object.
     * size_t idx: the idx used to initialize the new Option object.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    void addOption(const Card* card, size_t idx)
    {
      options.push_back(Option(card, idx));
    }

    std::vector<Option>::const_reverse_iterator rbegin() const { return options.rbegin(); }
    std::vector<Option>::const_reverse_iterator rend() const { return options.rend(); }
    std::vector<Option>::const_iterator begin() const { return options.begin(); }
    std::vector<Option>::const_iterator end() const { return options.end(); }

    /* DESCRIPTION:
     * ------------
     * The function returns the Card pointer from the first Option object which
     * is selected (hint: find_if).
     *
     * If there are no Option objects which status is selected, the function
     * should throw a LogicError (see: exception.hh).
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * The Card pointer of first Option object which status is selected.
     */
    const Card* getSelectedCard() const
    {
      auto ret = find_if(begin(), end(), selected);
      if(ret == end())
      	throw Exception::LogicError ("No card was selected");
      return (ret->card);
    }

    /* DESCRIPTION:
     * ------------
     * The function returns the idx from the first Option object which is
     * selected (hint: find_if).
     *
     * If there are no Option objects which status is selected, the function
     * should throw a LogicError (see: exception.hh).
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * The idx of the first Option object which status is selected.
     */
    size_t getSelectedIdx() const
    {
      auto ret = find_if(begin(), end(), selected);
      if(ret == end())
      	throw Exception::LogicError ("No index was selected");
      return (ret->idx);
    }

    /* DESCRIPTION:
     * ------------
     * The function counts the number of Option objects which have the status
     * selected as true.
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * Number of Option objects with the status selected set as true.
     */
    size_t countSelected() const
    {
      size_t counter = 0;
      for (auto it = begin(); it != end(); it++) {
      	if (it->selected)
      		counter++;
      }    
      return counter;
    }

    /* DESCRIPTION:
     * ------------
     * The function toggles the selection status of the Option object in the 
     * parameter idx.
     *
     * In practice this just swaps the selection status of the Option object
     * in the idx to the opposite.
     *
     * If the parameter idx is out of bounds i.e. >= the options vector's size,
     * the function throw a LogicError (see: exception.hh).
     *
     * PARAMETERS:
     * ------------
     * size_t idx: the index of the Option object, which selected status to toggle.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    void toggle(size_t idx) const
    {
    	if (idx >= size()) {
    		throw Exception::LogicError("Index out of bounds");
    	}
      	if (options[idx].selected)
      		(options[idx]).selected = false;
      	else
      		(options[idx]).selected = true;
    }
    /* DESCRIPTION:
     * ------------
     * The function sets the selected status of all the Option objects as false.
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    void clearSelections() const
    {
      for (auto it = begin(); it != end(); it++)  
      	it->selected = false;
    }

    /* DESCRIPTION:
     * ------------
     * The function sets the selected status of all the Option objects as true.
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * Nothing.
     */
    void selectAll() const
    {
      for (auto it = begin(); it != end(); it++)  
      	it->selected = true;
    }

    /* DESCRIPTION:
     * ------------
     * Returns a boolean value indicating whether the options vector is empty.
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * True if the options vector is empty, otherwise false.
     */
    bool empty() const
    {
      return (size() == 0);
    }

    /* DESCRIPTION:
     * ------------
     * Checks whether the options vector is in ascending order according to
     * the Option objects' indices (idx).
     *
     * Hint: is_sorted, and cmpIdx (private function) might help.
     *
     * PARAMETERS:
     * ------------
     * None.
     *
     * RETURNS:
     * ------------
     * True if the vector is in order, false otherwise.
     */
    bool validate() const
    {
    	size_t previous = 0;
      for (auto it = begin(); it != end(); it++) {
      	if (it->idx < previous)
      		return false;
      	previous = it->idx;
      }
      return true; 
    }

    size_t size(void) const { return options.size(); }    
  private:
    static bool selected(const Option& opt) { return opt.selected; }
    static bool cmpIdx(const Option& left, const Option& right) { return left.idx < right.idx; }
    std::vector<Option> options;    
  };

  // Phase in TurnContext
  enum TurnPhase {
    // Out of turn
    PHASE_PRE_TURN,
    // Action phase
    PHASE_ACTION,
    // Buy Phase
    PHASE_COIN,
    PHASE_BUY,
    // Clean-up
    PHASE_END
  };

  // Decisions that certain cards require players to take
  enum Decision
  {
    DECIDE_HAND_OR_DISCARD, // Library card
    DECIDE_DISCARD_DECK, // Chancellor card
    DECIDE_TOP_OF_DECK_OR_DISCARD, // Spy card
    DECIDE_REACT // Play Moat card?
  };
}

#endif
