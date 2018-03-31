/*
 * UnitAI.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: mzagainova
 */
#include <UnitAI.h>

UnitAI::UnitAI(){

}

UnitAI::~UnitAI(){
}

void UnitAI::Tick(float dt){
	for(int i = 0; i < commands.size(); i++){
		while(!commands[i]->done()){
			commands[i]->tick(dt);
		}
	}
}

void UnitAI::SetCommand(Command *c){
	commands.clear();
	commands.push_front(c);
}

void UnitAI::AddCommand(Command *c){
	commands.push_back(c);
}




