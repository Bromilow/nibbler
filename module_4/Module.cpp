
#include "Module.hpp"

Module::Module(GameEnvironment & data) : gameData(data),  _choice(-1)
{
	sigaction(SIGWINCH, NULL, &this->_oldSIGWINCH);
	//std::cout << "Module::Default constructor" << std::endl; //debug
	this->_terminal_H = 0;
	this->_terminal_W = 0;

	initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, true);

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);

	// Refresh and clear stdscr
	clear();
	refresh();

	// Get max X and Y
	getmaxyx(stdscr, this->_terminal_H, this->_terminal_W);

	// Get padding to center map in terminal
	//this->_padX = (this->_terminal_W / 2) - (this->gameData.mapWidth + this->gameData.mapWidth / 2); //  (this->_terminal_W / 2) - (this->gameData.mapWidth / 2)
	//this->_padY = (this->_terminal_H / 2) - (this->gameData.mapHeight);
	this->_padX = 1;
	this->_padY = 1;

	// Game area
	this->_gameWindow = newwin(this->_terminal_H - INFO_WIN_H, this->_terminal_W, INFO_WIN_H, 0);
	/*box(this->_gameWindow, 0, 0);*/
	nodelay(this->_gameWindow, true);
	keypad(this->_gameWindow, true);

	// Scrolling in window
	/*idlok(this->_gameWindow, true);
	scrollok(this->_gameWindow, true);*/

	// Info bar
	this->_infoWindow = newwin(INFO_WIN_H, this->_terminal_W, 0, 0);
	/*box(this->_infoWindow, 0, 0);*/
	nodelay(this->_infoWindow, true);

	wrefresh(this->_gameWindow);
	wrefresh(this->_infoWindow);
	// Refresh stdscr
	refresh();
}

Module::~Module()
{
	//std::cout << "Module::Destructor" << std::endl; //debug
	delwin(this->_gameWindow);
	delwin(this->_infoWindow);
	endwin();
	sigaction(SIGWINCH, &this->_oldSIGWINCH, NULL);
}

Module::Module(const Module & src) : gameData(src.gameData)
{
	//std::cout << "Module::Copy constructor" << std::endl; //debug
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	//std::cout << "Module::Assignation Operator" << std::endl; //debug
	this->_gameWindow = rhs._gameWindow;
	this->_infoWindow = rhs._infoWindow;
	this->_terminal_W = rhs._terminal_W;
	this->_terminal_H = rhs._terminal_H;

	return (*this);
}

// Member functions
t_input		Module::getInput(int accept)
{
    int	choice;

	choice = wgetch(this->_gameWindow);
	//std::cerr << "B4-1:\nchoice: " << choice << "\n_choice: " << this->_choice << std::endl;
	if (choice != -1 && this->_choice != choice)
		this->_choice = choice;
	//std::cerr << "B4-2:\nchoice: " << choice << "\n_choice: " << this->_choice << std::endl;
	if (accept == 1)
	{
		choice = this->_choice;
		this->_choice = -1;
		if (this->gameData.paused)
			switch(choice)
			{
				case 27:
				case 'q':
					return QUIT;
				case 'p':
					return PAUSE;
				case '1':
					return MOD1;
				case '2':
					return MOD2;
				case '3':
					return MOD3;
				case KEY_UP:
				case KEY_DOWN:
				case KEY_LEFT:
				case KEY_RIGHT:
				case ' ':
				default:
					return NONE;
			}
		switch(choice)
		{
			case KEY_UP:
				return UP;
			case KEY_DOWN:
				return DOWN;
			case KEY_LEFT:
				return LEFT;
			case KEY_RIGHT:
				return RIGHT;
			case 27:
			case 'q':
				return QUIT;
			case 'p':
				return PAUSE;
			case '1':
				return MOD1;
			case '2':
				return MOD2;
			case '3':
				return MOD3;
			case ' ':
				return SUPACHOMP;
			default:
				return NONE;
		}
	}
	return (NONE);
}

