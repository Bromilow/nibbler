/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 14:25:39 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 20:27:49 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameEnvironment.hpp"

GameEnvironment::GameEnvironment(void) : width(0), height(0)
{
    //std::cout << "GameEnvironment::Default constructor" << std::endl; //debug
}

GameEnvironment::GameEnvironment(const int w, const int h, const char *filename) : width(w), height(h)
{
    //std::cout << "GameEnvironment::Parameterized constructor" << std::endl; //debug
    this->player = NULL;
    this->levelData = NULL;
    this->moduleController = new ModuleController(filename);
}

GameEnvironment::GameEnvironment(GameEnvironment const & src)
{
    //std::cout << "GameEnvironment::Copy constructor" << std::endl;  //debug
    *this = src;
}

GameEnvironment & GameEnvironment::operator=(GameEnvironment const & rhs)
{
    //std::cout << "GameEnvironment::Assignation operator" << std::endl;  //debug
    if (this != &rhs)
    {
        this->player = rhs.player;
        this->levelData = rhs.levelData;
        this->moduleController = rhs.moduleController;
        this->width = rhs.width;
        this->height = rhs.height;
    }
    return (*this);
}

GameEnvironment::~GameEnvironment(void)
{
    //std::cout << "GameEnvironment::Destructor" << std::endl;  //debug
    if (this->player != NULL)
        delete this->player;
    if (this->levelData != NULL)
        delete this->levelData;
    if (this->moduleController != NULL)
        delete this->moduleController;
}

int     GameEnvironment::gameLoop(void)
{
    //std::cout << "GameEnvironment::gameLoop()" << std::endl;  //debug
    long            _oldNanoSec;
    time_t          _oldSec;
 //   int             _gameStartTime;     // timestamp program started
//    int             _sessionStartTime;  // timestamp when current game session started
    struct timespec _timeNow;           // Holds current time values

    int i = 0;
    while (i < 5)
    {
        clock_gettime(CLOCK_REALTIME, &_timeNow);
        if ((_timeNow.tv_nsec - _oldNanoSec) > 6666600) // 16666600 / 2.8
        {
            //std::cout << "GameEnvironment::gameLoop()::input time frame" << std::endl; //debug
            // Get input
            this->moduleController->module->getInput();
        }
        if ((_timeNow.tv_nsec - _oldNanoSec) > 749997000) // 16666600 * 45 
        {
            //std::cout << "GameEnvironment::gameLoop()::update display : 60FPS" << std::endl; //debug
            _oldNanoSec = _timeNow.tv_nsec;

            // Update position and gamestate according to input (left, right, pause, exit, main menu)

            // Update display
            this->moduleController->module->updateDisplay();
        }
        if ((_timeNow.tv_sec - _oldSec) > 0)
        {
            //std::cout << "GameEnvironment::gameLoop()::seconds" << std::endl; //debug
            _oldSec  = _timeNow.tv_sec;
            ++i;
            _oldNanoSec = 0;
            //std::cout << "Secs elapsed : " << i << std::endl; //debug
        }
    }
    return (0);
}