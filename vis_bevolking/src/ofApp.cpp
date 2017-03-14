#include "ofApp.h"

void ofApp::setup(){
	db = new SQLite::Database("data/bevolking.sqlite");
	font.load("Roboto-Light.ttf", 64);

	gui.setup("bevolking");
	gui.add(year.set("year", 2000, 1900, 2016));
	gui.add(totpop.set("total population", true));
	gender.setup("gender");
	gender.add(man.set("man", false));
	gender.add(women.set("women", false));
	gui.add(&gender);
}

void ofApp::update(){	
	updateGender();
}

void ofApp::draw(){
	ofDrawCi
	gui.draw();
}

void ofApp::updateGender() {
	if (selectedYear != year) {
		selectedYear = year;
		string statement = "SELECT total,\
		(men * 1.0 / total * 100) AS pctmen,\
		(women * 1.0 / total * 100) AS pctwomen\
		FROM bevolking\
		WHERE year = ?";
		SQLite::Statement query(*db, statement);
		query.bind(1, selectedYear);
		if (query.executeStep()) {
			totalPop = query.getColumn("total").getDouble();
			pctMen = query.getColumn("pctmen").getDouble();
			pctWomen = query.getColumn("pctwomen").getDouble();
		}
		query.reset();
	}
}

void ofApp::drawGender() {
	if (man || women) {
		ofSetColor(ofColor::forestGreen);
		ofNoFill();
		ofDrawBox(ofPoint(ofGetWidth() / 2, ofGetHeight() - 50), 200, 100, 0);
		ofFill();
		if (man) {
			ofSetColor(ofColor::cornflowerBlue);
			ofDrawBox(ofPoint(ofGetWidth() / 2 - 50, ofGetHeight() - 50), 100, pctMen, 0);
		}
		if (women) {
			ofSetColor(ofColor::orangeRed);
			ofDrawBox(ofPoint(ofGetWidth() / 2 + 50, ofGetHeight() - 50), 100, pctWomen, 0);
		}
	}
}

float ofApp::pctToAngle(float pct) {
	float angle = 360 * pct / 100;
	return angle;
}