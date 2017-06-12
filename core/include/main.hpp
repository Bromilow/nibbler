/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:43:57 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 03:53:20 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_MAIN_HPP
# define NIBBLER_MAIN_HPP

# include <string>
# include <cstdlib>
# include <iostream>
# include "GameEnvironment.hpp"

# define MIN_SCREEN_W    640
# define MIN_SCREEN_H    480
# define MAX_SCREEN_W    1280
# define MAX_SCREEN_H    960

int     checkInput(int ac, char **av);
int     main_menu(void);

#endif /* NIBBLER_MAIN_HPP */