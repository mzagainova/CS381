/*
 * Command.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */
#include <Command.h>

Command::Command()
{

}

Command::Command(Entity381* ent, COMMAND_TYPE ct){

}

Command::~Command(){

}

void Command::init(){

}

void Command::tick(float dt){

}

bool Command::done(){
	return true;
}


MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location)
{
	targetLocation = location;
	entity = ent;
	MOVE_DISTANCE_THRESHOLD = targetLocation.squaredDistance(entity->position);
	init();
}

MoveTo::~MoveTo(){

}

void MoveTo::init(){
	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian temp = Ogre::Math::ATan2(difference.y, difference.x) * 180/ 3.1415926;
	entity->desiredHeading = temp.valueRadians();
	entity->desiredSpeed = entity->maxSpeed;
}

// move currently selected ent to location
void MoveTo::tick(float dt){
	MOVE_DISTANCE_THRESHOLD = targetLocation.squaredDistance(entity->position);

	if(MOVE_DISTANCE_THRESHOLD < 100)
	{
		entity->desiredSpeed = 0;
	}
}

bool MoveTo::done(){
	if(MOVE_DISTANCE_THRESHOLD < 10)
	{
		return true;
	}
	return false;
}


Intercept::Intercept(Entity381* ent, Entity381* targetEnt){
	entity = ent;
	targetEntity = targetEnt;
	diff = targetEntity->position - entity->position;
	relVel = targetEntity->speed - entity->speed;

	init();
}

Intercept::~Intercept(){

}

void Intercept::init(){
	Ogre::Radian temp = Ogre::Math::ATan2(diff.y, diff.x) * 180/ 3.1415926;
	entity->desiredHeading = temp.valueRadians();
	entity->desiredSpeed = entity->maxSpeed;

	t = diff / relVel;
}

void Intercept::tick(float dt){
	predictedLocation = targetEntity->position + targetEntity->speed * t;

	MOVE_DISTANCE_THRESHOLD = predictedLocation.squaredDistance(entity->position);

	if(MOVE_DISTANCE_THRESHOLD < 100)
	{
		entity->desiredSpeed = 0;
	}
}

bool Intercept::done(){

}

