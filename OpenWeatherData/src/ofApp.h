#pragma once
#include <algorithm>

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxGui.h"

#include "FlowField.h"
#include "Vehicle.h"

class ofApp : public ofBaseApp {

	public:
		int resolution;
		int colsperfield;
		vector<float> speed;
		vector<float> degree;

		ofxJSONElement json;
		int elementCount;
		FlowField flowfield;
		vector<Vehicle> vehicles;

		void getData();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);      
		void mousePressed(int x, int y, int button);
};
