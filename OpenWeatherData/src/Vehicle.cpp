#include "Vehicle.h"

Vehicle::Vehicle(){}

Vehicle::Vehicle(ofVec2f l, float ms, float mf)
{
	position = l;
	r = 3.0;
	maxspeed = ms;
	maxforce = mf;
	acceleration = ofVec2f(0, 0);
	velocity = ofVec2f(0, 0);
}

void Vehicle::run() {
	update();
	borders();
	display();
}

void Vehicle::update() {

}

void Vehicle::borders() {

}

void Vehicle::display() {
	
}

void Vehicle::follow(FlowField flow) {
	ofVec2f desired = flow.lookup(position);
	desired.scale(maxspeed);
	ofVec2f steer = desired - velocity;
	steer.getLimited(maxforce);
	applyForce(steer);
}

void Vehicle::applyForce(ofVec2f force) {
	acceleration += force;
}
