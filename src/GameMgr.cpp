/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine), mPlane(Ogre::Vector3::UNIT_Y, 0) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel(){

	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  cameraNode->setPosition(0, 0, 0);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  MakeGround();
	  MakeSky();
	  MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-1000, 50, 0);

	for(int i = 0; i < 5; i++)
	{
		engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);
		pos.x += 500;
	}

	pos = Ogre::Vector3(-1000, 0, -300);
	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection
}

void GameMgr::MakeGround(){


	  Ogre::MeshManager::getSingleton().createPlane(
	    "ground",
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    mPlane,
	    15000, 15000, 20, 20,
	    true,
	    1, 5, 5,
	    Ogre::Vector3::UNIT_Z);

	  Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
	  engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  groundEntity->setCastShadows(false);
	  //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	  //groundEntity->setMaterialName("OceanHLSL_GLSL");
	  groundEntity->setMaterialName("Ocean2_Cg");
	  //groundEntity->setMaterialName("NavyCg");
}

void GameMgr::MakeSky(){
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}
