/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:39:02 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/17 14:50:20 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENVIRONMENT_HPP
# define GAME_ENVIRONMENT_HPP

/* map array, food */

/*
    You can generate food by getting the area of the map, generating a random
    number within the area size and then placing food at thhat position.
    To get the random position on the map, you will need to take the random number, 
    divide it by the map-width to get the row and use the remainder as positioning on the row.

    EXAMPLE:
        map_area = map_w * map_h; (map_area = 8 * 6)
        rand_pos = rand() % map_area;
        food_row = rand_pos / 8;
        food_col = rand_pos % 8;
        map[food_row][food_col] = MAP_FOOD;
*/

# include <cstdlib>
# include <ctime>

# define MAP_NONE       0
# define MAP_WALL       1
# define MAP_FOOD       2
# define MAP_PLAYER     10
# define MAP_MAX_FOOD   3

typedef enum    e_input {
    NONE = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    QUIT,
    PAUSE,
    MOD1,
    MOD2,
    MOD3,
    SUPACHOMP,
}               t_input;

class GameEnvironment {
public:
    GameEnvironment(const unsigned int w, const unsigned int h);
	GameEnvironment(GameEnvironment const & src);
	GameEnvironment & operator=(GameEnvironment const & rhs);
	~GameEnvironment(void);
    
    unsigned int    **map;
    unsigned int    mapWidth;
    unsigned int    mapHeight;
    unsigned int    snakeLength;  
    unsigned int    snakeLocation;
    t_input         snakeDirection;
    unsigned int    foodLocation[MAP_MAX_FOOD];
    unsigned int    foodCount;
    bool            paused;
    bool            supachomp;
    bool            snakeAlive;

/*    unsigned int    getMapWidth(void) const;
    unsigned int    getMapHeight(void) const;*/
    void            changeSnakeDir(t_input action);
    void            generateFood(const int amount);

    void            updateMapData(void);
    unsigned int    moveToNextBlock(void);
    unsigned int    checkPlayerCollision(unsigned int x, unsigned int y);
    void            gameOver(void);

    /*unsigned int    spawnFood();*/

    /*int loadNewMap(const unsigned int w, const unsigned int h);*/

private:
};

#endif /* GAME_ENVIRONMENT_HPP */