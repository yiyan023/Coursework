module address;
using namespace std;

Address::Address(std::size_t streetNumber, const std::string &streetName, const std::string &city,  
        const std::string &unit, Direction direction ) 
    : streetNumber{streetNumber}, unit{unit}, streetName{streetName}, city{city}, direction{direction} {}

// Note that we check the street name for equality before the direction.
// Because of the enumerated class ordering, EAST < NORTH < SOUTH < WEST < NONE.
// Due to string comparison, "" < any string containing something.
std::strong_ordering Address::operator<=>(const Address &other) const {
	auto res_city = city <=> other.city;
	if (res_city != 0) return res_city;

	auto res_str = streetName <=> other.streetName;
	if (res_str != 0) return res_str;

	auto res_dir = direction <=> other.direction;
	if (res_dir != 0) return res_dir;

	auto res_num = streetNumber <=> other.streetNumber;
	if (res_num != 0) return res_num;

    return unit <=> other.unit;
} // Address::operator<=>

Address::Direction Address::convert(const std::string &direction) const {
    if ( direction == "East" ) return Address::Direction::EAST;
    if ( direction == "West" ) return Address::Direction::WEST;
    if ( direction == "North" ) return Address::Direction::NORTH;
    if ( direction == "South" ) return Address::Direction::SOUTH;
    return Address::Direction::NONE;
} // Address::convert

std::string Address::convert(const Address::Direction direction) const {
    if ( direction == Address::Direction::EAST ) return "East";
    if ( direction == Address::Direction::WEST ) return "West";
    if ( direction == Address::Direction::NORTH ) return "North";
    if ( direction == Address::Direction::SOUTH ) return "South";
    return "";
}

// A valid address consists of MAX_NUM_ADDR_ELEMS comma-separated values on a single line.
std::istream& operator>>(std::istream &in, Address &addr) {
    static const size_t MAX_NUM_ADDR_ELEMS = 5;
    string words[MAX_NUM_ADDR_ELEMS], line;
    size_t pos = 0, prevPos = 0;
    getline(in, line);
    if ( !in.good() ) return in;
    for (size_t i = 0; i < MAX_NUM_ADDR_ELEMS; ++i) {
        pos = line.find(",", prevPos);
        words[i] = line.substr(prevPos, pos-prevPos);
        prevPos = pos+1;
    } // for
    addr.unit = words[0];
    addr.streetNumber = stoul(words[1]);
    addr.streetName = words[2];
    addr.direction = addr.convert(words[3]);
    addr.city = words[4];
    return in;
} // operator>>

std::ostream& operator<<(std::ostream &out, const Address &addr) {
    out << addr.unit << "," << addr.streetNumber << "," << addr.streetName << ","
        << addr.convert(addr.direction) << "," << addr.city;
    return out;
} // operator<<

