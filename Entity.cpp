#include "Entity.hpp"


/////////////////////////////////[  constructor/destructor  ]////////////////////////////////////////

Entity::Entity(void)
{

    setLocation(getLocation('x') + 10, getLocation('y'));
    displayGameObject();

}

Entity::Entity(Entity const & src)
{
    *this = src;
    return;
}


Entity::~Entity(void)
{
    return;
}

Entity::Entity(WINDOW * win, int xPos, int yPos) : GameObject::GameObject(win, 'B')
{
    //mvwaddch(this->getWindow(), this->getLocation('y') + 10, this->getLocation('x') + 10, '*');
    setLocation(xPos, yPos);
}
/////////////////////////////////[  overloaded operators  ]////////////////////////////////////////

Entity& Entity::operator=(Entity const & rhs)
{
    if (this != &rhs)
    {
		this->setLocation(rhs.getLocation('x'), rhs.getLocation('y'));
        this->setMax('x', rhs.getMax('x'));
		this->setMax('y', rhs.getMax('y'));
        this->setWindow(rhs.getWindow());
        this->_entities = rhs._entities;
        this->setCharacter(rhs.getCharacter());
        this->setAlive(rhs.isAlive());
    }

    return *this;
}



/*void    Entity::shoot(Entity object, int location)
{

}

bool        Entity::hitPlayer()
{

}*/
