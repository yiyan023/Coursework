#include "canvas.h"
#include <iostream>
using namespace std;

Canvas::Canvas() {
	this->rectangleLen = 0; // number of rectangles
	this->capacity = 0; // length of rectangles array
	this->rectangles = new Rectangle*[capacity];
}

Canvas::Canvas( const Canvas & other ) {
	this->rectangleLen = other.rectangleLen;
	this->capacity = other.capacity;
	this->rectangles = new Rectangle*[other.capacity];

	for (int i = 0; i < other.rectangleLen; i++) {
		this->rectangles[i] = new Rectangle{*other.rectangles[i]};
	}
}

Canvas::Canvas( Canvas && other ) {
	this->rectangleLen = other.rectangleLen;
	this->capacity = other.capacity;
	this->rectangles = other.rectangles;

	other.rectangles = nullptr;
	other.rectangleLen = 0;
	other.capacity = 0;
}

Canvas::~Canvas() {
	for (int i = 0; i < rectangleLen; i++) {
		delete rectangles[i];
	}

	delete[] rectangles;
}

Canvas&Canvas::operator=( const Canvas & other ) {
	if (this == &other) return *this;

	for (int i = 0; i < rectangleLen; i++) {
		delete rectangles[i];
	}

	delete[] rectangles;

	rectangles = new Rectangle*[other.capacity];

	for (int i = 0; i < other.rectangleLen; i++) {
		rectangles[i] = new Rectangle{*other.rectangles[i]};
	}

	rectangleLen = other.rectangleLen;
	capacity = other.capacity;

	return *this;
}

Canvas &Canvas::operator=(Canvas && other) {
	if (this == &other) return *this;

	for (int i = 0; i < rectangleLen; i++) {
		delete rectangles[i];
	}

	delete[] rectangles;

	this->rectangleLen = other.rectangleLen;
	this->capacity = other.capacity;
	this->rectangles = other.rectangles;

	other.rectangles = nullptr;
	other.rectangleLen = 0;
	other.capacity = 0; 

	return *this;
}

void Canvas::add( const Rectangle & rectangle ) {
	if (rectangleLen >= capacity) { // update array length in heap
		if (capacity == 0) {
			capacity = 4;
		} else {
			capacity *= 2;
		}

		Rectangle** new_rect = new Rectangle*[capacity];

		for (int i = 0; i < rectangleLen; i++) {
			new_rect[i] = new Rectangle{*rectangles[i]};
		}

		for (int i = 0; i < rectangleLen; i++) {
			delete rectangles[i];
		}

		delete[] rectangles;
		rectangles = new_rect;		
	}

	rectangles[rectangleLen] = new Rectangle{rectangle};
	rectangleLen++;
}

int Canvas::numRectangles() const {
	return rectangleLen;
}

int Canvas::getWidth() const {
	int width = 0;
  
	for (int i = 0; i < rectangleLen; i++) { // find rectangle with right-most vertex
		width = max(width, rectangles[i]->getPoint().getX() + rectangles[i]->getWidth());
	} 
  
	return width;
}

int Canvas::getHeight() const {
	int height = 0;
  
	for (int i = 0; i < rectangleLen; i++) { // find rectangle with bottom-most vertex
		height = max(height, rectangles[i]->getPoint().getY() + rectangles[i]->getHeight());
	} 
  
	return height;
}

Rectangle Canvas::get( int rectangleId ) const {
	return *rectangles[rectangleId];
}

void Canvas::translate( int rectangleId, int x, int y) {
	rectangles[rectangleId]->translate(x, y);
}

void Canvas::scale( int rectangleId, float heightFactor, float widthFactor) {
	rectangles[rectangleId]->scale(heightFactor, widthFactor);
}

void Canvas::change( int rectangleId, Colour newColour ) {
	rectangles[rectangleId]->change(newColour);
}

void Canvas::remove( int rectangleId ) {
	delete rectangles[rectangleId];

	for(int i = rectangleId; i < rectangleLen-1; i++) { // shift elements up in the array after deleting
		rectangles[i] = rectangles[i+1];
	}
	
	rectangleLen--;
}

void Canvas::empty() {
	rectangleLen = 0;
	capacity = 4;

	for (int i = 0; i < rectangleLen; i++) {
		delete rectangles[i];
	}

	delete[] rectangles;

	rectangles = new Rectangle*[capacity];
}

std::ostream & operator<<( std::ostream & out, const Canvas & canvas ) {
	out << "Dimensions: " << canvas.getHeight() << "x" << canvas.getWidth() << endl;
	out << "Number of rectangles: " << canvas.numRectangles() << endl;

	for (int i = 0; i < canvas.numRectangles(); i++) {
		out << "\t" << canvas.get(i) <<endl;
	}	

	return out;
}
