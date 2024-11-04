#ifndef _POINT_H
#define _POINT_H
#include <iostream>

// A Point has an x- and a y-coordinate. 
// Class invariant: x >= 0, y >= 0

struct Point {
    // Precondition: The x- and y-coordinates of the Point must be >= 0.
    Point( int x = 0, int y = 0 );

    // Returns the x-coordinate.
    int getX() const;

    // Returns the y-coordinate.
    int getY() const;

    // Precondition: getPoint().getX() + other.getX() >= 0 and
    //               getPoint().getY() + other.getY() >= 0
    // Returns: Point{this->x + other.x, this->y + other.y}
    Point operator+( const Point & other );

  private: // Everything that follows cannot be directly accessed.
    int x, y;
};

// You may add an input operator if you wish.

// Outputs the Point to the specified output stream in the format: "(x,y)".
std::ostream & operator<<( std::ostream & out, const Point & point );

#endif
