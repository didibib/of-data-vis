#pragma once

#include "ofMain.h"

class FlowField
{
public:
	FlowField();   
	FlowField(int r, int ficou, vector<float> degs);

	vector<ofVec2f> field;
	vector<float> degree;
	int fieldcount;
	int fieldwidth;
	int cols, rows;
	int resolution;	

	void setup();
	void display();
	void drawVector(ofVec2f v, float x, float y, float scalel);
	ofVec2f lookup(ofVec2f lookup);		
};

