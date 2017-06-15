/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:57 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/14 18:04:30 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_MAIN_HPP
# define NIBBLER_MAIN_HPP

# include <string>
# include <cstdlib>
# include <iostream>
# include <dlfcn.h>
/*# include "IModule.hpp"*/
# include "GameEnvironment.hpp"

int     checkInput(int ac, char **av);
int     main_menu(void);

#endif /* NIBBLER_MAIN_HPP */