int		Module::updateDisplay(void)
{
	//std::cerr << "Module::updateDisplay()" << std::endl; //debug
	/*static unsigned int n = 0;*/
	unsigned int 		x, y, newYMax, newXMax;

	// Get terminal size
	getmaxyx(stdscr, newYMax, newXMax);
	if (newXMax <= this->gameData.mapWidth * 2 + 5 || newYMax <= this->gameData.mapHeight * 2 + 10)
	{
		wclear(stdscr);
		wclear(this->_infoWindow);    
		wclear(this->_gameWindow);
		mvwprintw(this->_gameWindow, 1, 1, "Terminal too small!");
		wrefresh(stdscr);
		wrefresh(this->_infoWindow);
		wrefresh(this->_gameWindow);
		return (0);
	}
	if (newXMax != this->_terminal_W || newYMax != this->_terminal_H)
	{
		// Resize and move infowin
		wresize(this->_infoWindow, INFO_WIN_H, newXMax);
		mvwin(this->_infoWindow, 0, 0);

		// Resize and move gamewin
		wresize(this->_gameWindow, newYMax - INFO_WIN_H, newXMax);
		mvwin(this->_gameWindow, newYMax - INFO_WIN_H , 0);

		// Update padding
		//this->_padX = (this->_terminal_W / 2) - (this->gameData.mapWidth + this->gameData.mapWidth / 2); //  (this->_terminal_W / 2) - (this->gameData.mapWidth / 2)
		//this->_padY = (this->_terminal_H / 2) - (this->gameData.mapHeight);

		// Update dimensions
		this->_terminal_W = newXMax;
		this->_terminal_H = newYMax;
	}
	if (this->gameData.paused)
	{
		wclear(stdscr);
		wclear(this->_infoWindow);    
		wclear(this->_gameWindow);
		mvwprintw(this->_gameWindow, this->_terminal_H / 2, this->_terminal_W / 2, "\\;---[ PAUSED ]---;/");
		wrefresh(stdscr);
		wrefresh(this->_infoWindow);
		wrefresh(this->_gameWindow);
		return(1);
	}

	wclear(this->_infoWindow);
	wclear(this->_gameWindow);

	static int i = 0;
	int a;


	mvwprintw(this->_infoWindow,1,1, "Time : %d\n", this->gameData.gameTime);
	mvwprintw(this->_infoWindow,2,1, "your score is %d", this->gameData.snakeLength - 4);
	a = 0;

/*
.__   __.  __  .______   .______    __       _______ .______      
|  \ |  | |  | |   _  \  |   _  \  |  |     |   ____||   _  \     
|   \|  | |  | |  |_)  | |  |_)  | |  |     |  |__   |  |_)  |    
|  . `  | |  | |   _  <  |   _  <  |  |     |   __|  |      /     
|  |\   | |  | |  |_)  | |  |_)  | |  `----.|  |____ |  |\  \----.
|__| \__| |__| |______/  |______/  |_______||_______|| _| `._____|
*/

	for (; a != 3; a++)
	{
		mvwprintw(this->_infoWindow,1 ,20, "()  () (----) |^^^) |^^^) ||     |---- (^^^)");
		mvwprintw(this->_infoWindow,2 ,20, "(-) ()   ||   |--B  |--B  ||     |--   (><)");
		mvwprintw(this->_infoWindow,3 ,20, "() (-) (----) |___) |___) |||||  |____ |   \\");
	}


	for (y = 0; y < this->gameData.mapHeight; ++y)	
	{
		x = 0;
		//wmove(this->_gameWindow, y + this->_padY, x + this->_padX);
		for (; x < this->gameData.mapWidth; ++x)
		{
			switch (this->gameData.map[y][x])
			{
				case MAP_NONE:
					wattron(this->_gameWindow, COLOR_PAIR(1));
					mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "    ");
					mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "    ");
					wattroff(this->_gameWindow, COLOR_PAIR(1));
					break;
				case MAP_WALL:
					mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "####");
					mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "####");
					break;
				case MAP_FOOD:
					
					if ((i % 2) == 0)
					{
						wattron(this->_gameWindow, COLOR_PAIR(5));
						mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "    ");
						mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "CHOW");
						wattroff(this->_gameWindow, COLOR_PAIR(5));
						i++;
					}
					else if ((i % 2) == 1)
					{
						wattron(this->_gameWindow, COLOR_PAIR(5));
						mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "CHOW");
						mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "    ");
						wattroff(this->_gameWindow, COLOR_PAIR(5));
						i++;
					}
					break;
				case MAP_PLAYER:
					wattron(this->_gameWindow, A_REVERSE);
					mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "    ");
					mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "    ");
					wattroff(this->_gameWindow, A_REVERSE);
					break;
			}
			if (this->gameData.map[y][x] == this->gameData.snakeLength + 9)
			{
				// its the tail
				wattron(this->_gameWindow, COLOR_PAIR(4));
				mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "....");
				mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "....");
				wattroff(this->_gameWindow, COLOR_PAIR(4));
			}
			else if ((this->gameData.map[y][x] > MAP_PLAYER) &&
				(this->gameData.map[y][x] < this->gameData.snakeLength + 9))
			{
				// its the body
				wattron(this->_gameWindow, COLOR_PAIR(4));
				mvwprintw(this->_gameWindow, (y * 2)  + this->_padY, (x * 4) + this->_padX, "oooo");
				mvwprintw( this->_gameWindow, (y * 2) + 1  + this->_padY, (x * 4) + this->_padX, "oooo");
				wattroff(this->_gameWindow, COLOR_PAIR(4));
			}
		}
		//wprintw(this->_gameWindow, "\n");
	}

	box(this->_infoWindow, 0, 0);
	box(this->_gameWindow, 0, 0);


	// Update virtual screen
	wnoutrefresh(this->_infoWindow);
	wnoutrefresh(this->_gameWindow);


	// update physical screen
	doupdate();

	return (1);
}

// Class factories
// Need to add type def for class factories --- http://www.tldp.org/HOWTO/C++-dlopen/thesolution.html#AEN216
IModule*	create_module(GameEnvironment & data) 
{
	//std::cout << "Module::Class Factory::create_module()" << std::endl; //debug
	/*(void)data;*/
	return new Module(data);
}

void		destroy_module(IModule* module)
{
	//std::cout << "Module::Class Factory::delete_module()" << std::endl; //debug
	delete module;
	std::cout << "Module::Class Factory::delete_module()::MODULE DELETED" << std::endl; //debug

}