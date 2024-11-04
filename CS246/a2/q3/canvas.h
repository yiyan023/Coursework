#ifndef _CANVAS_H
#define _CANVAS_H
#include "rectangle.h"

// The upper left-hand corner of a Canvas is at (0,0). X-coordinates increase
// towards the right (there is no negative value). Y-coordinates increase
// downwards (there is no negative value). Canvases hold Rectangles.
struct Canvas {
    // Creates an initially empty Canvas, where height == width == 0.
    Canvas();
    Canvas( const Canvas & other ); // copy constructor
    Canvas( Canvas && other ); // move constructor

    ~Canvas(); // destructor

    Canvas & operator=( const Canvas & other ); // copy assignment
    Canvas & operator=( Canvas && other ); // move assignment

    // Adds the given Rectangle after already existing rectangles.
    // Postcondition: The dimensions of the Canvas "stretch" to fit the Rectangle,
    // if necessary, depending upon where the Rectangle's upper-left-hand corner
    // is defined to be and its dimensions. 
    void add( const Rectangle & rectangle );

    // Returns the number of rectangles in the Canvas.
    int numRectangles() const; 

    // Returns the width of the Canvas.
    int getWidth() const; 

    // Returns the height of the Canvas.
    int getHeight() const; 

    // Precondition: 0 <= rectangleId < numRectangles()
    // Returns array[rectangleId].
    Rectangle get( int rectangleId ) const;

    // Precondition: 0 <= rectangleId < numRectangles() and
    //    array[rectangleId].getPoint().getX() + x >= 0 and
    //    array[rectangleId].getPoint().getY() + y >= 0
    // Postcondition: array[rectangleId].translate(x,y) and
    //    Canvas dimensions may have been altered as a result
    void translate( int rectangleId, int x = 0, int y = 0 );

    // Precondition: 0 <= rectangleId < numRectangles() and
    //     heightFactor > 0 and widthFactor > 0
    // Scales the Rectangle's dimensions by the specified amounts. 
    // Postcondition: array[rectangleId]'s new height = old height * heightFactor 
    //    and array[rectangleId]'s new width = old width * widthFactor and
    //    Canvas dimensions may have been altered as a result
    void scale( int rectangleId, float heightFactor = 1.0, float widthFactor = 1.0 );

    // Precondition: 0 <= rectangleId < numRectangles()
    // Postcondition: array[rectangleId] now has the new colour.
    void change( int rectangleId, Colour newColour );

    // Precondition: 0 <= rectangleId < numRectangles()
    // Postcondition: For all rectangles with rectangleId < idx < numRectangles,
    //    idx = idx-1 and numRectangles() = numRectangles()-1
    void remove( int rectangleId );

    // Removes all rectangles from the canvas, setting height = width = 0.
    void empty();
    
  private: // Everything that follows cannot be directly accessed.

    // ******* Add your data fields and any helper methods below this line
    Rectangle **rectangles;
    int rectangleLen, capacity;
};

// You may add an input operator if you wish.

// Outputs the Canvas. Format is:
// Dimensions: heightxwidth
// Number of rectangles: N
// \t[Rectangle_0]
// ...
// \t[Rectangle_N-1]
// where '\t' is a tab character.
std::ostream & operator<<( std::ostream & out, const Canvas & canvas );

#endif
