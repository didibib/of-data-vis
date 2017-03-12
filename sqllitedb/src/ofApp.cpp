#include "ofApp.h"

void ofApp::setup(){
	db = new SQLite::Database("data/huishoudens.sqlite");

	/*
	SQLite::Statement query(*db, "SELECT * FROM huish");
	while (query.executeStep()) {
		ofLog() << query.getColumn("year") << " " << query.getColumn("hh_total") << endl;
	}
	*/

	//SQLite::Statement query(*db, "SELECT * FROM huish WHERE year=?");
	//for (int year = 2012; year <= 2016; year++) {
	//	query.bind(1, year); // vervang het eerste vraagteken in mijn query met year
	//	if (query.executeStep()) {
	//		ofLog() << query.getColumn("year") << " " << query.getColumn("hh_total") << endl;
	//	}
	//	query.reset();
	//}

}

void ofApp::update(){
	year = ofMap(ofGetMouseX(), 0, ofGetWidth() - 100, 2012, 2016, true);
	if (year != selectedYear) {
		selectedYear = year;
		string statement = "SELECT hh_total,\
			(hh_single*1.0/hh_total * 100),\
			(hh_multiple*1.0/hh_total * 100)\
			FROM huish\
			WHERE year = ?"; // vermenigvuldig met 1.0 om het stiekem tot een float te maken
		SQLite::Statement query(*db, statement);
		query.bind(1, selectedYear); // vul de vraagteken in
		if (query.executeStep()) {
			pctSingle = query.getColumn(0).getDouble();
			pctMultiple = query.getColumn(1).getDouble();
			ofLog() << pctSingle << " " << pctMultiple << endl;
		}
		query.reset();
	}
}

void ofApp::draw(){
	ofBeginShape();
	ofCurveVertex(year, ofGetHeight()/2 + ofGetHeight() * sin(year * pctMultiple));
	ofEndShape();
}

