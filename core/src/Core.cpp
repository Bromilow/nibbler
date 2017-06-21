/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 14:25:39 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/17 17:29:16 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include "Core.hpp"
#include "ModuleController.hpp"

Core::Core(void)
{
    //std::cout << "Core::Default constructor" << std::endl; //debug
}

Core::Core(const unsigned int w, const unsigned int h, const int lib)
{
    // Change signal signal handling
    struct sigaction    newAct;

    newAct.sa_sigaction = &_shutdown;
    newAct.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &newAct, &this->_oldSIGINT);
    sigaction(SIGQUIT, &newAct, &this->_oldSIGQUIT);
    sigaction(SIGSEGV, &newAct, &this->_oldSIGSEGV);

    // Setup module paths
    const char *tmp[N_MODULES] = {"./module_1/lib1_NCurses.so", "./module_2/lib2_NCurses.so", "./module_3/lib3_NCurses.so"};
    for (int i = 0; i < N_MODULES; ++i)
        this->modulePaths[i] = tmp[i];

    this->gameData = new GameEnvironment(w, h);

    this->moduleController = new ModuleController(*(this->gameData));
    this->moduleController->loadLibrary(this->modulePaths[lib]);
}

Core::Core(Core const & src)
{
    //std::cout << "Core::Copy constructor" << std::endl;  //debug
    *this = src;
}

Core & Core::operator=(Core const & rhs)
{
    //std::cout << "Core::Assignation operator" << std::endl;  //debug
    if (this != &rhs)
    {
        this->gameData = rhs.gameData;
        this->moduleController = rhs.moduleController;
        /*this->width = rhs.width;
        this->height = rhs.height;*/
    }
    return (*this);
}

Core::~Core(void)
{
    //std::cout << "Core::Destructor" << std::endl;  //debug
    if (this->moduleController != NULL)
        delete this->moduleController;
    if (this->gameData != NULL)
        delete this->gameData;

    sigaction(SIGINT, &this->_oldSIGINT, NULL);
    sigaction(SIGQUIT, &this->_oldSIGQUIT, NULL);
    sigaction(SIGSEGV, &this->_oldSIGSEGV, NULL);
}

int     Core::gameLoop(void)
{
    long            _oldNanoSec;
    time_t          _oldSec;
    struct timespec timeNow;
    t_input         action;
    int             diff;

    clock_gettime(CLOCK_REALTIME, &timeNow);
    _oldNanoSec = timeNow.tv_nsec;
    _oldSec  = timeNow.tv_sec;
    diff = 0;
    while (this->gameData->snakeAlive)
    {
        clock_gettime(CLOCK_REALTIME, &timeNow);
        if ((timeNow.tv_sec - _oldSec) > 0)
        {
            if (!this->gameData->paused)
                ++this->gameData->gameTime;
            _oldSec  = timeNow.tv_sec;
            diff = ONE_NANOSEC - _oldNanoSec;
            _oldNanoSec = 0;
        }
        if ((diff + timeNow.tv_nsec - _oldNanoSec) >= this->gameData->gameSpeed) // 1 sec / FPS 
        {
            _oldNanoSec = timeNow.tv_nsec;
            diff = 0;

            action = this->moduleController->module->getInput(1);
            switch (action)
            {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    this->gameData->changeSnakeDir(action);
                    break;
                case QUIT:
                    return (0);
                case PAUSE:
                    this->gameData->paused = !this->gameData->paused;
                    break;
                case MOD1:
                    this->loadNewModule(this->modulePaths[0]);
                    break;
                case MOD2:
                    // load new module
                    this->loadNewModule(this->modulePaths[1]);
                    break;
                case MOD3:
                    // load new module
                    this->loadNewModule(this->modulePaths[2]);
                    break;
                case SUPACHOMP:
                    // do stuff
                    this->gameData->supachomp = true;
                    break;
                case NONE:
                    break;
            }

            if (!this->gameData->paused)
            {
                // Update position and gamestate according to input (left, right, pause, exit, main menu)
                this->gameData->updateMapData();
            }
            // Update display
            if (!this->moduleController->module->updateDisplay())
                this->gameData->paused = true;
        }
        // Read input, but dont accept it yet
        this->moduleController->module->getInput(0);
    }
    return (0);
}

void	Core::loadNewModule(const char *libPath)
{
    if (this->moduleController != NULL)
        delete this->moduleController;
    this->moduleController = new ModuleController(*(this->gameData));
    this->moduleController->loadLibrary(libPath);
}


void	_shutdown(int signal, siginfo_t *info, void *data)
{
    (void)signal;
    (void)info;
    (void)data;
    exit(EXIT_FAILURE);
}