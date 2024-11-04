module list;
import <utility>;

List::Node::~Node() { delete next; }

void List::swap(List &other) {
  std::swap(other.head, head);
  std::swap(other.count, count);
}

List::Iterator::Iterator(Node *location) : location{location} {}
List::Iterator &List::Iterator::operator++() {
  location = location->next;
  return *this;
}

const std::string &List::Iterator::operator*() const { return location->value; }

bool List::Iterator::operator!=(const List::Iterator &other) const {
  return location != other.location;
}

List::List() : head{nullptr}, count{0} {}
List::~List() { delete head; }

List::Iterator List::begin() const { return Iterator(head); }
List::Iterator List::end() const { return Iterator(nullptr); }

void List::push_front(const std::string &value) {
  head = new Node{head, value};
  ++count;
}

void List::pop_front() {
  if (head) {
    --count;
    Node *tmp = head;
    head = head->next;
    tmp->next = nullptr;
    delete tmp;
  }
}

size_t List::size() const { return count; }
