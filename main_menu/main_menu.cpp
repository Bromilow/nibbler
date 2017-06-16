/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 21:48:01 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/16 20:50:39 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_menu.hpp"

int main_menu(void)
{
    initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);
    
    int			choice;
	int			highlight = 0;
    int         yMax, xMax, newYMax, newXMax;     // max size of terminal
    WINDOW      *menuwin;
    const int   menu_length = 5;
    int         menu_order[menu_length] = {4, 1, 2, 3, 0};
	std::string	choices[menu_length] = {"QUIT",
                                        "one",
                                        "two",
                                        "three",
                                        "random" };

    // Get terminal size
    getmaxyx(stdscr, yMax, xMax);

    // Create menu area
    // newwin(nlines, ncols, posY, posX);
    menuwin = newwin(MENU_H, MENU_W, (yMax/2) - (MENU_H / 2), (xMax/2) - (MENU_W / 2));
    keypad(menuwin, true);  // Enable keypad

    while (1)
    {
        // Get terminal size
        getmaxyx(stdscr, newYMax, newXMax);
        if (newXMax <= MENU_W * 2 || newYMax <= MENU_H * 2)
        {
            wclear(stdscr);
            wclear(menuwin);    
            mvwprintw(menuwin, 1, 1, "Terminal too small!");
            wrefresh(stdscr);
            wrefresh(menuwin);
            continue;
        }
        else if (newXMax != xMax || newYMax != yMax)
        {
            mvwin(menuwin, (newYMax/2) - (MENU_H / 2), (newXMax/2) - (MENU_W / 2));
            wresize(menuwin, MENU_H, MENU_W);
            xMax = newXMax;
            yMax = newYMax;
        }

        keypad(menuwin, true);  // Enable keypad
        wclear(stdscr);
        wclear(menuwin);

        // Print out choices and highlight the current selection
        for (int i = 0; i < menu_length; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[menu_order[i]].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        box(menuwin, 0, 0);
        wrefresh(stdscr);
        wrefresh(menuwin);

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
        if (choice == 10 && highlight < menu_length && menu_order[highlight] < menu_length){
            delwin(menuwin);
            endwin();
            endwin();
            return (menu_order[highlight]);
        }

    }
    delwin(menuwin);
    endwin();
    return (-1);
}