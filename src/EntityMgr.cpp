/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */
#include "Entity381.h"
#include <EntityMgr.h>
#include <Engine.h>
#include "InputMgr.h"
#include "FlyingEntity381.h"

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreateEntity(std::string meshfilename, Ogre::Vector3 pos){
	Entity381 *ent = new Entity381(this->engine, meshfilename, pos, count);
	count++;
	entities.push_back(ent);
}

void EntityMgr::CreateBanshee(Ogre::Vector3 pos){
	Banshee *ent = new Banshee(this->engine, pos, count);
	count++;
	entities.push_back((FlyingEntity381 *) ent);
}




void EntityMgr::SelectNextEntity(){
	selectedEntityIndex += 1;
	selectedEntityIndex %= entities.size();

	if(engine->inputMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	{
		if(std::find(selectedEntity.begin(), selectedEntity.end(), entities[selectedEntityIndex]) == selectedEntity.end())
		{
			selectedEntity.push_back(entities[selectedEntityIndex]);
		}

	}

	else
	{
		while(!selectedEntity.empty())
		{
			selectedEntity.pop_back();
		}
		selectedEntity.push_back(entities[selectedEntityIndex]);
	}

	for(int i = 0; i < (int)entities.size(); i++)
	{
		entities[i]->isSelected = false;
	}

	for(int i = 0; i < (int)selectedEntity.size(); i++)
	{
		selectedEntity[i]->isSelected = true;
	}

}



void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	switch(entType){
	case BansheeType:
		CreateBanshee(pos);
		break;
		default:
		CreateEntity("robot.mesh", pos);
		break;
	}
}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < (int)entities.size(); i++){
		entities[i]->isSelected = false;
	}
	for(int i = 0; i < (int)selectedEntity.size(); i++){
		selectedEntity[i]->isSelected = true;
	}
	for(int i = 0; i < count; i++){
		entities[i]->Tick(dt);
	}
}
