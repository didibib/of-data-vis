#pragma once
#include "ofMain.h"

class PieChart
{
public:
	PieChart(float x, float y, float radius, float startAngle, float endAngle, ofColor color);
	void update();
	void draw();
	ofPath path;

private:
	float x, y;
	float radius;
	float startAngle, endAngle;
	ofColor color;
};

