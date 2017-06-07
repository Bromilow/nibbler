/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 14:53:27 by kbamping           #+#    #+#             */
/*   Updated: 2017/05/27 21:34:10 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SNAKE_OBJECT_HPP_
# define _SNAKE_OBJECT_HPP_

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


class SnakeObject {
public:
		SnakeObject(void);
        SnakeObject(WINDOW * win, char ch);
		SnakeObject(SnakeObject const & src);
		SnakeObject& operator=(SnakeObject const & rhs);
		~SnakeObject(void);

		

		void	mvfwd(void);                            /
		//void	mvdown(void);
		void	turnLeft(void);
		void	turnRight(void);
		int		getInput(void);
        void	displaySnakeObject(void);
        int     getLocation(char c) const;
        void    setLocation(int xLoc, int yLoc);
        int     getMax(char c) const;
        void    setMax(char c, int val);
        WINDOW  *getWindow() const;
        void    setWindow(WINDOW *win);
        //bool	isAlive(void) const;
        //void	setAlive(bool val);
        char    getCharacter(void) const;
        void    setCharacter(char c);
        

private:
        int     _currLocation[2];
        int     _xMax;
        int     _yMax;
		char	_character;
        WINDOW  *_curwin;
        //bool    _alive;
        //////
        int     _direction;              // need to initialise 

};

#endif /* _SNAKE_OBJECT_HPP_ */