/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLoop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:51:13 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/08 17:02:01 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameLoop.hpp" // Add include path to Makefile

int     gameLoop(void)
{
    long            _oldNanoSec;
    time_t          _oldSec;
 //   int             _gameStartTime;     // timestamp program started
//    int             _sessionStartTime;  // timestamp when current game session started
    struct timespec _timeNow;           // Holds current time values

    int i = 0;
    while (i < 5)
    {
        clock_gettime(CLOCK_REALTIME, &_timeNow);
        if ((_timeNow.tv_nsec - _oldNanoSec) > 16666600)
        {
            _oldNanoSec = _timeNow.tv_nsec;
            // Get input

            // Update position and gamestate according to input (left, right, pause, exit, main menu)

            // Update display
        }
        if ((_timeNow.tv_sec - _oldSec) > 0)
        {
            _oldSec  = _timeNow.tv_sec;
            ++i;
            _oldNanoSec = 0;
            std::cout << "Secs elapsed : " << i << std::endl;
        }
    }
    return (0);
}

/*int    getTotalGameTime(void)
{
    clock_gettime(CLOCK_REALTIME, this->_timeNow);
    return (static_cast<int>(this->timeNow.tv_sec - this->_gameStartTime));
}

int    getCurrentSessionTime(void)
{
    clock_gettime(CLOCK_REALTIME, this->_timeNow);
    return (static_cast<int>(this->timeNow.tv_sec - this->_sessionStartTime));
}*/