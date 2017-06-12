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

# include <curses.h>
# include <iostream>
# include "IModule.hpp"

class Module : public IModule
{
    public:
        Module();
        ~Module();
        Module(const Module & src);
        Module & operator=(const Module & rhs);
        
        virtual int getInput(void);
        virtual int updateDisplay(void);

    private:
        WINDOW *_gameWindow;
        WINDOW *_infoWindow;
        int     _terminal_W;
        int     _terminal_H;
        
};

extern "C" IModule* create_module(void);
extern "C" void     destroy_module(IModule* module);

#endif /* MODULE_HPP */