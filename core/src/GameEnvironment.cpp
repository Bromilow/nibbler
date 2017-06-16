/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 14:25:39 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/16 16:29:05 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include "GameEnvironment.hpp"
#include "ModuleController.hpp"

GameEnvironment::GameEnvironment(void)
{
    //std::cout << "GameEnvironment::Default constructor" << std::endl; //debug
}

GameEnvironment::GameEnvironment(const unsigned int w, const unsigned int h, const char *filename) : gameFPS(DEFAULT_GAME_FPS)
{
    // Set gameSpeed. Round to nearest 100th
    this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;

    //std::cout << "GameEnvironment::Parameterized constructor" << std::endl; //debug
    this->player = NULL;
    this->levelData = new Level(w, h);
    
    this->moduleController = new ModuleController(filename, *(this->levelData));
    this->moduleController->loadLibrary(filename);
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
        /*this->width = rhs.width;
        this->height = rhs.height;*/
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
    int             i;
 //   int             _gameStartTime;     // timestamp program started
//    int             _sessionStartTime;  // timestamp when current game session started
    struct timespec _timeNow;           // Holds current time values

    clock_gettime(CLOCK_REALTIME, &_timeNow);
    _oldNanoSec = _timeNow.tv_nsec;
    _oldSec  = _timeNow.tv_sec;
    i = 0;
    while (i < 8)
    {
        clock_gettime(CLOCK_REALTIME, &_timeNow);
        if ((_timeNow.tv_nsec - _oldNanoSec) > 16666600 /*this->gameSpeed*/) // 16666600 * 60 == 1 sec 
        {
            _oldNanoSec = _timeNow.tv_nsec;

            // Get input
            this->moduleController->module->getInput();

            // Update position and gamestate according to input (left, right, pause, exit, main menu)

            // Update display
            this->moduleController->module->updateDisplay();
        }
        if ((_timeNow.tv_sec - _oldSec) > 0)
        {
            ++i;
            _oldSec  = _timeNow.tv_sec;
            _oldNanoSec = 0;
        }
    }
    return (0);
}