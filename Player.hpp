#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "GameObject.hpp"

class Player : public GameObject {
	public:
		Player(void);
		Player(WINDOW * win);
		Player(Player const & src);
		Player& operator=(Player const & rhs);
		~Player(void);

		// have collision detection -- 

};

#endif
