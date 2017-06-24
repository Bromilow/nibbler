/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:57 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:17:38 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_MAIN_HPP
# define NIBBLER_MAIN_HPP

# include <string>
# include <cstdlib>
# include <iostream>
# include <dlfcn.h>
# include "Core.hpp"

typedef int (*main_menu_t)();

int     checkInput(int ac, char **av);
int     main_menu(void);

#endif /* NIBBLER_MAIN_HPP */