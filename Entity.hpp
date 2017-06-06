
#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "GameObject.hpp"


class Entity : public GameObject
{
	public:

Entity(void);
Entity(WINDOW * win, int xPos, int yPos);
Entity(Entity const & src);
Entity& operator=(Entity const & rhs);
~Entity(void);

/*
void    		shoot(Entity object, int location);          
bool         	hitPlayer();
bool         	hitBullet();*/

// have collision detection -- 

private:
	Entity  *_entities;
};

#endif
