#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SQLiteCpp.h"
#include "ofxJSON.h"
#include "PieChart.h"

class ofApp : public ofBaseApp {

public:
	ofxPanel gui;
	ofParameter<int> year;
	ofParameter<bool> totpop;

	ofxGuiGroup gender;
	ofParameter<bool> man;
	ofParameter<bool> women;
	void updateGender();
	void drawGender();	

	void setup();
	void update();
	void draw();
	float pctToAngle(float pct);

private:
	ofTrueTypeFont font;
	SQLite::Database* db;
	int selectedYear;
	int totalPop;
	double pctMen;
	double pctWomen;

};
