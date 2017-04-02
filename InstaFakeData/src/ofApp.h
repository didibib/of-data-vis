#pragma once

#include "ofMain.h"
#include <algorithm>

#include "ofxGui.h"
#include "Cell.h"

class ofApp : public ofBaseApp {

	public:
		bool drawGui;
		ofxPanel gui;
		ofParameter<string> searchTag;
		ofParameter<bool> showAreas;
		ofParameter<bool> showRoute;

		ofImage route;

		int resolution = 20;
		int cols, rows;
		vector<Cell> grid;		
		float zoff;

		vector<string> hashtags;
		ofBuffer buffer;
		string mouseHashText;
		int underlineWidth;
		bool ownTags;

		vector<ofRectangle> areas;
		vector<string> areatag;
		bool isDrawing;
		ofPoint areaPosition;
		float areaWidth, areaHeight;
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);		
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
};