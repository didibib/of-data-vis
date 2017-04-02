#pragma once
#include <algorithm>
using namespace std;

#include "ofMain.h"
#include "Area.h"

class FlowField
{
public:
	FlowField();   
	FlowField(int colsperfield, int fieldcount, vector<float> degs, vector<float> speed);

	vector<ofVec2f> field;
	vector<float> degree;
	vector<float> speed;
	float maxspeed;
	int colsperfield;
	int elementsperfield;
	int fieldcount;
	int fieldwidth;
	int cols, rows;
	int resolution;	

	vector<Area> areas;
	string strdegree, strspeed;
	ofColor lowcolor;
	ofColor highcolor;

	void setup();
	void display();
	void fieldata();
	void drawVector(ofVec2f v, float x, float y, float scalel);
	ofVec2f lookup(ofVec2f lookup);	
};

