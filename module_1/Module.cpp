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

Module::Module(GameEnvironment & data) : gameData(data)
{
	this->_oldSIGWINCH = signal(SIGWINCH, NULL);
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

	// Get padding to center map in terminal
	this->_padX = (this->_terminal_W - this->gameData.mapWidth) / 2;
	this->_padY = (this->_terminal_H - this->gameData.mapHeight) / 2;

	// Game area
	this->_gameWindow = newwin(this->_terminal_H - INFO_WIN_H, this->_terminal_W, 0, 0);
	/*box(this->_gameWindow, 0, 0);*/
	nodelay(this->_gameWindow, true);
	keypad(this->_gameWindow, true);

	// Scrolling in window
	/*idlok(this->_gameWindow, true);
	scrollok(this->_gameWindow, true);*/

	// Info bar
	this->_infoWindow = newwin(INFO_WIN_H, this->_terminal_W, this->_terminal_H - INFO_WIN_H, 0);
	/*box(this->_infoWindow, 0, 0);*/
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
	signal(SIGWINCH, this->_oldSIGWINCH);
}

Module::Module(const Module & src) : gameData(src.gameData)
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
t_input		Module::getInput(const bool accept)
{
	//std::cout << "Module::getInput()" << std::endl; //debug
    int	choice;

	if (!accept)
		getch();
	else {
		choice = wgetch(this->_gameWindow);
		switch(choice)
		{
			case KEY_UP:
				return UP;
			case KEY_DOWN:
				return DOWN;
			case KEY_LEFT:
				return LEFT;
			case KEY_RIGHT:
				return RIGHT;
			case 27:
			case 'q':
				return QUIT;
			case 'p':
				return PAUSE;
			case '1':
				return MOD1;
			case '2':
				return MOD2;
			case '3':
				return MOD3;
			case ' ':
				return SUPACHOMP;
			default:
				return NONE;
		}
	}
	return (NONE);
}

int		Module::updateDisplay(void)
{
	/*static unsigned int n = 0;*/
	unsigned int 		x, y, newYMax, newXMax;

	// Get terminal size
	getmaxyx(stdscr, newYMax, newXMax);
	if (newXMax <= this->gameData.mapWidth + 5 || newYMax <= this->gameData.mapHeight + 10)
	{
		wclear(stdscr);
		wclear(this->_gameWindow);
		wclear(this->_infoWindow);    
		mvwprintw(this->_gameWindow, 1, 1, "Terminal too small!");
		wrefresh(stdscr);
		wrefresh(this->_gameWindow);
		wrefresh(this->_infoWindow);
		return (1);
	}
	else if (newXMax <= this->gameData.paused)
	{
		wclear(stdscr);
		wclear(this->_gameWindow);
		wclear(this->_infoWindow);    
		mvwprintw(this->_gameWindow, 1, 1, "\\;---[ PAUSED ]---;/");
		wrefresh(stdscr);
		wrefresh(this->_gameWindow);
		wrefresh(this->_infoWindow);
		return (1);
	}
	else if (newXMax != this->_terminal_W || newYMax != this->_terminal_H)
	{
		// Resize and move gamewin
		wresize(this->_gameWindow, newYMax - INFO_WIN_H, newXMax);
		mvwin(this->_gameWindow, 0, 0);

		// Resize and move infowin
		wresize(this->_infoWindow, INFO_WIN_H, newXMax);
		mvwin(this->_infoWindow, newYMax - INFO_WIN_H, 0);

		// Update padding
		this->_padX = (newXMax - this->gameData.mapWidth) / 2;
		this->_padY = (newYMax - this->gameData.mapHeight) / 2;

		// Update dimensions
		this->_terminal_W = newXMax;
		this->_terminal_H = newYMax;
	}

	wclear(this->_gameWindow);
	wclear(this->_infoWindow);

	for (y = 0; y < this->gameData.mapHeight; ++y)
	{
		x = 0;
		wmove(this->_gameWindow, y + this->_padY, x + this->_padX);
		for (; x < this->gameData.mapWidth; ++x)
		{
			switch (this->gameData.map[y][x])
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
					waddch(this->_gameWindow, ACS_DIAMOND);
					break;
			}
			if (this->gameData.map[y][x] == this->gameData.snakeLength + 9)
			{
				// its the tail
				wprintw(this->_gameWindow, ".");
				/*if (this->gameData.snakeDirection % 2)
					wprintw(this->_gameWindow, "|");
				else
					wprintw(this->_gameWindow, "-");*/
			}
			else if ((this->gameData.map[y][x] > MAP_PLAYER) &&
				(this->gameData.map[y][x] < this->gameData.snakeLength + 9))
			{
				// its the body
				wprintw(this->_gameWindow, "o");
			}
		}
		wprintw(this->_gameWindow, "\n");
	}

	box(this->_gameWindow, 0, 0);
	box(this->_infoWindow, 0, 0);

	// Update virtual screen
	wnoutrefresh(this->_gameWindow);
	wnoutrefresh(this->_infoWindow);

	// update physical screen
	doupdate();

	return (1);
}

// Class factories
// Need to add type def for class factories --- http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html#AEN216
IModule*	create_module(GameEnvironment & data) 
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