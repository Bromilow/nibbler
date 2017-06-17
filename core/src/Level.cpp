/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 20:15:03 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/16 17:25:29 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Level.hpp"

Level::Level(const unsigned int w, const unsigned int h) : mapWidth(w), mapHeight(h), snakeLength(4), snakeDirection(UP)
{
    // Create map height
    map = new unsigned int*[h];
    srand(time(0));

    for (unsigned int y = 0; y < h; ++y) {
        // Create new row
        map[y] = new unsigned int[w];

        // Add scenery to row
        for (unsigned int x = 0; x < w; ++x) {
            // If sides of map,
            if (y == 0 || y == (h - 1) || x == 0 || x == (w - 1)) {
                // Assign wall/boundary
                map[y][x] = MAP_WALL;
            } else if (y == (h / 2) && x == (w / 2)) {
                // Center of map, assign player start position
                this->snakeLocation = y * x;
                map[y][x] = MAP_PLAYER;
                for (int i = 1 ; i <= 4; ++i)
                    map[y + i][x] = MAP_PLAYER + i;
            } else {
                // Assign empty block
                map[y][x] = MAP_NONE;
            }
        }
    }
}



Level::Level(Level const & src)
{
    if (this != &src)
    {
        *this = src;
    }
}

Level & Level::operator=(Level const & rhs)
{
    if (this != &rhs)
    {
        this->map = rhs.map;
        this->mapWidth = rhs.mapWidth;
        this->mapHeight = rhs.mapHeight;
        this->snakeLength = rhs.snakeLength;
        this->snakeLocation = rhs.snakeLocation;
        this->snakeDirection = rhs.snakeDirection;
    }
    return (*this);
}

Level::~Level(void)
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

unsigned int    Level::getMapWidth(void) const
{
    return (this->mapWidth);
}

unsigned int    Level::getMapHeight(void) const
{
    return (this->mapHeight);
}

void            Level::changeSnakeDir(t_input action)
{
    if (this->snakeDirection % 2 != action % 2)
        this->snakeDirection = action;
}

 unsigned int    Level::moveToNextBlock(void)
 {
    unsigned int    x;
    unsigned int    y;

    x = this->snakeLocation % this->mapWidth;
    y = this->snakeLocation / this->mapWidth;

    switch (this->snakeDirection)
    {
        case UP:
            --y;
        case RIGHT:
            ++x;
        case DOWN:
            ++y;
        case LEFT:
            --x;
    }
    if (this->checkCollision(x, y))
        return (0);
    else
        this->map[y][x] = MAP_PLAYER; 
    return(1);      
}

void            Level::updateMapData(void)
{
    int x, y;

    for (y = 0; y < this->mapHeight; ++y)
    {
        x = 0;
        for (; x < this->mapWidth; ++x)
        {
            if (this->map[y][x] == this->snakeLength + 9)
                this->map[y][x] = MAP_NONE;
            if (this->map[y][x] >= MAP_PLAYER)
                this->map[y][x] += 1;
        }
    }
}

void            Level::generateFood(const int amount)
{
    int tmp;

    for (int i = 0; i < amount && i < MAP_FOOD; ++i)
    {
        tmp = rand % (this->mapHeight * this->mapWidth);
        if (this->checkCollision( tmp % this->mapWidth, tmp / this->mapWidth))
            --i;
        else
            this->foodLocation[i] = tmp;
    }
}