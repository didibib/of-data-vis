#include "FlowField.h"

FlowField::FlowField() {

}

FlowField::FlowField(int r, int ficou, vector<float> degs)
{
	resolution = r;
	degree = degs;
	fieldcount = ficou;
	cols = ofGetWidth() / resolution;
	fieldwidth = cols / fieldcount;
	rows = ofGetHeight() / resolution;

	//setup();
}

void FlowField::setup() {
	
}

void FlowField::display() {
	for (int i = 0; i < fieldcount; i++) {
		for (int x = 0; x < fieldwidth; x++) {
			for (int y = 0; y < rows; y++) {
				int index = x + y*cols;
				ofPushMatrix();
				ofTranslate(x * resolution, y * resolution);
				cout << degree[fieldcount] << endl;
				//ofRotate(degree[fieldcount]);
				ofSetColor(ofColor::black);
				ofDrawLine(0, 0, 0, resolution - 2);
				ofPopMatrix();
				//field[index] = ofVec2f(cos(degree[fieldcount] * DEG_TO_RAD), sin(degree[fieldcount] * DEG_TO_RAD));
			}
		}
	}
/*
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			drawVector(field[x + y * cols], x * resolution, y * resolution, resolution - 2);
		}
	}
*/
}

void FlowField::drawVector(ofVec2f v, float x, float y, float scalel) {
	ofPushMatrix();
	float arrowSize = 4;
	ofTranslate(x, y);

	//ofRotateZ(degree);

	float len = v.length() * scalel; // length() for magnitude
	ofSetColor(ofColor::black);
	ofDrawLine(0, 0, len, 0);

	ofPopMatrix();
}

ofVec2f FlowField::lookup(ofVec2f lookup) {
	int column = int(ofClamp(lookup.x / resolution, 0, cols - 1));
	int row = int(ofClamp(lookup.y / resolution, 0, rows - 1));
	return field[column + ofGetWidth() * row];
}
