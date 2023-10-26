#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
//************************************************
// entitymanager.h
//************************************************

#include <entt/entt.hpp>
#include "subject.h"

enum EntityFlag {
  ENTITY_FLAG_DESTROY
};

class EntityManager : public Subject
{
public:
    EntityManager(entt::registry *);
    void createBullet(void);
    entt::entity createPlayer(void);
    entt::entity createZombie(entt::entity);
    entt::entity create_ammo(void);
private:
    entt::registry* registry_; //Directly coupled to the global ECS for ease
};

#endif //_ENTITYMANAGER_H_
