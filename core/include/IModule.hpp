/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IModule.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:31:30 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 18:43:44 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMODULE_HPP
# define IMODULE_HPP

class IModule {
    public:
        virtual ~IModule() = default;
        virtual int getInput(void) = 0;
        virtual int updateDisplay(void) = 0;
};

#endif /* IMODULE_HPP */