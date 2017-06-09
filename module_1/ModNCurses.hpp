/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModNCurses.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:41:59 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 14:31:29 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_NCURSES_HPP
# define MOD_NCURSES_HPP

# include <curses.h>
# include <iostream>
# include "IModule/IModule.hpp"

class ModNCurses : public IModule
{
    public:
        ModNCurses();
        ~ModNCurses();
        ModNCurses(const ModNCurses & src);
        ModNCurses & operator=(const ModNCurses & rhs);
        
        virtual int getInput(void);
        virtual int updateDisplay(void);
    private:
        WINDOW *_gameWindow;
        WINDOW *_infoWindow;
        int     _terminal_W;
        int     _terminal_H;
        
};

extern "C" IModule* create_module(void);
extern "C" void destroy_module(IModule* p);

#endif /* MOD_NCURSES_HPP */