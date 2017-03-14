#include "PieChart.h"

PieChart::PieChart(float x, float y, float radius, float startAngle, float endAngle, ofColor color){
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->startAngle = startAngle;
	this->endAngle = endAngle;
	this->color = color;
	path.setCircleResolution(60);
}

void PieChart::update() {
	path.moveTo(x + radius, y);
	path.arc(x, y, radius, radius, startAngle, endAngle);
	path.setFilled(true);
	path.setStrokeWidth(1);
}

void PieChart::draw() {
	ofSetColor(color);
	path.draw();
	ofNoFill();
}
