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

Level::Level(const unsigned int w, const unsigned int h) : mapWidth(w), mapHeight(h)
{
    // Create map height
    map = new unsigned int*[h];

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
                map[y][x] = MAP_PLAYER;
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