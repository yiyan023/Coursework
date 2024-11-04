export module list;
import <string>;

export class List {
/*
 * A a plain-old-data Node class.
 * DO NOT MODIFY THIS CLASS
 */
  struct Node {
    Node *next;
    std::string value;
    ~Node();
  };
  Node *head = nullptr;
  size_t count = 0;

  // OPTIONAL
  void swap(List &other);

 public:
  class Iterator {
    friend class List;
    Node *location;

    Iterator(Node *location);

   public:
    Iterator &operator++();

    const std::string &operator*() const;
    bool operator!=(const Iterator &other) const;
  };

 public:
  // Default constructor and destructor.
  // Should initialize new Lists to be empty in constant time.
  List();
  ~List();

  Iterator begin() const;
  Iterator end() const;

  // Inserts an element to the front of the list,
  // in constant time.
  void push_front(const std::string &value);

  // Removes an element from the front of the list,
  // if the list is non-empty.  Does nothing if the list
  // is empty.
  void pop_front();

  // Returns the size of the list, in constant time.
  size_t size() const;
};
