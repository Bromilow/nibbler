/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:57 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 12:45:05 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
# define NIBBLER_HPP

# include <string>
# include <cstdlib>
# include <iostream>
# include <dlfcn.h>
# include "GameLoop.hpp"
# include "IModule/IModule.hpp"

# define MIN_SCREEN_W    640
# define MIN_SCREEN_H    480
# define MAX_SCREEN_W    1280
# define MAX_SCREEN_H    960

int     main_menu(void);
int     initialize_module(int option, IModule *module);
int     delete_module(int option, IModule *module);

#endif /* NIBBLER_HPP */