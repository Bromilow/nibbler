/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:39:02 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/25 13:13:46 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENVIRONMENT_HPP
# define GAME_ENVIRONMENT_HPP

# include <cstdlib>
# include <time.h>

# define MIN_MAP_W    		0
# define MIN_MAP_H    		0
# define MAX_MAP_W    		225
# define MAX_MAP_H    		68
# define DEFAULT_GAME_FPS	2
# define ONE_NANOSEC		1000000000
# define N_MODULES			3
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
    INCR_SPD,
    DECR_SPD
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
        unsigned int	gameFPS;
        unsigned int	gameSpeed;

        void            changeSnakeDir(t_input action);
        void            generateFood(const int amount);
        void            setGameSpeed(int amt);
        void            updateMapData(void);
        unsigned int    moveToNextBlock(void);
        unsigned int    checkPlayerCollision(unsigned int x, unsigned int y);
        void            gameOver(void);
};

#endif /* GAME_ENVIRONMENT_HPP */