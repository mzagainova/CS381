/*
 * Command.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <Entity381.h>
#include <OgreVector3.h>

enum COMMAND_TYPE
{
	Type_MoveTo,
	Type_Intercept,
	Type_Follow
};

class Entity381;

class Command {

public:
	Command();
	Command(Entity381* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381* entity;
	COMMAND_TYPE commandType;

};

class MoveTo: public Command {

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};

class Intercept: public Command {

public:
	Intercept(Entity381* ent, Entity381* targetEnt);
	~Intercept();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;
	Ogre::Vector3 predictedLocation;
	Ogre::Vector3 diff, relVel, t;
	Entity381 *targetEntity;

};



#endif /* COMMAND_H_ */
