import list;
import tierlist;
import <iostream>;

// output operators to test iteration.
std::ostream &operator<<(std::ostream &out, const TierList::value_type &entry) {
  return out << "[tier " << entry.tier << "]: " << entry.entry;
}

std::ostream &operator<<(std::ostream &out, const TierList &l) {
  out << l.size() << std::endl;

  for (auto s : l) {
    out << s << std::endl;
  }
  return out;
}


using namespace std;
//  test-harness operators
enum Op {NONE, CONSTRUCT, DELETE, READ, PRINT, POP_BACK_TIER, PUSH_BACK_TIER,
    PRINT_FIRST_TIER, POP_FRONT_AT_TIER};

// converts a one-character input command into its corresponding test-harness operator
Op convertOp(string opStr) {
  switch(opStr[0]) {
   case 'c': return CONSTRUCT; 
   case 'd': return DELETE;
   case 'r': return READ;
   case 'D': return POP_FRONT_AT_TIER;
   case 'p': return PRINT;
   case 'b': return POP_BACK_TIER;
   case 'B': return PUSH_BACK_TIER;
   case 'F': return PRINT_FIRST_TIER;
   default: return NONE;
  }
}

// Prints out the _first_ element in each tier.
void printFirstTier(TierList *lists[]) {
  int index;
  cin >> index;
  auto i = lists[index]->begin();
  while (i != lists[index]->end()) {
    cout << *i << endl;
    i = i >> 1;
  }
  i = i << 1;
  if (!(i != lists[index]->end())) return;
  if (!(i != lists[index]->begin())) return;
  do {
    cout << *i << endl;
    if (!(i != lists[index]->begin())) break;
    i = i << 1;
  } while (true);
}

int main () {
  TierList *lists[3] = {nullptr};

  string command, value;
  int index;
  size_t tier;
  while (cin >> command) {
    switch(Op op = convertOp(command)) {
     case CONSTRUCT: // c [0-2] : creates a new TierList in slot [0-2]
      cin >> index;
      lists[index] = new TierList;
      break;
     case DELETE: // d [0-2] : destroys the TierList in slot [0-2]
      cin >> index;
      delete lists[index];
      lists[index] = nullptr;
      break;
     case READ: // r [0-2] tier item : reads an item into the TierList in slot
                //                   [0-2] at the stated tier, with given value
      cin >> index >> tier >> value;
      lists[index]->push_front_at_tier(tier, value);
      break;
     case PRINT: // p [0-2] : prints the TierList in slot [0-2]
      cin >> index;
      cout << *(lists[index]) << endl;
      break;				
     case PUSH_BACK_TIER: // B [0-2] : adds a tier to the TierList at slot [0-2]
      cin >> index;
      lists[index]->push_back_tier();
      break;
     case POP_BACK_TIER: // b [0-2] : removes the last tier from Tierlist
      cin >> index;
      lists[index]->pop_back_tier();
      break;
     case PRINT_FIRST_TIER: // F [0-2] : prints the first item in each tier,
                            //           backwards and forwards (tests >>, <<)
      printFirstTier(lists);
      break;
     case POP_FRONT_AT_TIER: // D [0-2] tier : remove first item from given tier
      cin >> index >> tier;
      lists[index]->pop_front_at_tier(tier);
      break;
     default: 
      cerr << "Invalid command." << endl;
    }
  }
    
  for(auto p: lists) delete p;
}
