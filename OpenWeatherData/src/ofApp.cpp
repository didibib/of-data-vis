#include "ofApp.h"

void ofApp::setup() {
	getData();
	for (int i = 0; i < elementCount; i++) {
		flowfield = FlowField(resolution, elementCount, degree);
	}	
}


void ofApp::update() {

}

void ofApp::draw() {
	flowfield.display();

	//ofPushMatrix();

	//ofTranslate(500, 500);
	//ofVec2f line = ofVec2f(cos(degree * DEG_TO_RAD), sin(degree * DEG_TO_RAD));
	//ofRotateZ(degree);
	//float len = line.length() * 100; // length() = magnitude
	//ofSetColor(ofColor::black);
	//ofDrawLine(0, 0, len, 0);

	//ofPopMatrix();
}

void ofApp::keyPressed(int key) {
    getData();
}

void ofApp::getData() {
    string url = "http://api.openweathermap.org/data/2.5/forecast?q=Amsterdam,nl&appid=37f584c9d170b496e7abe382b2237a5a&units=metric";

    bool success = json.open(url);
    if (success) {
        elementCount = json["cnt"].asInt();
        ofLog() << json["cnt"].asInt() << " elementen gekregen" << endl;

        for (int i = 0; i < elementCount; ++i) {
            ofLog() << "wind speed #" << i << " : " << json["list"][i]["wind"]["speed"] << endl;
			ofLog() << "wind speed #" << i << " : " << json["list"][i]["wind"]["deg"] << endl;
			speed = json["list"][i]["wind"]["speed"].asFloat();
			degree.push_back(json["list"][i]["wind"]["deg"].asFloat());
        }

    } else {
        ofLog() << "Oops. No data!" << endl;
    }
}

void ofApp::visualize() {
	
}