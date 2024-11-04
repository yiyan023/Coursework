export module address;

import <compare>;
import <iostream>;
import <string>;

// std::size_t is an unsigned int. See https://en.cppreference.com/w/cpp/types/size_t
// for details.

export class Address {
  public:
    enum class Direction { EAST, NORTH, SOUTH, WEST, NONE };

    Address(std::size_t streetNumber, const std::string &streetName, const std::string &city,  
        const std::string &unit = "", Direction direction = Direction::NONE );

    std::strong_ordering operator<=>(const Address &other) const;

  private:
    std::size_t streetNumber;
    std::string unit, streetName, city;
    Direction direction;

    Direction convert(const std::string &direction) const;
    std::string convert(const Direction direction) const;

    // Friend declarations
    friend std::istream& operator>>(std::istream &in, Address &addr);
    friend std::ostream& operator<<(std::ostream &out, const Address &addr);
};

export std::istream& operator>>(std::istream &in, Address &addr);
export std::ostream& operator<<(std::ostream &out, const Address &addr);
