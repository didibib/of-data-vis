#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"
#include "ofxGui.h"
#include "ofxCenteredTrueTypeFont.h"

class ofApp : public ofBaseApp {

    public:
		ofxPanel gui;
		ofParameter<int> year;
		ofParameter<bool> showNumbers;

		void drawVisualisation();
		//void drawMaxCircle();

        void setup();
        void update();
        void draw();

    private:
        SQLite::Database* db;
        int selectedYear = 1900;
		ofxCenteredTrueTypeFont font;

        int total;
        int north;
        int east;
        int south;
        int west;

		int size = 2;
		int turn;
		int maxVal;
		int totalSize;
};