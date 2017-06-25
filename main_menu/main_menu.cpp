/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 21:48:01 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/24 15:28:14 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_menu.hpp"

int main_menu(void)
{
    int			choice;
	int			highlight = 0;
    int         yMax, xMax, newYMax, newXMax;
    WINDOW      *menuwin;
    const int   menu_length = 5;
    int         menu_order[menu_length] = {4, 1, 2, 3, 0};
	std::string	choices[menu_length] = {"QUIT",
                                        "one",
                                        "two",
                                        "three",
                                        "random" };

    initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);

    // Get terminal size
    getmaxyx(stdscr, yMax, xMax);

    // Create menu area
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

        keypad(menuwin, true);
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

        if (xMax > 80 && yMax > 14 + menu_length)
        {
            mvwprintw(stdscr, 1, (xMax / 2) - 40, "::::    ::: ::::::::::: :::::::::  :::::::::  :::        :::::::::: :::::::::  ");
            mvwprintw(stdscr, 2, (xMax / 2) - 40, ":+:+:   :+:     :+:     :+:    :+: :+:    :+: :+:        :+:        :+:    :+: ");
            mvwprintw(stdscr, 3, (xMax / 2) - 40, ":+:+:+  +:+     +:+     +:+    +:+ +:+    +:+ +:+        +:+        +:+    +:+ ");
            mvwprintw(stdscr, 4, (xMax / 2) - 40, "+#+ +:+ +#+     +#+     +#++:++#+  +#++:++#+  +#+        +#++:++#   +#++:++#:  ");
            mvwprintw(stdscr, 5, (xMax / 2) - 40, "+#+  +#+#+#     +#+     +#+    +#+ +#+    +#+ +#+        +#+        +#+    +#+ ");
            mvwprintw(stdscr, 6, (xMax / 2) - 40, "#+#   #+#+#     #+#     #+#    #+# #+#    #+# #+#        #+#        #+#    #+# ");
            mvwprintw(stdscr, 7, (xMax / 2) - 40, "###    #### ########### #########  #########  ########## ########## ###    ### ");
        }

/*        
::::    ::: ::::::::::: :::::::::  :::::::::  :::        :::::::::: :::::::::  
:+:+:   :+:     :+:     :+:    :+: :+:    :+: :+:        :+:        :+:    :+: 
:+:+:+  +:+     +:+     +:+    +:+ +:+    +:+ +:+        +:+        +:+    +:+ 
+#+ +:+ +#+     +#+     +#++:++#+  +#++:++#+  +#+        +#++:++#   +#++:++#:  
+#+  +#+#+#     +#+     +#+    +#+ +#+    +#+ +#+        +#+        +#+    +#+ 
#+#   #+#+#     #+#     #+#    #+# #+#    #+# #+#        #+#        #+#    #+# 
###    #### ########### #########  #########  ########## ########## ###    ### 
*/

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