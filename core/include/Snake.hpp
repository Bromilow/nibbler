/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 14:53:27 by kbamping           #+#    #+#             */
/*   Updated: 2017/05/27 21:34:10 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <curses.h>
# include <string>
# include <cstdio>
# include <cstdlib>
# include <ctime>
# include <iostream>

# define DIR_UP 1
# define DIR_RIGHT 2
# define DIR_DOWN 3
# define DIR_LEFT 4


class Snake : public Base {
public:
		Snake(void);
        Snake(WINDOW * win, char ch);
		Snake(Snake const & src);
		Snake& operator=(Snake const & rhs);
		~Snake(void);

		

		void	mvfwd(void);
		void	turnLeft(void);
		void	turnRight(void);
/* overload */void	displayObject(void);
        

private:
        int     _direction;
        int     _length;
        int     _score;        

};

#endif /* _SNAKE_HPP_ */