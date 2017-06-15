/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:41:48 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 14:31:17 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Module.hpp"

Module::Module(Level & data) : levelData(data)
{
	//std::cout << "Module::Default constructor" << std::endl; //debug
	this->_terminal_H = 0;
	this->_terminal_W = 0;

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
	this->_padX =(this->_terminal_W - this->levelData.mapWidth) / 2;
	this->_padY =(this->_terminal_H - this->levelData.mapHeight) / 2;

	// Game area
	this->_gameWindow = newwin(this->_terminal_H - 2, this->_terminal_W, 0, 0);
	box(this->_gameWindow, 0, 0);
	nodelay(this->_gameWindow, true);
	keypad(this->_gameWindow, true);
	idlok(this->_gameWindow, true);
	scrollok(this->_gameWindow, true);

	// Info bar
	this->_infoWindow = newwin(2, this->_terminal_W, this->_terminal_H - 2, 0);
	box(this->_infoWindow, 0, 0);
	nodelay(this->_infoWindow, true);

	wrefresh(this->_gameWindow);
	wrefresh(this->_infoWindow);
	// Refresh stdscr
	refresh();
}

Module::~Module()
{
	//std::cout << "Module::Destructor" << std::endl; //debug
	delwin(this->_gameWindow);
	delwin(this->_infoWindow);
	endwin();
}

Module::Module(const Module & src) : levelData(src.levelData)
{
	//std::cout << "Module::Copy constructor" << std::endl; //debug
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	//std::cout << "Module::Assignation Operator" << std::endl; //debug
	this->_gameWindow = rhs._gameWindow;
	this->_infoWindow = rhs._infoWindow;
	this->_terminal_W = rhs._terminal_W;
	this->_terminal_H = rhs._terminal_H;

	return (*this);
}

// Member functions
int     Module::getInput(void)
{
	//std::cout << "Module::getInput()" << std::endl; //debug
    int	choice = wgetch(this->_gameWindow);

	switch(choice)
	{
		case KEY_UP:
			//std::cout << "KEY_UP" << std::endl;
			wprintw(this->_infoWindow, "hello??");
			break;
		case KEY_DOWN:
			//std::cout << "KEY_DOWN" << std::endl;
			break;
		case KEY_LEFT:
			//std::cout << "KEY_LEFT" << std::endl;
			break;
		case KEY_RIGHT:
			//std::cout << "KEY_RIGHT" << std::endl;
			break;
		default:
			//std::cout << "KEY : " << choice << " : " << static_cast<char>(choice) << std::endl;
			break;
	}
	return (choice);
}

int		Module::updateDisplay(void)
{
	/*static unsigned int n = 0;*/
	unsigned int 		x;
	unsigned int 		y;

	wclear(this->_gameWindow);
	wclear(this->_infoWindow);

	for (y = 0; y < this->levelData.mapHeight; ++y)
	{
		x = 0;
		wmove(this->_gameWindow, y + this->_padY, x + this->_padX);
		for (; x < this->levelData.mapWidth; ++x)
		{
			switch (this->levelData.map[y][x])
			{
				case MAP_NONE:
					wprintw(this->_gameWindow, " ");
					break;
				case MAP_WALL:
					wprintw(this->_gameWindow, "#");
					break;
				case MAP_FOOD:
					wprintw(this->_gameWindow, "X");
					break;
				case MAP_PLAYER:
					wprintw(this->_gameWindow, "O");
					break;
			}
			
		}
		wprintw(this->_gameWindow, "\n");
	}

	box(this->_gameWindow, 0, 0);
	box(this->_infoWindow, 0, 0);

	// Update virtual screen
	wnoutrefresh(this->_gameWindow);
	wnoutrefresh(this->_infoWindow);

	// Update physical screen
	doupdate();

	return (1);
}

// Class factories
// Need to add type def for class factories --- http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html#AEN216
IModule*	create_module(Level & data) 
{
	//std::cout << "Module::Class Factory::create_module()" << std::endl; //debug
	/*(void)data;*/
	return new Module(data);
}

void		destroy_module(IModule* module)
{
	//std::cout << "Module::Class Factory::delete_module()" << std::endl; //debug
	delete module;
	std::cout << "Module::Class Factory::delete_module()::MODULE DELETED" << std::endl; //debug

}