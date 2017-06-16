/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Level.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 18:39:02 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/16 15:03:50 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_HPP
# define LEVEL_HPP

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

# define MAP_NONE 0
# define MAP_WALL 1
# define MAP_FOOD 2
# define MAP_PLAYER 10

# include <cstdlib>

class Level {
public:
    Level(const unsigned int w, const unsigned int h);
	Level(Level const & src);
	Level & operator=(Level const & rhs);
	~Level(void);
    
    unsigned int    **map;
    unsigned int    mapWidth;
    unsigned int    mapHeight;

    unsigned int    getMapWidth(void) const;
    unsigned int    getMapHeight(void) const;
    /*unsigned int    spawnFood();*/

    /*int loadNewMap(const unsigned int w, const unsigned int h);*/

private:

};

#endif /* LEVEL_HPP */