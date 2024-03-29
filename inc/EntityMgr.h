#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Entity381.h>
#include <Types381.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  std::vector<Entity381*> entities;
  std::vector<Entity381*> selectedEntity;
  int selectedEntityIndex;


  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
  void SelectNextEntity();

  void Tick(float dt);

protected:

private:
	void CreateDDG51(Ogre::Vector3 pos);
	void CreateCarrier(Ogre::Vector3 pos);
	void CreateSpeedBoat(Ogre::Vector3 pos);
	void CreateFrigate(Ogre::Vector3 pos);
	void CreateAlien(Ogre::Vector3 pos);
	void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
	void CreateBanshee(Ogre::Vector3 pos);

  int count;

};

#endif // #ifndef __EntityMgr_h_
