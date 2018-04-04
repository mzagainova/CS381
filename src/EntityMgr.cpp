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
		selectedEntity.clear();
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
	case DDG51Type:
		CreateDDG51(pos);
		break;
	case CarrierType:
		CreateCarrier(pos);
		break;
	case SpeedBoatType:
		CreateSpeedBoat(pos);
		break;
	case FrigateType:
		CreateFrigate(pos);
		break;
	case AlienType:
		CreateAlien(pos);
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
	for(unsigned int i = 0; i < entities.size(); i++){
		entities[i]->Tick(dt);
	}
}

void EntityMgr::CreateDDG51(Ogre::Vector3 pos){
	DDG51 *ent = new DDG51(this->engine, "ddg51.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateCarrier(Ogre::Vector3 pos){
	Carrier *ent = new Carrier(this->engine, "cvn68.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}

void EntityMgr::CreateSpeedBoat(Ogre::Vector3 pos){
	SpeedBoat *ent = new SpeedBoat(this->engine, "cigarette.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateFrigate(Ogre::Vector3 pos){
	Frigate *ent = new Frigate(this->engine, "sleek.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
void EntityMgr::CreateAlien(Ogre::Vector3 pos){
	Alien *ent = new Alien(this->engine, "alienship.mesh", pos, count);
	count++;
	entities.push_back((Entity381 *) ent);
}
