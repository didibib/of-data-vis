#include <SQLiteCpp/include/SQLiteCpp/Database.h>
#include "ofApp.h"

void ofApp::setup() {
	ofEnableDepthTest();
	string databasePath = ofToDataPath("bevolking.sqlite", true);
	db = new SQLite::Database(databasePath);
	//font.load("Roboto-Thin.ttf", 40);
	gui.setup("settings");
	gui.add(year.set("year", 2000, 1900, 2016));
	gui.add(showNumbers.set("show numbers", false));
	ofSetCircleResolution(60);
}

void ofApp::update() {
	turn = ofMap(ofGetMouseX(), 100, ofGetWidth() - 100, -10, 10, true);

	if (year != selectedYear) {
		selectedYear = year;
		string sql = "SELECT year, north, east, south, west, north+east+south+west AS total FROM bevolking WHERE year=?";

		SQLite::Statement query(*db, sql);

		query.bind(1, selectedYear); // vervang 1e vraagteken door de waarde van de variabele
		if (query.executeStep()) {
			total = query.getColumn("total").getInt();
			year = query.getColumn("year").getInt();
			north = query.getColumn("north").getInt();
			east = query.getColumn("east").getInt();
			south = query.getColumn("south").getInt();
			west = query.getColumn("west").getInt();
			//ofLog() << selectedYear << " " << total << " "
			//	<< north << " " << east << " " << south << " " << west
			//	<< endl;
		}
		query.reset();
		float fontSize = ofMap(year, 1900, 1960, 25, 40);
		font.loadFont("Roboto-Thin.ttf", fontSize);
	}
	totalSize = sqrt(total) * size;
	cout << " totalSize " << totalSize << endl;
}

void ofApp::draw() {
	ofBackgroundGradient(ofColor::aqua, ofColor::darkGrey);
	drawVisualisation();
	ofDisableDepthTest();
	gui.draw();
}

void ofApp::drawVisualisation() {
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofNoFill();
	ofSetColor(ofColor(13, 40, 84));
	ofSetLineWidth(1);

	ofRotateZ(turn + 45);
	//TOTALs
	if (showNumbers) ofDrawBitmapString(ofToString(total), -totalSize, -totalSize - 5);
	ofDrawRectangle(-totalSize / 2, -totalSize / 2, totalSize, totalSize);
	ofDrawRectangle(totalSize / 2, -totalSize / 2, totalSize, totalSize);
	ofDrawRectangle(totalSize / 2, totalSize / 2, totalSize, totalSize);
	ofDrawRectangle(-totalSize / 2, totalSize / 2, totalSize, totalSize);

	ofFill();
	//NORTH
	ofSetColor(ofColor::pink);
	float radiusNorth = sqrt(north) * size;
	ofDrawRectangle(-radiusNorth / 2, -radiusNorth / 2, radiusNorth, radiusNorth);
	ofSetColor(ofColor::black);
	if (showNumbers) ofDrawBitmapString(ofToString(north), -radiusNorth, -radiusNorth - 2);
	//EAST
	ofSetColor(ofColor::antiqueWhite);
	float radiusEast = sqrt(east) * size;
	ofDrawRectangle(radiusEast / 2, -radiusEast / 2, radiusEast, radiusEast);
	ofSetColor(ofColor::black);
	if (showNumbers) ofDrawBitmapString(ofToString(east), radiusEast + 5, -radiusEast + 2);
	//SOUTH
	ofSetColor(ofColor::pink);
	float radiusSouth = sqrt(south) * size;
	ofDrawRectangle(radiusSouth / 2, radiusSouth / 2, radiusSouth, radiusSouth);
	ofSetColor(ofColor::black);
	if (showNumbers) ofDrawBitmapString(ofToString(south), radiusSouth + 10, radiusSouth + 10);
	//WEST
	ofSetColor(ofColor::blanchedAlmond);
	float radiusWest = sqrt(west) * size;
	ofDrawRectangle(-radiusWest / 2, radiusWest / 2, radiusWest, radiusWest);
	ofSetColor(ofColor::black);
	if (showNumbers) ofDrawBitmapString(ofToString(west), -radiusWest + 10, radiusWest - 5);

	ofRotateZ(-45);
	ofSetColor(ofColor(13, 40, 84));
	float c = sqrt(pow(totalSize, 2) + pow(totalSize, 2));
	cout << " c: " << c << endl;
	font.drawStringCenteredHorizontally("N", 0, -c + 80);
	font.drawStringCenteredVertically("E", c - 80, 0);
	font.drawStringCenteredHorizontally("S", 0, c - 40);
	font.drawStringCenteredVertically("W", -c + 30, 0);

	ofPopMatrix();
}

/*
void ofApp::drawVisualisation() {
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofNoFill();
	ofSetColor(ofColor(13, 40, 84));
	ofSetLineWidth(2);

	//ofDrawCircle(0, 0, maxRadius + 5);

	ofRotateZ(turn+45);

	ofDrawRectangle(0, 0, totalSize, totalSize);
	ofFill();
	ofSetColor(ofColor::pink);
	float radiusNorth = north * 1.0f / total * size;
	ofDrawRectangle(-radiusNorth / 2, -radiusNorth / 2, radiusNorth, radiusNorth);

	ofSetColor(ofColor::antiqueWhite);
	float radiusEast = east * 1.0f / total * size;
	ofDrawRectangle(radiusEast / 2, -radiusEast / 2, radiusEast, radiusEast);

	ofSetColor(ofColor::pink);
	float radiusSouth = south * 1.0f / total * size;
	ofDrawRectangle(radiusSouth / 2, radiusSouth / 2, radiusSouth, radiusSouth);

	ofSetColor(ofColor::blanchedAlmond);
	float radiusWest = west * 1.0f / total * size;
	ofDrawRectangle(-radiusWest / 2, radiusWest / 2, radiusWest, radiusWest);

	ofRotateZ(-45);
	ofSetColor(ofColor(13, 40, 84));
	font.drawStringCenteredHorizontally("N", 0, -maxRadius - 10);
	font.drawStringCenteredVertically("E", maxRadius + 10, 0);
	font.drawStringCenteredHorizontally("S", 0, maxRadius + 50);
	font.drawStringCenteredVertically("W", -maxRadius - 60, 0);
	ofPopMatrix();
}


void ofApp::drawMaxCircle() {
	if (north > east) {
		maxVal = north;
	}
	if (east > north) {
		maxVal = east;
	}
	if (south > maxRadius) {
		maxVal = south;
	}
	if (west > maxRadius) {
		maxVal = west;
	}
	maxVal *= 1.0f / total * size;
	maxRadius = sqrt(pow(maxVal, 2) + pow(maxVal, 2));
}
*/