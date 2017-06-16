/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 14:53:27 by kbamping          #+#    #+#             */
/*   Updated: 2017/06/08 21:51:54 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BASE_HPP_
# define _BASE_HPP_

# include <curses.h>
# include <string>
# include <cstdlib>

# define DIR_UP 1
# define DIR_RIGHT 2
# define DIR_DOWN 3
# define DIR_LEFT 4


class Base {
public:
		Base(void);
        Base(WINDOW * win, char ch);
		Base(Base const & src);
		Base& operator=(Base const & rhs);
		~Base(void);

        void	displayObject(void);
        int     getLocation(char c) const;
        void    setLocation(int xLoc, int yLoc);
        int     getMax(char c) const;
        void    setMax(char c, int val);
        WINDOW  *getWindow() const;
        void    setWindow(WINDOW *win);
        char    getCharacter(void) const;
        void    setCharacter(char c);
        

private:
        int     _currLocation[2];
        int     _xMax;
        int     _yMax;
		char	_character;
        WINDOW  *_curwin;

};

#endif /* _BASE_HPP_ */