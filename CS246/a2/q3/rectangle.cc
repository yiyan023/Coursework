#include "rectangle.h"

using namespace std;

Colour translateColour( char c ) { // change character input to Colour struct
    switch( c ) {
        case 'r' : return Colour::Red;
        case 'g' : return Colour::Green;
        case 'b' : return Colour::Blue;
        case 'y' : return Colour::Yellow;
        case 'o' : return Colour::Orange;
        case 'a' : return Colour::Black;
        case 'w' : return Colour::White;
    }
    return Colour::Red;
}

string translateColour( Colour colour ) { // change Colour struct to string name
	switch( colour ) {
			case Colour::Red:    return "Red";
			case Colour::Green:  return "Green";
			case Colour::Blue:   return "Blue";
			case Colour::Yellow: return "Yellow";
			case Colour::Orange: return "Orange";
			case Colour::Black:  return "Black";
			case Colour::White:  return "White";
	}
	return "Red";
}

Rectangle::Rectangle( Point upperLeft, int height, int width, Colour colour ) {
	this->point = upperLeft; 
	this->height = height; 
	this->width = width; 
	this->colour = colour;
}

void Rectangle::translate( int x, int y) {
	this->point = point + Point{x, y};
}

void Rectangle::scale( float heightFactor, float widthFactor) {
	this->width *= widthFactor; 
	this->height *= heightFactor;
}

void Rectangle::change( Colour newColour ) {
  this->colour = newColour;
}

Colour Rectangle::getColour() const {
  return this->colour;
}

Point Rectangle::getPoint() const {
  return this->point;
}

int Rectangle::getWidth() const {
  return this->width;
}

int Rectangle::getHeight() const {
  return this->height;
}

std::istream & operator>>( std::istream & in, Rectangle & rectangle ) {
    char c; 
		int x, y, h, w;
    in >> c >> x >> y >> h >> w;
    rectangle = Rectangle(Point{x, y}, h, w, translateColour(c));
    return in;
}

std::ostream & operator<<( std::ostream & out, const Rectangle & rectangle ) {
    out << "[" << translateColour(rectangle.getColour()) << " " << rectangle.getPoint() << " " << rectangle.getHeight() << "x" << rectangle.getWidth() << "]";
    return out;
}
