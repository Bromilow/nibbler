/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <rbromilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:39:02 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/24 19:36:24 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENVIRONMENT_HPP
# define GAME_ENVIRONMENT_HPP

# include <cstdlib>
# include <ctime>

# define MIN_MAP_W    		0
# define MIN_MAP_H    		0
# define MAX_MAP_W    		225
# define MAX_MAP_H    		68
# define DEFAULT_GAME_FPS	2
# define ONE_NANOSEC		1000000000
# define N_MODULES			4
# define MAP_NONE           0
# define MAP_WALL           1
# define MAP_FOOD           2
# define MAP_PLAYER         10
# define MAP_MAX_FOOD       3

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
    unsigned int	gameTime;
    unsigned int	gameFPS;			/* default: 60fps     */
	unsigned int	gameSpeed;			/* gameSpeed = (ONE_NANOSEC / gameFPS) / 100; gameSpeed *= 100; gameSpeed is now rounded to hundreds */

/*    unsigned int    getMapWidth(void) const;
    unsigned int    getMapHeight(void) const;*/
    void            changeSnakeDir(t_input action);
    void            generateFood(const int amount);
    void            increaseGameSpeed(void);
    void            decreaseGameSpeed(void);
    void            updateMapData(void);
    unsigned int    moveToNextBlock(void);
    unsigned int    checkPlayerCollision(unsigned int x, unsigned int y);
    void            gameOver(void);

    /*unsigned int    spawnFood();*/

    /*int loadNewMap(const unsigned int w, const unsigned int h);*/

private:
};

#endif /* GAME_ENVIRONMENT_HPP */