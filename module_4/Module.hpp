/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:41:59 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/11 16:26:56 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_HPP
# define MODULE_HPP

# include <SDL.h>
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

        SDL_Window          *_gameWindow;
        SDL_Renderer        *_renderer;

        unsigned int        _window_W;
        unsigned int        _window_H;
        unsigned int        _padX;
        unsigned int        _padY;
        unsigned int        _choice;
        SDL_Surface*        _field_surface;
        SDL_Surface*        _fruit_surface;
        SDL_Surface*        _shead_surface;
        SDL_Surface*        _snake_surface;
        SDL_Texture*        _field_texture;
        SDL_Texture*        _fruit_texture;
        SDL_Texture*        _shead_texture;
        SDL_Texture*        _snake_texture;

        t_input _handleInput(unsigned int choice);
        int     _gameIsPaused(void);
        void    _updateGameWindow(void);
        
};

extern "C" IModule* create_module(GameEnvironment & data);
extern "C" void     destroy_module(IModule* module);

#endif /* MODULE_HPP */