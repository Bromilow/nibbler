/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 21:30:48 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/25 18:04:18 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Module.hpp"

Module::Module(GameEnvironment & data) : gameData(data),  _choice(-1)
{
	sigaction(SIGWINCH, NULL, &this->_oldSIGWINCH);
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
	this->_padX = 1;
	this->_padY = 1;

	// Game area
	this->_gameWindow = newwin(this->_terminal_H - INFO_WIN_H, this->_terminal_W, INFO_WIN_H, 0);
	nodelay(this->_gameWindow, true);
	keypad(this->_gameWindow, true);

	// Info bar
	this->_infoWindow = newwin(INFO_WIN_H, this->_terminal_W, 0, 0);
	nodelay(this->_infoWindow, true);

	wrefresh(this->_gameWindow);
	wrefresh(this->_infoWindow);
	refresh();
}

Module::~Module()
{
	delwin(this->_gameWindow);
	delwin(this->_infoWindow);
	endwin();
	sigaction(SIGWINCH, &this->_oldSIGWINCH, NULL);
}

Module::Module(const Module & src) : gameData(src.gameData)
{
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	this->_gameWindow = rhs._gameWindow;
	this->_infoWindow = rhs._infoWindow;
	this->_terminal_W = rhs._terminal_W;
	this->_terminal_H = rhs._terminal_H;
	this->_padX = rhs._padX;
	this->_padY = rhs._padY;
	this->_oldSIGWINCH = rhs._oldSIGWINCH;
	this->_choice = rhs._choice;

	return (*this);
}

t_input		Module::getInput(int accept)
{
    int	choice;

	choice = wgetch(this->_gameWindow);
	if (choice != -1 && this->_choice != choice)
		this->_choice = choice;
	if (accept == 1)
	{
		choice = this->_choice;
		this->_choice = -1;
		return (this->_handleInput(choice));
	}
	return (NONE);
}

t_input		Module::_handleInput(int choice)
{
	if (this->gameData.paused)
		switch(choice)
		{
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
			case KEY_UP:
			case KEY_DOWN:
			case KEY_LEFT:
			case KEY_RIGHT:
			case ' ':
			case 'a':
			case 'z':
			default:
				return NONE;
		}
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
		case 'a':
			return INCR_SPD;
		case 'z':
			return DECR_SPD;
		default:
			return NONE;
	}
}

int		Module::updateDisplay(void)
{
	unsigned int	newYMax;
	unsigned int	newXMax;

	// Get terminal size
	getmaxyx(stdscr, newYMax, newXMax);

	// Check game state
	if (newXMax <= this->gameData.mapWidth * 2 + 5 || newYMax <= this->gameData.mapHeight + 10)
		return (this->_screenTooSmall());
	if (newXMax != this->_terminal_W || newYMax != this->_terminal_H)
		this->_resizeWindow(newYMax, newXMax);
	if (this->gameData.paused)
		return (this->_gameIsPaused());
	
	// Prep screen for new output
	wclear(this->_infoWindow);
	wclear(this->_gameWindow);

	// Update info window
	this->_updateInfoWindow();
	
	// Update game window
	this->_updateGameWindow();

	// Draw borders
	box(this->_infoWindow, 0, 0);
	box(this->_gameWindow, 0, 0);

	// Update virtual screen
	wnoutrefresh(this->_infoWindow);
	wnoutrefresh(this->_gameWindow);

	// update physical screen
	doupdate();

	return (1);
}

int     Module::_screenTooSmall(void)
{
	wclear(stdscr);
	wclear(this->_infoWindow);    
	wclear(this->_gameWindow);
	mvwprintw(this->_gameWindow, 1, 1, "Terminal too small!");
	wrefresh(stdscr);
	wrefresh(this->_infoWindow);
	wrefresh(this->_gameWindow);
	return (0);
}

void    Module::_resizeWindow(unsigned int newYMax, unsigned int newXMax)
{
	// Resize and move infowin
	wresize(this->_infoWindow, INFO_WIN_H, newXMax);
	mvwin(this->_infoWindow, 0, 0);

	// Resize and move gamewin
	wresize(this->_gameWindow, newYMax - INFO_WIN_H, newXMax);
	mvwin(this->_gameWindow, newYMax - INFO_WIN_H , 0);

	// Update dimensions
	this->_terminal_W = newXMax;
	this->_terminal_H = newYMax;
}

int     Module::_gameIsPaused(void)
{
	wclear(stdscr);
	wclear(this->_infoWindow);    
	wclear(this->_gameWindow);
	mvwprintw(this->_gameWindow, this->_terminal_H / 2, this->_terminal_W / 2, "\\;---[ PAUSED ]---;/");
	wrefresh(stdscr);
	wrefresh(this->_infoWindow);
	wrefresh(this->_gameWindow);
	return(0);
}

void    Module::_updateInfoWindow(void)
{
	mvwprintw(this->_infoWindow, 1, 1, "Time\t\t: %d\n", this->gameData.gameTime);
	mvwprintw(this->_infoWindow, 2, 1, "Score\t\t: %d", this->gameData.snakeLength - 4);
	mvwprintw(this->_infoWindow, 3, 1, "gameFPS\t: %d", this->gameData.gameFPS);
}

void    Module::_updateGameWindow(void)
{
	unsigned int	y;
	unsigned int	x;

	for (y = 0; y < this->gameData.mapHeight; ++y)
	{
		x = 0;
		wmove(this->_gameWindow, y + this->_padY, x + this->_padX);
		for (; x < this->gameData.mapWidth; ++x)
		{
			switch (this->gameData.map[y][x])
			{
				case MAP_NONE:
					wprintw(this->_gameWindow, "  ");
					break;
				case MAP_WALL:
					wprintw(this->_gameWindow, "# ");
					break;
				case MAP_FOOD:
					wprintw(this->_gameWindow, "X ");
					break;
				case MAP_PLAYER:
					waddch(this->_gameWindow, ACS_DIAMOND);
					waddch(this->_gameWindow, ' ');
					break;
			}
			if (this->gameData.map[y][x] == this->gameData.snakeLength + 9)
				wprintw(this->_gameWindow, ". ");
			else if ((this->gameData.map[y][x] > MAP_PLAYER) &&
				(this->gameData.map[y][x] < this->gameData.snakeLength + 9))
			{
				wprintw(this->_gameWindow, "o ");
			}
		}
		wprintw(this->_gameWindow, "\n");
	}
}

// Class factories
IModule*	create_module(GameEnvironment & data) 
{
	return new Module(data);
}

void		destroy_module(IModule* module)
{
	delete module;
}