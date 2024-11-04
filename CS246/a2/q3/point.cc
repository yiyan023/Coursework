#include "point.h"

using namespace std;

Point::Point(int x, int y) {
  this->x = x; 
	this->y = y;
}

int Point::getX() const {
  return this->x;
}

int Point::getY() const {
  return this->y;
}

Point Point::operator+(const Point& other) {
  return Point{this->x + other.x, this->y + other.y};
}

std::ostream & operator<<( std::ostream & out, const Point & point ) {
	out << "(" << point.getX() << "," << point.getY() << ")";
	return out;
}
