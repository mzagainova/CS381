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
		commands[0]->tick(dt);

		if(commands[0]->done())
		{
			delete commands[0];
			commands.erase(commands.begin());
		}
	}
}

void UnitAI::SetCommand(Command *c){
	for(unsigned int i = 0; i < commands.size(); i ++)
	{
		if(commands[i])
		{
			delete commands[i];
		}
	}
	commands.clear();
	commands.push_back(c);
}

void UnitAI::AddCommand(Command *c){

	commands.push_back(c);
}




