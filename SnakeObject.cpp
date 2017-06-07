/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeObject.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:40:15 by kbamping          #+#    #+#             */
/*   Updated: 2017/05/28 10:02:52 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeObject.hpp"

SnakeObject::SnakeObject(void)
{
    return;
}

SnakeObject::SnakeObject(WINDOW * win, char ch)
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

SnakeObject::SnakeObject(SnakeObject const & src)
{
    *this = src;
    return;
}

SnakeObject& SnakeObject::operator=(SnakeObject const & rhs)
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

SnakeObject::~SnakeObject(void)
{
    return;
}

/*// refactoring
void	SnakeObject::mvfwd(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], ' ');
	this->_currLocation[1]--;
	if (this->_currLocation[1] < 1)
		this->_currLocation[1] = this->_yMax - 2;
}

/*void	SnakeObject::mvdown(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], ' ');
	this->_currLocation[1]++;
	if (this->_currLocation[1] > this->_yMax - 2)
		this->_currLocation[1] = 1;
}

void	SnakeObject::turnLeft(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], ' ');
	this->_currLocation[0]--;
	this->_currLocation[0]--;
	if (this->_currLocation[0] < 1)
		this->_currLocation[0] = 1;
}

void	SnakeObject::turnRight(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], ' ');
    
	this->_currLocation[0]++;
	this->_currLocation[0]++;
	if (this->_currLocation[0] > this->_xMax - 2)
		this->_currLocation[0] = this->_xMax - 2;
}


int SnakeObject::getInput(void)
{
	int	choice = wgetch(this->_curwin);
	switch(choice)
	{
		case KEY_UP:
			mvup();
			break;
		case KEY_DOWN:
			mvdown();
			break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		default:
			break;
	}
	return (choice);
}
/*/

void	SnakeObject::displaySnakeObject(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], this->_character);
}

int		SnakeObject::getLocation(char c) const
{
	if (c == 'x')
    	return (this->_currLocation[0]);
	else if (c == 'y')
    	return (this->_currLocation[1]);
	else
		return (-1);
}

void    SnakeObject::setLocation(int xLoc, int yLoc)
{
	if (xLoc == -1)
    	xLoc = this->_currLocation[0];
	if (yLoc == -1)
		yLoc = this->_currLocation[1];

	this->_currLocation[0] = xLoc;	
    this->_currLocation[1] = yLoc;
}

int     SnakeObject::getMax(char c) const
{
    return ((c == 'x' ? this->_xMax : (c == 'y') ? this->_yMax : -1));
}

void    SnakeObject::setMax(char c, int val)
{
    if (c == 'x')
        this->_xMax = val;
    else if (c == 'y')
        this->_yMax = val;
}

WINDOW  *SnakeObject::getWindow() const
{
    return (this->_curwin);
}

void    SnakeObject::setWindow(WINDOW *win)
{
    this->_curwin = win;
}

/*bool	SnakeObject::isAlive(void) const
{
	return ((this->_alive ? true : false));
}

void	SnakeObject::setAlive(bool val)
{
	this->_alive = val;
}*/

char    SnakeObject::getCharacter(void) const
{
	return (this->_character);
}

void    SnakeObject::setCharacter(char c)
{
	if (c > '\0')
		this->_character = c;
}

void	SnakeObject::mvfwd(void)
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

void	SnakeObject::turnLeft(void)
{
	if (this->_direction == 1)
	{
		this->direction = 4;
	}
	else
		this->direction--;
}

void	SnakeObject::turnRight(void)
{
	if (this->_direction == 4)
	{
		this->direction = 0;
	}
	else
	this->direction++;
}


