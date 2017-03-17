#pragma once

#include "ofMain.h"
#include "FlowField.h"

class Vehicle
{
public:
	Vehicle();
	Vehicle(ofVec2f l, float ms, float mf);

	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float r;
	float maxforce;
	float maxspeed;

	void run();
	void update();
	void borders();
	void display();
	void follow(FlowField flow);

	void applyForce(ofVec2f force);
};

