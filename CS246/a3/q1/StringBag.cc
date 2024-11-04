export module stringBag;

import <iostream>;
import <string>;
using namespace std;

export class StringBag {
		
    public:
	// ** Ctors and dtor
	// Default, copy, and move ctors
	StringBag ();
	StringBag (const StringBag& otherSB);
	StringBag (StringBag && otherSB);
	// Dtor
	~StringBag ();
	
	// ** Operator overloads
	// Take the union of two StringBags
	StringBag operator+(const StringBag& otherSB) const;
	// Take the difference of two StringBags
	StringBag operator-(const StringBag & otherSB) const;
	// Shortcut operators
	StringBag& operator+=(const StringBag& otherSB);
	StringBag& operator-=(const StringBag& otherSB);
	// Copy and move assignment operators
	StringBag& operator=(const StringBag & otherSB);
	StringBag& operator=(StringBag && otherSB);
	// Check if two StringBags have the same elements and arities
	bool operator==(const StringBag & otherSB) const;

	// ** add/remove elements
	//
	// add one instance of a string value
	void add (const string & s);
	// remove one instance of a string value
	void remove (const string & s);
	// remove all instances of a string value
	void removeAll (const string & s);

	// ** Accessor functions
	//
	// How many times does s occur in the StringBag?
	size_t arity(const string &s) const;
	// Now many elements in the StringBag, including duplicates
	size_t getNumElements() const;
	// How many values in the StringBag (ignoring duplicates)
	size_t getNumValues() const;

	// ** Housekeeping method
	// Removes all nodes with arity zero, kinda like garbage collection
	void dezombify ();

	// ** Print methods
	//
	// We will define these methods for you; note that debugPrint shows
	// zero-arity nodes (if any) but operator<< does not
	void debugPrint (ostream & out) const;
	friend ostream& operator<<(ostream &out, const StringBag & sb);

    private:
	//** Data parts
	//
	// The struct definition for the Nodes that store the individual
	// elements of s StringBag; we'll give you the complete definition
	// for this below
	struct Node;
	// Counts number of elements, including duplicates
	size_t numElements;
	// Counts number of values, ignores duplicates
	size_t numValues;
	// Pointer to the first list element
	Node* first;

	// ** Utility method; used only by other methods/ops of StringBag
	//
	// Returns a pointer to the Node containing the string if there is
	// one in the StringBag; returns nullptr otherwise.
	Node* find (const string & s) const;
};

// Node struct declaration
export
struct StringBag::Node {
    // Data parts
    const string s;
    size_t arity;
    Node* next;
    // Simple workhorse ctor
    Node (const string & s, size_t arity, Node* next);
};

ostream& operator<<(ostream &out, const StringBag &sb) {
    StringBag::Node* cur = sb.first;
    out << "{ ";
    while (nullptr != cur) {
	if (cur->arity > 0) {
	    out << "(" << cur->s << ", " << cur->arity << "), ";
	}
	cur = cur->next;
    }
    out << "}";
    return out;
}

void StringBag::debugPrint (ostream & out) const {
    out << "StringBag with " << getNumElements() << " elements and "
	<< getNumValues() << " values: " << endl;
    out << "{ " << endl;
    Node* cur = first;
    while (nullptr != cur) {
	out << "    (" << cur->s << ", " << cur->arity << "), " << endl;
	cur = cur->next;
    }
    out << "}" << endl;
}
