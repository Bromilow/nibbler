/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 14:25:39 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:18:11 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include "ModuleController.hpp"

Core::Core(const unsigned int w, const unsigned int h, const int lib)
{
    // Change signal handling
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
    *this = src;
}

Core & Core::operator=(Core const & rhs)
{
    if (this != &rhs)
    {
        this->gameData = rhs.gameData;
        this->moduleController = rhs.moduleController;
        for (int i = 0; i < N_MODULES; ++i)
            this->modulePaths[i] = rhs.modulePaths[i];
    }
    return (*this);
}

Core::~Core(void)
{
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
    int             diff;

    current_utc_time(&timeNow);
    _oldNanoSec = timeNow.tv_nsec;
    _oldSec  = timeNow.tv_sec;
    diff = 0;
    while (this->gameData->snakeAlive)
    {
        current_utc_time(&timeNow);
        if ((timeNow.tv_sec - _oldSec) > 0)
        {
            if (!this->gameData->paused)
                ++this->gameData->gameTime;
            _oldSec  = timeNow.tv_sec;
            diff = ONE_NANOSEC - _oldNanoSec;
            _oldNanoSec = 0;
        }
        if ((diff + timeNow.tv_nsec - _oldNanoSec) >= this->gameData->gameSpeed)
        {
            _oldNanoSec = timeNow.tv_nsec;
            diff = 0;

            if (!handleAction(this->moduleController->module->getInput(1)))
                return (0);

            if (!this->gameData->paused)
                this->gameData->updateMapData();
                
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

int     Core::handleAction(t_input action)
{
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
    return (1);
}

void    Core::current_utc_time(struct timespec *ts) {

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;

  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif

}

void	_shutdown(int signal, siginfo_t *info, void *data)
{
    (void)signal;
    (void)info;
    (void)data;
    exit(EXIT_FAILURE);
}