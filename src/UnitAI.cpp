/*
 * UnitAI.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */
#include <UnitAI.h>

UnitAI::UnitAI(): Aspect(NULL){

}

UnitAI::~UnitAI(){
}

void UnitAI::Tick(float dt){
	if(!commands.empty())
	{
		if(commands.front()->done())
		{
			commands.pop_front();
		}
		commands.front()->tick(dt);
	}
}

void UnitAI::SetCommand(Command *c){
	commands.clear();
	commands.push_front(c);
	Ogre::LogManager::getSingletonPtr()->logMessage("*** set command ***");
}

void UnitAI::AddCommand(Command *c){
	commands.push_back(c);
	Ogre::LogManager::getSingletonPtr()->logMessage("*** add command ***");
}




