#pragma once

#include "ofMain.h"

class Cell
{
public:
	Cell();
	Cell(int x, int y, int w, float z, ofColor color, string tag);

	int x, y, w;
	float z;
	ofColor color;
	string tag;

	ofRectangle rect;

	void draw();
};

