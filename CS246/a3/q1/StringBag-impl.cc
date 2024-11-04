module stringBag;
import <iostream>;
import <string>;
import <utility>;
using namespace std;

// Node workhorse ctor
StringBag::Node::Node (const string & s, size_t arity, Node* next): s{s}, arity{arity}, next{next} {}

// StringBag default ctor
StringBag::StringBag(): numElements{0}, numValues{0}, first{nullptr} {}

// StringBag copy ctor
StringBag::StringBag(const StringBag & otherSB): numElements{otherSB.numElements}, numValues{otherSB.numValues}, first{nullptr} {
    if (otherSB.first) {
        first = new Node(otherSB.first->s, otherSB.first->arity, nullptr);
        Node* cur = first;
        Node* temp = otherSB.first->next;

        while (temp) {
            cur->next = new Node(temp->s, temp->arity, nullptr);
            cur = cur->next;
            temp = temp->next;
        }
    }
}

// StringBag move ctor
StringBag::StringBag (StringBag && otherSB): numElements{otherSB.numElements}, numValues{otherSB.numValues}, first{otherSB.first} {
	otherSB.first = nullptr;
}

// StringBag dtor
StringBag::~StringBag() {
	while( first != nullptr) {
        Node* node = first->next;
        delete first;
        first = node;
    }
}

// StringBag copy operator=
StringBag& StringBag::operator=(const StringBag & otherSB) {
	if (this == &otherSB) return *this;

    numElements = otherSB.numElements; 
	numValues = otherSB.numValues;

    while( first != nullptr) {
        Node* node = first->next;
        delete first;
        first = node;
    }
    
    if (otherSB.first) {
        first = new Node(otherSB.first->s, otherSB.first->arity, nullptr);
        Node* cur = first;
        Node* temp = otherSB.first->next;

        while (temp) {
            cur->next = new Node(temp->s, temp->arity, nullptr);
            cur = cur->next;
            temp = temp->next;
        }
    }

    return *this;
}

// StringBag move operator=
StringBag& StringBag::operator=(StringBag && otherSB) {
	if (this == &otherSB) return *this;

	while( first != nullptr) {
        Node* node = first->next;
        delete first;
        first = node;
    }

	first = otherSB.first;
	numElements = otherSB.numElements;
	numValues = otherSB.numValues;
	otherSB.first = nullptr;

	return *this;
}

void StringBag::add(const string & s) {
    numElements++;
    Node* temp = find(s);
    if (temp != nullptr) temp->arity++;
    else {
		first = new Node(s, 1, first);
    	numValues++;
	}
}

void StringBag::remove(const string & s) {
	Node* temp = this->find(s);

	if (temp != nullptr) {
		if (temp->arity > 0) {
			temp->arity--;
			numElements--;
			if (temp->arity == 0 && numValues > 0) numValues--;
		}
	}
}

void StringBag::removeAll(const string & s) {
	Node* temp = this->find(s);

	if (temp != nullptr) {
		numElements -= temp->arity;
		if (numValues > 0) numValues--;
		temp->arity = 0;
	}
}

StringBag StringBag::operator+(const StringBag & otherSB) const {	
	StringBag s = StringBag(otherSB);
	s += *this;
    return s;
}

StringBag StringBag::operator-(const StringBag & otherSB) const {
	StringBag s = StringBag(*this);
    s -= otherSB;
	return s;
}

StringBag& StringBag::operator+=(const StringBag& otherSB) {
	Node *temp = otherSB.first;
	while (temp != nullptr) {
		for (size_t i = 0; i < temp->arity; i++) add(temp->s);
		if (temp->arity == 0 && this->find(temp->s) == nullptr) {
			Node* new_node = new Node(temp->s, 0, first);
			first = new_node;
		}
		temp = temp->next;
	}
	return *this;
}

StringBag& StringBag::operator-=(const StringBag& otherSB) {
    Node *temp = otherSB.first;
	while (temp != nullptr) {
		for (size_t i = 0; i < temp->arity; i++) remove(temp->s);
		temp = temp->next;
	}
	return *this;
}

bool StringBag::operator==(const StringBag & otherSB) const {
	StringBag res_1{*this - otherSB};
	StringBag res_2{otherSB - *this};
	return res_1.numElements == 0 && res_2.numElements == 0;
}

// go thru and delete Nodes with arity==0
void StringBag::dezombify() {
	Node* cur = this->first;
	Node* prev = nullptr;

	while (cur != nullptr) {
		if (cur->arity == 0) {
			Node* temp = cur->next; 

			if (prev == nullptr) this->first = temp;
			else {prev->next = temp;}

			delete cur;
			cur = temp;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}
}

// Returns a pointer to the Node for value s if it exists, even if it has 
// arity zero
StringBag::Node* StringBag::find (const string & s) const {
	Node* cur = this->first;
	while (cur != nullptr) {
		if (cur->s == s) return cur;
		cur = cur->next;
	}
	return nullptr;
}

size_t StringBag::getNumElements () const {return numElements;}

size_t StringBag::getNumValues () const {return numValues;}

size_t StringBag::arity(const string & s) const {
	Node *cur = this->find(s);
	if (cur != nullptr) return cur->arity;
	else {return 0;}
}
