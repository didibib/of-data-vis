#include "ofApp.h"

void ofApp::setup() {
	ofSetRectMode(OF_RECTMODE_CORNER);

	drawGui = true;
	gui.setup();
	gui.add(searchTag.set("#hashtags"));
	gui.add(showAreas.set("cluster", false));
	gui.add(showRoute.set("show route", false));

	route.allocate(route.getWidth(), route.getHeight(), OF_IMAGE_COLOR);
	route.load("route.png");

	buffer = ofBufferFromFile("hashtags.txt");
	for (auto line : buffer.getLines()) {
		hashtags.push_back(line);
	} //auto lines = ofSplitString(ofBufferFromFile("file.txt").getText(), "\n");

	cols = ofGetWidth() / resolution;
	rows = ofGetHeight() / resolution;

	float yoff = 10000;
	for (int y = 0; y < rows; y++) {
		float xoff = 0;
		for (int x = 0; x < cols; x++) {
			float z = ofMap(ofNoise(xoff, yoff), 0, 1, 255, 0);
			string tag = hashtags[ofRandom(hashtags.size())];
			ofColor color = ofColor(50);
			Cell cell = Cell(x, y, resolution, z, color, tag);
			grid.push_back(cell);
			xoff += 0.1;
		}
		yoff += 0.1;
	}
	zoff += 0.01;
}

void ofApp::update() {

}

void ofApp::draw() {
	if (!showRoute) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				grid[x + y*cols].draw();
			}
		}
		if (!showAreas) {
			ofFill();
			ofSetColor(ofColor::white);
			ofDrawRectangle(mouseX, mouseY + 5, underlineWidth * 5, 2);
			ofNoFill();
			ofDrawBitmapString(mouseHashText, mouseX, mouseY);
		}
	}
	else {
		ofSetColor(255);
		route.draw(0, 0);
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				int index = x + y*cols;
				if (grid[index].color == ofColor::red) {
					grid[index].draw();
				}
			}
		}
		ofFill();
		ofSetColor(ofColor::black);
		ofDrawRectangle(mouseX, mouseY + 5, underlineWidth * 5, 2);
		ofNoFill();
		ofDrawBitmapString(mouseHashText, mouseX, mouseY);
	}
	if (showAreas) {
		for (int i = 0; i < areas.size(); i++) {
			ofSetColor(ofColor::red);
			ofDrawRectangle(areas[i]);
			ofSetColor(ofColor::white);
			ofDrawBitmapString(areatag[i], areas[i].x, areas[i].y + 15);
		}
	}
	if (showRoute) {
		for (int i = 0; i < areas.size(); i++) {
			ofSetColor(ofColor::black);
			ofDrawBitmapString(mouseHashText, mouseX, mouseY);
		}
	}
	if (isDrawing) {
		ofSetColor(ofColor::green);
		ofDrawRectangle(areaPosition, areaWidth, areaHeight);
	}
	if (drawGui)
		gui.draw();
}

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'g':
		drawGui = !drawGui;
	}
}

void ofApp::mouseMoved(int x, int y) {
	if (!showAreas) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				int index = x + y*cols;
				if (grid[index].rect.inside(mouseX, mouseY)) {
					mouseHashText = grid[index].tag;
					underlineWidth = mouseHashText.length();
				}
			}
		}
	}
	else if (showRoute) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				int index = x + y*cols;
				if (grid[index].rect.inside(mouseX, mouseY)) {
					mouseHashText = grid[index].tag;
					underlineWidth = mouseHashText.length();
				}
			}
		}
	}
}

void ofApp::mouseDragged(int x, int y, int button) {
	if (isDrawing) {
		areaWidth = x - areaPosition.x;
		areaHeight = y - areaPosition.y;
		ofDrawRectangle(areaPosition, areaWidth, areaHeight);
	}

	if (button == 0) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				int index = x + y*cols;
				if (grid[index].rect.inside(mouseX, mouseY)) {
					grid[index].color = ofColor::red;
					grid[index].z = 255;
					mouseHashText = grid[index].tag;
				}
			}
		}
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (button == 2)
	{
		isDrawing = true;
		areaPosition = ofPoint(x, y);
	}
}

void ofApp::mouseReleased(int x, int y, int button) {
	isDrawing = false;
	areas.push_back(ofRectangle(areaPosition, areaWidth, areaHeight));
	areatag.push_back(hashtags[ofRandom(hashtags.size())]);
	areaWidth = areaHeight = 0;
}