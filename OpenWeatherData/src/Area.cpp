#include "Area.h"

Area::Area()
{
}

Area::Area(int x, int y, int w, int h, string speed, string degree) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
	this->degree = degree;
	rect = ofRectangle(x, y, w, h);
}

void Area::draw() {
	ofFill();
	ofSetColor(ofColor::lightYellow);
	ofDrawRectangle(rect);
	ofNoFill();
}