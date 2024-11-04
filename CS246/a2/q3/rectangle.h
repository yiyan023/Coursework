#ifndef _RECTANGLE_H
#define _RECTANGLE_H
#include "point.h"
#include <iostream>

enum class Colour { Red, Green, Blue, Orange, Yellow, Black, White };

// A rectangle is defined by a Point that specifies its upper-left corner, a
// Colour, and its dimensions (height and width). The dimensions must be > 0.
struct Rectangle {
    // Preconditions:
    //    Coordinates of upper-left corner (x >= 0, y >= 0) and
    //    height > 0 and width > 0
    Rectangle( Point upperLeft, int height, int width, Colour colour );

    // Precondition: getPoint().getX() + x >= 0 and
    //    getPoint().getY() + y >= 0
    // Postcondition: Point = {getPoint().getX() + x, getPoint().getY() + y}
    void translate( int x = 0, int y = 0 );

    // Precondition: heightFactor > 0 and widthFactor > 0
    // Scales the Rectangle's dimensions by the specified amounts. 
    // Postcondition: new height = old height * heightFactor 
    //    and new width = old width * widthFactor 
    void scale( float heightFactor = 1.0, float widthFactor = 1.0 );

    // Changes the colour to the new colour.
    void change( Colour newColour );

    Colour getColour() const;
    Point getPoint() const;
    int getWidth() const;
    int getHeight() const;

  private: // Everything that follows cannot be directly accessed.

    Point point; // Invariant: coordinates of upper-left corner (x>=0,y>=0)
    int height, width; // Invariant: dimensions (>0)
    Colour colour; // rectangle fill-colour
};

// Reads in a Rectangle from the specified input stream. Input format consists
// of: colour x-coordinate y-coordinate height width
// where colour is a character such that 'r' => Colour::Red, 'g' => Colour::Green,
//    'b' => Colour::Blue, 'o' => Colour::Orange, 'y' = Colour::Yellow,
//    'a' => Colour::Black and 'w' => Colour::White and the other 4 values are integers.
std::istream & operator>>( std::istream & in, Rectangle & rectangle );

// Outputs a Rectangle to the specified output stream. Output format is:
// [colour (x,y) heightxwidth]
std::ostream & operator<<( std::ostream & out, const Rectangle & rectangle );

// Precondition: c is one of {'r', 'g', 'b', 'o', 'y', 'a', 'w'}
// Returns: 'r' => Colour::Red
//          'g' => Colour::Green
//          'b' => Colour::Blue
//          'o' => Colour::Orange
//          'y' => Colour::Yellow
//          'a' => Colour::Black
//          'w' => Colour::White
Colour translateColour( char c );

#endif
