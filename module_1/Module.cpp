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

Module::Module()
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

	// Game area
	this->_gameWindow = newwin(5, this->_terminal_W, 10, 0);
	box(this->_gameWindow, 0, 0);
	nodelay(this->_gameWindow, true);
	keypad(this->_gameWindow, TRUE);

	// Info bar
	this->_infoWindow = newwin(5, this->_terminal_W, 0, 0);
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

Module::Module(const Module & src)
{
	//std::cout << "Module::Copy constructor" << std::endl; //debug
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	//std::cout << "Module::Assignation Operator" << std::endl; //debug
	this->_gameWindow = rhs._gameWindow;
	this->_infoWindow = rhs._infoWindow;

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
			printw("hello??");
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
	//std::cout << "Module::updateDisplay()" << std::endl; //debug
	wprintw(this->_gameWindow, "hello???");
	wprintw(this->_infoWindow, "hello???");

	wrefresh(this->_gameWindow);
	wrefresh(this->_infoWindow);

	return (1);
}

// Class factories
// Need to add type def for class factories --- http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html#AEN216
IModule*	create_module(void) 
{
	//std::cout << "Module::Class Factory::create_module()" << std::endl; //debug
	return new Module();
}

void		destroy_module(IModule* module)
{
	//std::cout << "Module::Class Factory::delete_module()" << std::endl; //debug
	delete module;
	std::cout << "Module::Class Factory::delete_module()::MODULE DELETED" << std::endl; //debug

}