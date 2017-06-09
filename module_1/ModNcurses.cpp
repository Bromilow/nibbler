/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModNcurses.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:41:48 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 03:02:26 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModNcurses.hpp"

ModNcurses::ModNCurses()
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);
	
	// Refresh and clear stdscr
	clear();
	refresh();

	// Get max X and Y
	getmaxyx(stdscr, this->_terminal_H, this->_terminal_W);

	// Game area
	this->_gameWindow = newwin((this->_terminal_H - 5), this->_terminal_W, 0, 0);
	box(this->_gameWindow, 0, 0);

	// Info bar
	this->_infoWindow = newwin(5, this->_terminal_W, (this->_terminal_H - 5), 0);
	box(this->_infoWindow, 0, 0);

	// Refresh stdscr
	refresh();
}

ModNcurses::~ModNCurses()
{
	delwin(this->_gameWindow);
	delwin(this->_infoWindow);
}

ModNcurses::ModNCurses(const ModNCurses & src)
{
	*this = src;
}

ModNCurses & ModNcurses::operator=(const ModNCurses & rhs)
{
	this->_gameWindow = rhs._gameWindow;
	this->_infoWindow = rhs._infoWindow;

	return (*this);
}

// Class factories
// Need to add type def for class factories --- http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html#AEN216
extern "C" IModule* create_module()
{
    return new ModNCurses;
}

extern "C" void destroy_module(IModule* p)
{
    delete p;
}

// Member functions
int     ModNcurses::getInput(void)
{
    int	choice = wgetch(this->_gameWindow);

	switch(choice)
	{
		case KEY_UP:
			std::cout << "KEY_UP" << std::endl;
			break;
		case KEY_DOWN:
			std::cout << "KEY_DOWN" << std::endl;
			break;
		case KEY_LEFT:
			std::cout << "KEY_LEFT" << std::endl;
			break;
		case KEY_RIGHT:
			std::cout << "KEY_RIGHT" << std::endl;
			break;
		default:
			std::cout << "KEY : " << choice << " : " << static_cast<char>(choice) << std::endl;
			break;
	}
	return (choice);
}

int		ModNcurses::updateDisplay(void)
{
	std::cout << "ModNcurses::updateDisplay()" << std::endl;
	return (1);
}