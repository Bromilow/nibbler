/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IModule.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:31:30 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/17 20:48:28 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMODULE_HPP
# define IMODULE_HPP

# include "GameEnvironment.hpp"

class IModule {
    public:
        virtual ~IModule() = default;
        virtual t_input getInput(const bool accept) = 0;
        virtual int     updateDisplay(void)         = 0;
};

#endif /* IMODULE_HPP */