/*
 * FlyingEntity381.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#include <Physics3D.h>
#include "FlyingEntity381.h"

FlyingEntity381::FlyingEntity381(Engine *engine, Ogre::Vector3 pos, int ident):
	Entity381(engine, "banshee.mesh", pos, ident) {
	// TODO Auto-generated constructor stub
	minAltitude = 0;
	maxAltitude = 1000;
	altitude = 0;
	desiredAltitude = 0;
	climbRate = 1;
	aspects.clear();
	Physics3D * phx = new Physics3D(this);
	Renderable *renderable = new Renderable(this);
	aspects.push_back((Aspect *) phx);
	aspects.push_back((Aspect *) renderable);
}

FlyingEntity381::~FlyingEntity381() {
	// TODO Auto-generated destructor stub
}


//-------------------------------------------------------------------------------------------------------------------------------
Banshee::Banshee(Engine *engine, Ogre::Vector3 pos, int ident):
		FlyingEntity381(engine, pos, ident){
	meshfilename = "banshee.mesh";
	this->minSpeed = 0;
	this->maxSpeed = 16.0f;//meters per second...
	this->minAltitude = 10;
	this->maxAltitude = 500;
	this->climbRate = 50;
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	this->altitude = pos.y;
	this->desiredAltitude = altitude;
	std::cout << "Created: " << this->name << std::endl;
}

Banshee::~Banshee(){

}

