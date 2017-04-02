#pragma once

#include "ofMain.h"

class Area
{
public:
	Area();
	Area(int x, int y, int w, int h, string speed, string degree);
	int x, y;
	int w, h;
	string speed, degree;

	ofRectangle rect;

	void draw();
};

