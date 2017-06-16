/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:40:15 by kbamping          #+#    #+#             */
/*   Updated: 2017/05/28 10:02:52 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(void)
{
    return;
}

Snake::Snake(WINDOW * win, char ch)
{
    this->_character = ch;
	this->_alive = true;
    
	this->setWindow(win);
    // Get terminal size
	getmaxyx(this->_curwin, this->_yMax, this->_xMax);
    setLocation(((this->_yMax - 5) / 2), 2);
    // Listen to keypad
	keypad(this->_curwin, true);
}

Snake::Snake(Snake const & src)
{
    *this = src;
    return;
}

Snake& Snake::operator=(Snake const & rhs)
{
    if (this != &rhs)
    {
		this->_currLocation[0] = rhs._currLocation[0];
		this->_currLocation[1] = rhs._currLocation[1];
        this->_xMax = rhs._xMax;
		this->_yMax = rhs._yMax;
		this->_character = rhs._character;
    }

    return *this;
}

Snake::~Snake(void)
{
    return;
}

void	Snake::displayObject(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], this->_character);
}

void	Snake::mvfwd(void)
{
	if (this->direction == DIR_UP){
		this->currLocation[1]--;  // move up screen
	}
	else if (this->direction == DIR_RIGHT){
		this->currLocation[0]++;
	}
	else if (this->direction == DIR_DOWN){
		this->currLocation[1]++;
	}
	else if (this->direction == DIR_LEFT){
		this->currLocation[0]--;
	}
}

void	Snake::turnLeft(void)
{
	if (this->_direction == 1)
	{
		this->direction = 4;
	}
	else
		this->direction--;
}

void	Snake::turnRight(void)
{
	if (this->_direction == 4)
	{
		this->direction = 0;
	}
	else
	this->direction++;
}