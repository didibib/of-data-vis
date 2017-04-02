#include "FlowField.h"

FlowField::FlowField() {

}

FlowField::FlowField(int colsperfield, int fieldcount, vector<float> degree, vector<float> speed)
{
	this->resolution = ofGetWidth() / fieldcount / colsperfield;
	this->colsperfield = colsperfield;
	this->fieldcount = fieldcount; // elements from data
	this->degree = degree;
	this->speed = speed;

	maxspeed = *max_element(begin(speed), end(speed));
	cols = ofGetWidth() / resolution;
	rows = ofGetHeight() / resolution;
	fieldwidth = cols / fieldcount;
	elementsperfield = fieldwidth * rows;

	lowcolor = ofColor::fromHex(0x8EA1F0); 
	highcolor = ofColor::fromHex(0xF5FAC8);

	setup();
}

void FlowField::setup() {	
	for (int i = 0; i < fieldcount; i++) {
		for (int x = 0; x < fieldwidth; x++) {
			for (int y = 0; y < rows; y++) {
				ofVec2f line = ofVec2f(cos(degree[i] * DEG_TO_RAD), sin(degree[i] * DEG_TO_RAD));
				field.push_back(line);
			}
		}
		Area area = Area(i * fieldwidth * resolution, 0, fieldwidth * resolution, ofGetHeight(), ofToString(speed[i]), ofToString(degree[i]));
		areas.push_back(area);
	}
}

void FlowField::display() {	
	fieldata();
	for (int i = 0; i < fieldcount; i++) {
		for (int x = 0; x < fieldwidth; x++) {
			for (int y = 0; y < rows; y++) {				
				drawVector(field[y + x * rows + i * elementsperfield], x * resolution + i * resolution * colsperfield, y * resolution, speed[i]);
			}
		}
	}
	stringstream info;
	info << "speed: " << strspeed << endl;
	info << "degree: " << strdegree << endl;
	ofDrawBitmapStringHighlight(info.str(), ofGetMouseX(), ofGetMouseY() - 30);
}

void FlowField::fieldata() {
	for (int i = 0; i < fieldcount; i++) {
		if (areas[i].rect.inside(ofGetMouseX(), ofGetMouseY())) {
			areas[i].draw();
			strdegree = areas[i].degree;
			strspeed = areas[i].speed;
		}
	}
}

void FlowField::drawVector(ofVec2f v, float x, float y, float scale) {
	float vectorscale = scale * resolution / maxspeed;

	ofPushMatrix();
	float len = v.length() * scale; // length() = magnitude
	ofTranslate(x + resolution / 2, y + resolution / 2);
	ofRotateZ(v.angle(ofVec2f(1, 0)));

	ofFill();
	float mspeed = ofMap(scale, 0, maxspeed, 0, 1);
	//cout << "mspeed " << scale << endl;
	ofColor color = lowcolor.lerp(highcolor, mspeed);
	ofSetColor(lowcolor.lerp(highcolor, mspeed));
	ofDrawLine(-len / 2, 0, len / 2, 0);
	float radius = vectorscale;
	ofPoint p1 = ofPoint(radius/2, 0);
	ofPoint p2 = ofPoint(-radius/2, -radius/3);
	ofPoint p3 = ofPoint(-radius/2, radius/3);
	ofDrawTriangle(p1, p2, p3);
	ofNoFill();

	ofPopMatrix();
}

ofVec2f FlowField::lookup(ofVec2f lookup) {
	int column = int(ofClamp(lookup.x / resolution, 0, cols - 1));
	int row = int(ofClamp(lookup.y / resolution, 0, rows - 1));
	return field[row + column * rows];
}