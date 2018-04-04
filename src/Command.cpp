/*
 * Command.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */
#include <Command.h>
#include "Utils.h"

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
	targetLocation.y = entity->position.y;
	MOVE_DISTANCE_THRESHOLD = targetLocation.squaredDistance(entity->position);
	entity->desiredSpeed = entity->maxSpeed;

	init();
}

MoveTo::~MoveTo(){

}

void MoveTo::init(){

}

// move currently selected ent to location
void MoveTo::tick(float dt){

	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian temp = Ogre::Math::ATan2(-difference.z, difference.x) ;
	entity->desiredHeading = temp.valueDegrees();
	entity->desiredHeading = FixAngle(entity->desiredHeading);

	MOVE_DISTANCE_THRESHOLD = difference.squaredLength();

	if(MOVE_DISTANCE_THRESHOLD < pow(pow(entity->maxSpeed, 2)/(2*entity->acceleration), 2))
	{
		entity->desiredSpeed = 0;
	}
}

bool MoveTo::done(){

	if(MOVE_DISTANCE_THRESHOLD < pow(pow(entity->maxSpeed, 2)/(2*entity->acceleration), 2))
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
	Ogre::Radian temp = Ogre::Math::ATan2(diff.z, diff.x) ;
	entity->desiredHeading = temp.valueDegrees();
	entity->desiredSpeed = entity->maxSpeed;
	MOVE_DISTANCE_THRESHOLD = diff.squaredLength();

	t = diff / relVel;
}

void Intercept::tick(float dt){

	predictedLocation = targetEntity->position + targetEntity->speed * t;

	Ogre::Vector3 difference = predictedLocation - entity->position;
	Ogre::Radian temp = Ogre::Math::ATan2(difference.z, difference.x) ;
	entity->desiredHeading = temp.valueDegrees();

	MOVE_DISTANCE_THRESHOLD = predictedLocation.squaredDistance(entity->position);

	if(MOVE_DISTANCE_THRESHOLD < 3000)
	{
		entity->desiredSpeed = 0;
	}
}

bool Intercept::done(){
	if(MOVE_DISTANCE_THRESHOLD < 3000)
	{
		return true;
	}
	return false;
}

Follow::Follow(Entity381* ent,  Entity381* target)
{
	targetLocation = target->position;
	entity = ent;
	targetEnt = target;
	targetLocation.y = entity->position.y;
	MOVE_DISTANCE_THRESHOLD = targetLocation.squaredDistance(entity->position);
	entity->desiredSpeed = entity->maxSpeed;

	init();
}

Follow::~Follow()
{

}

void Follow::init(){

}

// move currently selected ent to location
void Follow::tick(float dt){
	targetLocation = targetEnt->position;
	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian temp = Ogre::Math::ATan2(-difference.z, difference.x) ;
	entity->desiredHeading = temp.valueDegrees();
	entity->desiredHeading = FixAngle(entity->desiredHeading);
	MOVE_DISTANCE_THRESHOLD = difference.squaredLength();

	if(MOVE_DISTANCE_THRESHOLD < pow(pow(entity->maxSpeed, 2)/(2*entity->acceleration), 2))
	{
		entity->desiredSpeed = 0;
	}
	else
	{
		entity->desiredSpeed = entity->maxSpeed;
	}
}

bool Follow::done(){

	return false;
}
