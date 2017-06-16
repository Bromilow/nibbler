/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IModule.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:31:30 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/15 17:26:08 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMODULE_HPP
# define IMODULE_HPP

/*# include "GameEnvironment.hpp"*/
# include "Level.hpp"

typedef enum    e_input {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    PAUSE,
    MOD1,
    MOD2,
    MOD3,
    SUPACHOMP,
}               t_input;

class IModule {
    public:
        virtual ~IModule() = default;
        virtual int getInput(void) = 0;
        virtual int updateDisplay(void) = 0;
};

#endif /* IMODULE_HPP */