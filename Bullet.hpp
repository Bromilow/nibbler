
#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include "GameObject.hpp"                   			  // soon to be base


class Bullet : public GameObject
{
	public:
		Bullet(void);
		Bullet(Bullet const & src);
		Bullet& operator=(Bullet const & rhs);
		~Bullet(void);


void	    displayBullet();
void    	shoot(Bullet object);                         // fly accross the screen
void        hitPlayer();
void        hitBullet();

// wont have collision check -- basic object
		

	private:

		int		_xLoc;
		int		_yLoc;
        char	_character;
		int		*location;


};

#endif