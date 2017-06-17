/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEnvironment.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 14:25:39 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/16 23:54:08 by kbam7            ###   ########.fr       */
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

GameEnvironment::GameEnvironment(const unsigned int w, const unsigned int h, const int lib) : gameFPS(DEFAULT_GAME_FPS)
{
    const char *tmp[N_MODULES] = {"./module_1/lib1_NCurses.so", "./module_2/lib2_OpenGL.so", "./module_3/lib3_SDL.so"};
    for (int i = 0; i < N_MODULES; ++i)
        this->modulePaths[i] = tmp[i];

    // Set gameSpeed. Round to nearest 100th (16666600 by default)
    this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;

    //std::cout << "GameEnvironment::Parameterized constructor" << std::endl; //debug
    this->player = NULL;
    this->levelData = new Level(w, h);

    this->moduleController = new ModuleController(*(this->levelData));
    this->moduleController->loadLibrary(this->modulePaths[lib]);
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
    if (this->moduleController != NULL)
        delete this->moduleController;
    if (this->levelData != NULL)
        delete this->levelData;
    if (this->player != NULL)
        delete this->player;
}

int     GameEnvironment::gameLoop(void)
{
    long            _oldNanoSec;
    time_t          _oldSec;
    int             i;
    struct timespec timeNow;
    t_input         action;

    clock_gettime(CLOCK_REALTIME, &timeNow);
    _oldNanoSec = timeNow.tv_nsec;
    _oldSec  = timeNow.tv_sec;
    i = 0;
    while (i < 8)
    {
        clock_gettime(CLOCK_REALTIME, &timeNow);
        if ((timeNow.tv_nsec - _oldNanoSec) > 16666600 /*this->gameSpeed*/) // 16666600 * 60 == 1 sec 
        {
            _oldNanoSec = timeNow.tv_nsec;

            // Get input
            action = this->moduleController->module->getInput();
            switch (action)
            {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    this->levelData->changeSnakeDir(action);
                case QUIT:
                    return (0);
                case PAUSE:
                    this->levelData->paused = true;
                case MOD1:
                    this->loadNewModule(this->modulePaths[0]);
                case MOD2
                    // load new module
                    this->loadNewModule(this->modulePaths[1]);
                case MOD3
                    // load new module
                    this->loadNewModule(this->modulePaths[2]);
                case SUPACHOMP
                    // do stuff
                    this->player->supachomp = true;
            }

            // Update position and gamestate according to input (left, right, pause, exit, main menu)
            this->levelData->updateMapData();
           if (!(this->levelData->moveToNextBlock()))
                this->levelData->gameOver();

            // Update display
            this->moduleController->module->updateDisplay();
        }
        if ((timeNow.tv_sec - _oldSec) > 0)
        {
            ++i;
            _oldSec  = timeNow.tv_sec;
            _oldNanoSec = 0;
        }
    }
    return (0);
}