export module tierlist;
import list;
import <string>;

export class TierList {
  List **tiers;
  size_t tierCount;
  size_t reserved;

  void swap(TierList &other);
  void enlarge();

 public:
  // Default constructor and destructor for a TierList.
  // The default constructor should initalize an empty tier list.
  TierList();
  ~TierList();

  // Adds/removes a tier at the end of the tier list.
  // Tiers are indexed starting at 0.  Runs in time
  // at most _linear in the number of tiers_, but _not_ in the number
  // of elements.
  void push_back_tier();
  void pop_back_tier();

  // Adds/removes an element at the front of the given tier.
  // Must run in constant time.
  void push_front_at_tier(size_t tier, const std::string &entry);
  void pop_front_at_tier(size_t tier);

  // Returns the number of tiers.  Runs in constant time.
  size_t tierSize() const;
  // Returns the number of elements.  Can run in time
  // up to linear in the number of tiers.
  size_t size() const;

 public:
  struct value_type {
    size_t tier;
    std::string entry;
  };
  class Iterator {
    friend class TierList;

    // Fill in whatever private fields your Iterator class needs.
		List **list;
		size_t tier;
		size_t tier_count;
		List::Iterator list_iter;

    Iterator(List** list, size_t tier, size_t tierCount, List::Iterator list_iter);
  public:
    // Returns a value_type instance, containing
    // - a) the tier the item that the Iterator points to lives at.
    // - b) the item the Iterator points to
    value_type operator*() const;

    Iterator &operator++();

    // New Iterator operators which return a Iterator pointing to the
    // start of the tier bk elements behind/fwd elements later
    // of the tier the Iterator is currently on.
    //
    // If said tier is empty, the Iterator moves back/forward to the next
    // non-empty tier.
    Iterator operator<<(int bk) const;
    Iterator operator>>(int fwd) const;

    bool operator!=(const Iterator &other) const;
  };

  Iterator begin() const;
  Iterator end() const;
};
