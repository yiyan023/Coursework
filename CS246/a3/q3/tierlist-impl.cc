module tierlist;
import <utility>;
import <algorithm>;
import <iostream>;

void TierList::swap(TierList &other) {
  std::swap(tiers, other.tiers);
  std::swap(tierCount, other.tierCount);
  std::swap(reserved, other.reserved);
}

void TierList::enlarge() {
  reserved = 2 + 2 * std::max(reserved, tierCount);
  List **newTiers = new List *[reserved];
  std::fill_n(newTiers, reserved, nullptr);
  std::copy_n(tiers, tierCount, newTiers);
  delete[] tiers;
  tiers = newTiers;
}

TierList::TierList() : tiers{nullptr}, tierCount{0}, reserved(0) {}
TierList::~TierList() {
  if (tiers) {
    for (size_t i = 0; i < tierCount; ++i) {
      delete tiers[i];
    }
  }
  delete[] tiers;
}

void TierList::push_back_tier() {
  // Need at least 1 extra as sentinel.
  if (tierCount + 1 >= reserved) {
    enlarge();
  }
  tiers[tierCount++] = new List;
}
void TierList::pop_back_tier() {
  if (tierCount > 0) {
    delete tiers[--tierCount];
    tiers[tierCount] = nullptr;
  }
}

void TierList::push_front_at_tier(size_t tier, const std::string &entry) {
  tiers[tier]->push_front(entry);
}
void TierList::pop_front_at_tier(size_t tier) {
  tiers[tier]->pop_front();
}

size_t TierList::tierSize() const { return tierCount; }
size_t TierList::size() const {
  size_t result = 0;
  for (size_t i = 0; i < tierCount; i++) {
    result += tiers[i]->size();
  }
  return result;
}

TierList::Iterator::Iterator(List** list, size_t tier, size_t tierCount, List::Iterator list_iter): list{list}, tier{tier}, tier_count{tierCount}, list_iter{list_iter} {}

TierList::value_type TierList::Iterator::operator*() const {
	return value_type{tier, *list_iter};
}

TierList::Iterator &TierList::Iterator::operator++() {
	if (tier_count == 0) { // return the end of the tierlist if there are no tiers
		tier = 0;
		list_iter = List().end();
		return *this;
  	}

	++list_iter;
	if (list_iter != list[tier]->end()) return *this;

	++tier;
	while (tier < tier_count && (list[tier]->size() == 0)) ++tier; // ignore empty tiers
	if (tier >= tier_count) list_iter = List().end(); // reached the end of the tierlist
	else {list_iter = list[tier]->begin();}
	
	return *this;
}

TierList::Iterator TierList::Iterator::operator<<(int bk) const {
	Iterator temp = *this;

	while (bk > 0 && temp.tier > 0) {
		temp.tier--;
		if (temp.list[temp.tier]->size() != 0) bk--;
	}

	if (bk > 0) return TierList::Iterator{temp.list, temp.tier_count, temp.tier_count, List().end()};
	return TierList::Iterator(temp.list, temp.tier, temp.tier_count, temp.list[temp.tier]->begin());
}

TierList::Iterator TierList::Iterator::operator>>(int fwd) const {
	Iterator temp = *this;
	while (fwd > 0 && temp.tier < temp.tier_count-1) {
		temp.tier++; 
		if (temp.list[temp.tier]->size() != 0) fwd--;
	}
	
	if (fwd > 0) return TierList::Iterator{temp.list, temp.tier_count, temp.tier_count, List().end()};
	return TierList::Iterator(temp.list, temp.tier, temp.tier_count, temp.list[temp.tier]->begin());
}

bool TierList::Iterator::operator!=(const Iterator &other) const {
	return (list_iter != other.list_iter) || (tier != other.tier);
}

TierList::Iterator TierList::begin() const {
	size_t tier = 0;

	while (tier < tierCount && tiers[tier]->size() == 0) ++tier; // ignore empty tiers
	if (tier == tierCount) return end();
	return TierList::Iterator{tiers, tier, tierCount, tiers[0]->begin()};
}

TierList::Iterator TierList::end() const {
	return TierList::Iterator{tiers, tierCount, tierCount, List().end()};
}

