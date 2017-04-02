#include "Vehicle.h"

Vehicle::Vehicle(){}

Vehicle::Vehicle(ofVec2f position, float maxspeed, float maxforce)
{
	this->position = position;
	radius = 6.0;
	this->maxspeed = maxspeed;
	this->maxforce = maxforce;
	acceleration = ofVec2f(0, 0);
	velocity = ofVec2f(0, 0);
}

void Vehicle::run() {
	update();
	borders();
	display();
}

void Vehicle::update() {
	velocity += acceleration;
	cout << velocity << endl;
	velocity.limit(maxspeed);
	position += velocity;
	//acceleration *= 0;
}

void Vehicle::borders() {
	if (position.x < -radius) position.x = ofGetWidth() - radius;
	if (position.y < -radius) position.y = ofGetHeight() + radius;
	if (position.x > ofGetWidth() + radius) position.x = -radius;
	if (position.y > ofGetHeight() + radius) position.y = -radius;
}

void Vehicle::display() {	
	ofFill();
	ofSetColor(ofColor::red);
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZ(velocity.angle(ofVec2f(1, 0)));

	ofPoint p1 = ofPoint(radius, 0);
	ofPoint p2 = ofPoint(-radius * 2, -radius);
	ofPoint p3 = ofPoint(-radius * 2, radius);
	ofDrawTriangle(p1, p2, p3);	

	ofPopMatrix();
	ofNoFill();
}

void Vehicle::follow(FlowField flow) {
	ofVec2f desired = flow.lookup(position);
	desired.scale(maxspeed);
	ofVec2f steer = desired - velocity;
	steer.limit(maxforce);
	applyForce(steer);
}

void Vehicle::applyForce(ofVec2f force) {
	acceleration += force;
}
