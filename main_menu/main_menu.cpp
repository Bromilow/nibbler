/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 21:48:01 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/12 13:50:12 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_menu.hpp"

int main_menu(void) {
    std::cout << "main_menu() " << '\n';

    initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);
    
    int			choice;
	int			highlight = 0;
    int         yMax, xMax;     // max size of terminal
    const int   menu_length = 5;
    int         menu_order[menu_length] = {4, 1, 2, 3, 0};
	std::string	choices[menu_length] = {"QUIT",
                                        "one",
                                        "two",
                                        "three",
                                        "random" };


    while (1)
    {
        // Get terminal size
        getmaxyx(stdscr, yMax, xMax);

        // Create menu area
        // newwin(nlines, ncols, posY, posX);
        WINDOW * menuwin = newwin(MENU_H, MENU_W, (yMax/2) - (MENU_H / 2), (xMax/2) - (MENU_W / 2));
        box(menuwin, 0, 0);
        wrefresh(menuwin);
        keypad(menuwin, true);  // Enable keypad

        // Print out choices and highlight the current selection
        for (int i = 0; i < menu_length; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[menu_order[i]].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        // Get input from user
        choice = wgetch(menuwin);

        // Check for navigation
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = menu_length - 1;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == menu_length)
                    highlight = 0;
                break;
            default:
                break;
        }

        // Check for selection
        if (choice == 10 && highlight < menu_length){
            endwin();
            return (highlight);
        }

    }
    endwin();
    return (-1);
}