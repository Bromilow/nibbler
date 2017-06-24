/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 21:30:11 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:18:05 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameEnvironment.hpp"

GameEnvironment::GameEnvironment(const unsigned int w, const unsigned int h)
    : mapWidth(w), mapHeight(h), snakeLength(4), snakeDirection(UP), foodCount(3),
        paused(false), supachomp(false), snakeAlive(true), gameTime(0), gameFPS(DEFAULT_GAME_FPS)
{
    // Seed rand
    srand(time(0));

    // Set gameSpeed. Round to nearest 100th
    this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;

    // Create map height
    map = new unsigned int*[h];

    for (unsigned int y = 0; y < h; ++y) {
        map[y] = new unsigned int[w];
        // Add scenery to row
        for (unsigned int x = 0; x < w; ++x) {
            if (y == 0 || y == (h - 1) || x == 0 || x == (w - 1))
                map[y][x] = MAP_WALL;
            else if (y == (h / 2) && x == (w / 2)) {
                this->snakeLocation = (y * w) + (x + 1);
                map[y][x] = MAP_PLAYER;
            } else
                map[y][x] = MAP_NONE;
        }
    }

    // Init food
    for (int i = 0; i < MAP_MAX_FOOD; ++i)
        this->foodLocation[i] = 0;
    this->generateFood(this->foodCount);
}



GameEnvironment::GameEnvironment(GameEnvironment const & src)
{
    if (this != &src)
        *this = src;
}

GameEnvironment & GameEnvironment::operator=(GameEnvironment const & rhs)
{
    if (this != &rhs)
    {
        this->map = rhs.map;
        this->mapWidth = rhs.mapWidth;
        this->mapHeight = rhs.mapHeight;
        this->snakeLength = rhs.snakeLength;
        this->snakeLocation = rhs.snakeLocation;
        this->snakeDirection = rhs.snakeDirection;
        for (int i = 0; i < MAP_MAX_FOOD; ++i)
            this->foodLocation[i] = rhs.foodLocation[i];
        this->foodCount = rhs.foodCount;
        this->paused = rhs.paused;
        this->supachomp = rhs.supachomp;
        this->snakeAlive = rhs.snakeAlive;
        this->gameTime = rhs.gameTime;
        this->gameFPS = rhs.gameFPS;
        this->gameSpeed = rhs.gameSpeed;
    }
    return (*this);
}

GameEnvironment::~GameEnvironment(void)
{
    if (map != NULL)
    {
        unsigned int i = 0;
        while (i < mapHeight)
        {
            delete[] map[i];
            map[i] = NULL;
            ++i;
        }
        delete[] map;
        map = NULL;
    }
}

void            GameEnvironment::changeSnakeDir(t_input action)
{
    if (this->snakeDirection % 2 != action % 2)
        this->snakeDirection = action;
}

void            GameEnvironment::increaseGameSpeed(void)
{
    if (this->gameFPS < 25)
    {
        this->gameFPS++;
        this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;
    }
}

void            GameEnvironment::decreaseGameSpeed(void)
{
    if (this->gameFPS > 1)
    {
        this->gameFPS--;
        this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;
    }
}

void            GameEnvironment::updateMapData(void)
{
    unsigned int x, y;

    for (y = 0; y < this->mapHeight; ++y)
    {
        x = 0;
        for (; x < this->mapWidth; ++x)
        {
            if (this->map[y][x] == this->snakeLength + 9)
                this->map[y][x] = MAP_NONE;
            else if (this->map[y][x] >= MAP_PLAYER)
                this->map[y][x] += 1;
        }
    }
    if (!(this->moveToNextBlock()))
        this->gameOver();
    else if (this->snakeLength % 10 == 0)
        this->increaseGameSpeed();
}

unsigned int    GameEnvironment::moveToNextBlock(void)
{
    unsigned int    x;
    unsigned int    y;

    x = this->snakeLocation % this->mapWidth - 1;
    y = this->snakeLocation / this->mapWidth;

    if (this->snakeDirection == UP)
            --y;
    else if (this->snakeDirection == RIGHT)
            ++x;
    else if (this->snakeDirection == DOWN)
            ++y;
    else if (this->snakeDirection == LEFT)
            --x;
    
    if (this->checkPlayerCollision(x, y))
        return (0);
    else {
        this->map[y][x] = MAP_PLAYER;
        this->snakeLocation = (y * this->mapWidth) + (x + 1);
    }
    return(1);     
}

unsigned int    GameEnvironment::checkPlayerCollision(unsigned int x, unsigned int y)
{
    unsigned int    pos, i;
    
    if (this->map[y][x] != MAP_NONE && this->map[y][x] != MAP_FOOD)
        return (1);
    else if (this->map[y][x] == MAP_FOOD)
    {
        this->snakeLength++;
        pos = (y * this->mapWidth) + (x + 1);
        for (i = 0; i < this->foodCount; ++i)
            if (this->foodLocation[i] == pos)
                this->foodLocation[i] = 0;
        this->generateFood(this->foodCount);

    }
    return (0);
}

void            GameEnvironment::generateFood(const int amount)
{
    int rand_pos, x, y;

    for (int i = 0; i < amount && i < MAP_MAX_FOOD; ++i)
        if (this->foodLocation[i] == 0)
        {
            // Get random position
            rand_pos = rand() % (this->mapHeight * this->mapWidth);
            x = (rand_pos % this->mapWidth) - 1;
            y = rand_pos / this->mapWidth;

            // Check random position
            if (this->map[y][x] != MAP_NONE)
                --i;
            else if (this->map[y][x] == MAP_NONE)
            {
                this->foodLocation[i] = rand_pos;
                this->map[y][x] = MAP_FOOD;
            }
        }
}

void            GameEnvironment::gameOver(void)
{
    this->snakeAlive = false;
}