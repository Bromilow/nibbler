/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:41:59 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/24 13:53:25 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_HPP
# define MODULE_HPP

# include <curses.h>
# include <iostream>
# include <signal.h>
# include "IModule.hpp"

# define INFO_WIN_H 5

class Module : public IModule
{
    public:
        Module(GameEnvironment & data);
        ~Module();
        Module(const Module & src);
        Module & operator=(const Module & rhs);
        
        virtual t_input getInput(int accept);
        virtual int     updateDisplay(void);

        GameEnvironment & gameData;

    private:
        WINDOW              *_gameWindow;
        WINDOW              *_infoWindow;
        unsigned int        _terminal_W;
        unsigned int        _terminal_H;
        unsigned int        _padX;
        unsigned int        _padY;
        struct sigaction    _oldSIGWINCH;
        int                 _choice;

        t_input _handleInput(int choice);
        int     _screenTooSmall(void);
        void    _resizeWindow(unsigned int newYMax, unsigned int newXmax);
        int     _gameIsPaused(void);
        void    _updateInfoWindow(void);
        void    _updateGameWindow(void);
};

extern "C" IModule* create_module(GameEnvironment & data);
extern "C" void     destroy_module(IModule* module);

#endif /* MODULE_HPP */