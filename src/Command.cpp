/*
 * Command.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */
#include <Command.h>

Command::Command(Entity381* ent, COMMAND_TYPE ct){

}

Command::~Command(){

}

void Command::init(){

}

void Command::tick(float dt){

}

bool Command::done(){

}


MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location):
	Command(ent, MoveTo){

}

MoveTo::MoveTo~MoveTo(){

}

void MoveTo::init(){

}

// move currently selected ent to location
void MoveTo::tick(float dt){

}

bool MoveTo::done(){

}


Intercept::Intercept(Entity381* ent, Ogre::Vector3 location):
	Command(ent, Intercept){

}

Intercept::~Intercept(){

}

void Intercept::init(){

}

void Intercept::tick(float dt){

}

bool Intercept::done(){

}

