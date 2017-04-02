#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(int x, int y, int w, float z, ofColor color, string tag) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->z = z;
	this->color = color;
	this->tag = tag;
	rect = ofRectangle(x * w, y * w, w, w);
}

void Cell::draw() {
	ofFill();
	ofSetColor(color.r, color.g, color.b, z);	
	ofDrawRectangle(rect);
	ofNoFill();
}