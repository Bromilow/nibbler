/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameLoop.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:40:03 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/09 03:31:35 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_OBJECT_HPP
# define GAME_OBJECT_HPP

# include <ctime>
# include <iostream>
# include "IModule/IModule.hpp"

int     gameLoop(IModule *module);
/*int     getTotalGameTime(void);
int     getCurrentSessionTime(void);*/

#endif