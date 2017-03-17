#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "FlowField.h"
#include "Vehicle.h"

class ofApp : public ofBaseApp{

	public:
		int resolution = 20;
		float speed;
		vector<float> degree;

		ofxJSONElement json;
		int elementCount;
		FlowField flowfield;

		void getData();
		void visualize();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);           
};
