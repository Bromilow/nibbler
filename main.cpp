/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:40:48 by kbamping           #+#    #+#             */
/*   Updated: 2017/06/06 10:18:41 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameObject.hpp"
#include "Player.hpp"
#include "Entity.hpp"
/*
void	updateDisplay(void);
bool	objectsCollide(void);*/

int	main()
{
	initscr();
	noecho();
	cbreak();								// raw();
	curs_set(0);
	nodelay(stdscr, true);

	// get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	if (xMax < 50)
		xMax = 50;
	if (yMax < 20)
		yMax = 20;
	if (xMax > 150)
		xMax = 150;
	if (yMax > 50)
		yMax = 50;
	

	std::string	choices[2] = {"play", "exit"};
	int			choice;
	int			highlight = 0;

	while (1)
	{
		clear();
		//	creates a window for our input
		WINDOW * menuwin = newwin(4, 7, (yMax/2) - 2, (xMax/2) - 2);
		box(menuwin, 0, 0);
		refresh();
		wrefresh(menuwin);

		keypad(menuwin, true);

		for (int i = 0; i < 2; i++)
		{
			if (i == highlight)
				wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+1, 1, choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if (highlight == -1)
					highlight = 1;
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == 2)
					highlight = 0;
				break;
			default:
				break;
		}
		if (choice == 10)
		{
			if (choices[highlight] == "exit")
			{
				endwin();
				return (0);
			}
			else if (choices[highlight] == "play")
			{
				delwin(menuwin);
				endwin();
				refresh();

				WINDOW * infowin = newwin(5, xMax, 0, 0);
				box(infowin, 0, 0);
				wrefresh(infowin);

				WINDOW * gamewin = newwin(yMax - 5, xMax, 5, 0);
				box(gamewin, 0, 0);
				nodelay(gamewin, true);
				wrefresh(gamewin);

				refresh();

				Player * p = new Player(gamewin);
				Entity * e[20];
				for (int x = 0; x < 20; ++x)
				{
					 e[x] = new Entity(gamewin, xMax - 1, (rand() % yMax));
				}

				do {
					//updateDisplay();


				for (int i = 0 ;i < 5; i++) {
					if (e[i]->isAlive())
						e[i]->displayGameObject();
				}
				if (p->isAlive())
					p->displayGameObject();
					

					wrefresh(gamewin);
				} while (p->getmv() != 27);

				delwin(gamewin);
				delwin(infowin);
				endwin();
				continue;
			}
		}
	}
	return (0);
}
/*
void	updateDisplay(void) {
	for (int i = 0 ;i < 5; i++) {
		if (e[i].isAlive())
			e[i].displayGameObject();
	}
	if (p.isAlive())
		p.displayGameObject();
}

bool	objectsCollide(void) {
	int	playerLoc[2], enemyLoc[2];

	playerLoc[0] = Game::player->getLocation('x');
	playerLoc[1] = Game::player->getLocation('y');
	// Check enemies
	for (int i = 0 ;i < 5; i++) {
		enemyLoc[0] = Game::player->getLocation('x');
		enemyLoc[1] = Game::player->getLocation('y');
		if (playerLoc[0] == enemyLoc[0] + 1 && playerLoc[1] == enemyLoc[1]) {
			Game::player->setAlive(false);
			return (false);
		}
	}
	return (true);
}*/