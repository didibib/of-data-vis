#include "ofApp.h"

void ofApp::setup() {
	colsperfield = 1;
	getData();	

	for (int i = 0; i < elementCount; i++) {
		flowfield = FlowField(colsperfield, elementCount, degree, speed);
	}
}

void ofApp::update() {

}

void ofApp::draw() {
	flowfield.display();
	for (Vehicle v : vehicles) {
		v.follow(flowfield);
		v.run();
	}
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
			//ofLog() << "wind speed #" << i << " : " << json["list"][i]["wind"]["speed"] << endl;
			//ofLog() << "wind speed #" << i << " : " << json["list"][i]["wind"]["deg"] << endl;
			speed.push_back(json["list"][i]["wind"]["speed"].asFloat());
			degree.push_back(json["list"][i]["wind"]["deg"].asFloat());
		}

	}
	else {
		ofLog() << "Oops. No data!" << endl;
		elementCount = 20;
		for (int i = 0; i < elementCount; ++i) {
			speed.push_back(ofRandom(10, 20));
			if (i % 2 == 0)
				degree.push_back(20);
			else if (i % 3 == 0)
				degree.push_back(40);
			else
				degree.push_back(50);
		}
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	float maxspeed = *std::max_element(begin(speed), end(speed));
	vehicles.push_back(Vehicle(ofVec2f(mouseX, mouseY), maxspeed, ofRandom(0.1, 0.5)));
}