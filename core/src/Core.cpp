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

Core::Core(const unsigned int w, const unsigned int h, const int lib) : gameFPS(2/*DEFAULT_GAME_FPS*/)
{
    // Change signal signal handling
    sigaction(SIGINT, this->_shutdown, this->_oldSIGINT);
    sigaction(SIGQUIT, this->_shutdown, this->_oldSIGQUIT);
    sigaction(SIGSEGV, this->_shutdown, this->_oldSIGSEGV);

    // Setup module paths
    const char *tmp[N_MODULES] = {"./module_1/lib1_NCurses.so", "./module_2/lib2_OpenGL.so", "./module_3/lib3_SDL.so"};
    for (int i = 0; i < N_MODULES; ++i)
        this->modulePaths[i] = tmp[i];

    // Set gameSpeed. Round to nearest 100th (16666600 by default)
    this->gameSpeed = ((ONE_NANOSEC / this->gameFPS) / 100) * 100;

    //std::cout << "Core::Parameterized constructor" << std::endl; //debug
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
}

int     Core::gameLoop(void)
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
    while (i < 120 && this->gameData->snakeAlive)
    {
        clock_gettime(CLOCK_REALTIME, &timeNow);
        // Clear input stream
        this->moduleController->module->getInput(false);
        if ((timeNow.tv_nsec - _oldNanoSec) > this->gameSpeed) // 16666600 * 60 == 1 sec 
        {
            _oldNanoSec = timeNow.tv_nsec;

            action = this->moduleController->module->getInput(true);
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

            // Update position and gamestate according to input (left, right, pause, exit, main menu)
            this->gameData->updateMapData();
           /*if (!(this->gameData->moveToNextBlock()))
                this->gameData->gameOver();*/

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

void	Core::loadNewModule(const char *libPath)
{
    if (this->moduleController != NULL)
        delete this->moduleController;
    this->moduleController = new ModuleController(*(this->gameData));
    this->moduleController->loadLibrary(libPath);
}


void	_shutdown(int signal, siginfo_t *info, void *data)
{
    static unsigned int n = 0;

    (void)signal;
    (void)info;
    (void)data;
    ++n;
    if (n < 3) {
        if (this->moduleController != NULL)
            delete this->moduleController;
        if (this->gameData != NULL)
            delete this->gameData;
    } else {
        sigaction(SIGINT, this->_oldSIGINT, NULL);
        sigaction(SIGQUIT, this->_oldSIGQUIT, NULL);
        tsigaction(SIGSEGV, this->_oldSIGSEGV, NULL);
    }
}