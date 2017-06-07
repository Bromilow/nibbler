/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:40:15 by kbamping          #+#    #+#             */
/*   Updated: 2017/05/28 10:02:52 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::Base(void)
{
    return;
}

Base::Base(WINDOW * win, char ch)
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

Base::Base(Base const & src)
{
    *this = src;
    return;
}

Base& Base::operator=(Base const & rhs)
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

Base::~Base(void)
{
    return;
}

void	Base::displayObject(void)
{
	mvwaddch(this->_curwin, this->_currLocation[1], this->_currLocation[0], this->_character);
}

int		Base::getLocation(char c) const
{
	if (c == 'x')
    	return (this->_currLocation[0]);
	else if (c == 'y')
    	return (this->_currLocation[1]);
	else
		return (-1);
}

void    Base::setLocation(int xLoc, int yLoc)
{
	if (xLoc == -1)
    	xLoc = this->_currLocation[0];
	if (yLoc == -1)
		yLoc = this->_currLocation[1];

	this->_currLocation[0] = xLoc;	
    this->_currLocation[1] = yLoc;
}

int     Base::getMax(char c) const
{
    return ((c == 'x' ? this->_xMax : (c == 'y') ? this->_yMax : -1));
}

void    Base::setMax(char c, int val)
{
    if (c == 'x')
        this->_xMax = val;
    else if (c == 'y')
        this->_yMax = val;
}

WINDOW  *Base::getWindow() const
{
    return (this->_curwin);
}

void    Base::setWindow(WINDOW *win)
{
    this->_curwin = win;
}

char    Base::getCharacter(void) const
{
	return (this->_character);
}

void    Base::setCharacter(char c)
{
	if (c > '\0')
		this->_character = c;
}