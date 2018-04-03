/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include "Aspect.h"

#include <Utils.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine) {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	  #if defined OIS_WIN32_PLATFORM
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	  	  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	  	  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	  #elif defined OIS_LINUX_PLATFORM
	  	  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	  	  //pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	  	  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
	  #endif
	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, false));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, false));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;

	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){
	//Must capture both every tick for buffered input to work
	mMouse->capture();
	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}

//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);
	UpdateMouse(dt);
}

void InputMgr::UpdateMouse(float dt)
{
	static bool left_down;

	if(mMouse->getMouseState().buttonDown(OIS::MB_Left))
	{
		left_down = true;
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		OIS::MouseState arg = mMouse->getMouseState();

		Ogre::Real offsetX = arg.X.abs / screenWidth;
		Ogre::Real offsetY = arg.Y.abs / screenHeight;

		Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(offsetX, offsetY);

		std::pair<bool, float> result = mouseRay.intersects(engine->gameMgr->mPlane);

		if(result.first)
		{
			Ogre::Vector3 point = mouseRay.getPoint(result.second);
			selectClosestEntity(point);
		}
	}
	if(mMouse->getMouseState().buttonDown(OIS::MB_Right))
	{
		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();
		OIS::MouseState arg = mMouse->getMouseState();

		Ogre::Real offsetX = arg.X.abs / screenWidth;
		Ogre::Real offsetY = arg.Y.abs / screenHeight;

		Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(offsetX, offsetY);

		std::pair<bool, float> result = mouseRay.intersects(engine->gameMgr->mPlane);
		Ogre::Vector3 point = mouseRay.getPoint(result.second);

		if(returnClosestEntity(point))
		{
			if(result.first)
			{
				Ogre::Vector3 point = mouseRay.getPoint(result.second);
				if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				{

					for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i ++)
					{
						Intercept* temp = new Intercept(engine->entityMgr->selectedEntity[i], returnClosestEntity(point));
						engine->entityMgr->selectedEntity[i]->aspects[2]->AddCommand(temp);
					}
				}
				else
				{
					for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i ++)
					{
						Intercept* temp = new Intercept(engine->entityMgr->selectedEntity[i], returnClosestEntity(point));
						engine->entityMgr->selectedEntity[i]->aspects[2]->SetCommand(temp);
					}
				}
			}
		}
		else
		{
			if(result.first)
			{
				Ogre::Vector3 point = mouseRay.getPoint(result.second);
				if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				{

					for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i ++)
					{
						MoveTo* temp = new MoveTo(engine->entityMgr->selectedEntity[i], point);
						engine->entityMgr->selectedEntity[i]->aspects[2]->AddCommand(temp);
					}
				}
				else
				{
					for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i ++)
					{
						MoveTo* temp = new MoveTo(engine->entityMgr->selectedEntity[i], point);
						engine->entityMgr->selectedEntity[i]->aspects[2]->SetCommand(temp);
					}
				}
			}
		}
	}
	else
	{
		left_down = false;
	}

}

void InputMgr::selectClosestEntity(Ogre::Vector3 location)
{

	float maxDistance = 1000;
	Entity381* closest;
	for(size_t i = 0; i < engine->entityMgr->entities.size(); i++)
	{
		if(location.distance(engine->entityMgr->entities[i]->position) < maxDistance)
		{
			maxDistance = location.distance(engine->entityMgr->entities[i]->position);
			closest = engine->entityMgr->entities[i];
		}
	}
	if(closest)
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		{
			if(!closest->isSelected)
				engine->entityMgr->selectedEntity.push_back(closest);
		}
		else
		{
			for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i++)
			{
				engine->entityMgr->selectedEntity.pop_back();
			}
			engine->entityMgr->selectedEntity.push_back(closest);
		}

	}
}

Entity381* InputMgr::returnClosestEntity(Ogre::Vector3 location)
{

	float maxDistance = 1000;
	Entity381* closest;
	for(size_t i = 0; i < engine->entityMgr->entities.size(); i++)
	{
		if(location.distance(engine->entityMgr->entities[i]->position) < maxDistance)
		{
			maxDistance = location.distance(engine->entityMgr->entities[i]->position);
			closest = engine->entityMgr->entities[i];
		}
	}
	/*if(closest)
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		{
			if(!closest->isSelected)
				return closest;
		}
		/*else
		{
			for(size_t i = 0; i < engine->entityMgr->selectedEntity.size(); i++)
			{
				engine->entityMgr->selectedEntity.pop_back();
			}
			engine->entityMgr->selectedEntity.push_back(closest);
		}
	}*/
	return closest;
}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	 if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	 {
		 move = 600.0f;
	 	 rotate = .4f;
	 }
	 else
		 move = 400.0f;

	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_R))
	    dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_F))
	    dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_Z))
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_X))
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_Q))
	  	  engine->gameMgr->cameraNode->pitch(Ogre::Degree(5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_E))
	  	  engine->gameMgr->cameraNode->pitch(Ogre::Degree(-5 * rotate));

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	      dirVec.x -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	      dirVec.x += move;

	  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}
void InputMgr::UpdateVelocityAndSelection(float dt){
	static bool tab_down_last_frame;
	float deltaDesiredSpeed = 200.0;
	float deltaDesiredHeading = 50.0;

	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredSpeed += deltaDesiredSpeed * dt;
		}

	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredSpeed -= deltaDesiredSpeed * dt;
		}
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredHeading -= deltaDesiredHeading * dt;
		}
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredHeading += deltaDesiredHeading * dt;
		}
	}

	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD9)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredAltitude += deltaDesiredSpeed * dt;
		}
	}

	if(mKeyboard->isKeyDown(OIS::KC_NUMPAD3)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->desiredAltitude -= deltaDesiredSpeed * dt;
		}
	}

	for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
	{
		engine->entityMgr->selectedEntity[i]->desiredHeading = FixAngle(engine->entityMgr->selectedEntity[i]->desiredHeading);
	}

	//Set velocity to zero....
	if(mKeyboard->isKeyDown(OIS::KC_SPACE)){
		for(int i = 0; i < (int)engine->entityMgr->selectedEntity.size(); i++)
		{
			engine->entityMgr->selectedEntity[i]->velocity = Ogre::Vector3::ZERO;
			engine->entityMgr->selectedEntity[i]->desiredSpeed = engine->entityMgr->selectedEntity[i]->speed = 0;
			engine->entityMgr->selectedEntity[i]->desiredHeading = engine->entityMgr->selectedEntity[i]->heading;

		}
	}

	//tab handling
	if(mKeyboard->isKeyDown(OIS::KC_TAB)){
		if(!tab_down_last_frame)
			engine->entityMgr->SelectNextEntity();
		tab_down_last_frame = true;
	}
	else
	{
		tab_down_last_frame = false;
	}

}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	return true;
}
