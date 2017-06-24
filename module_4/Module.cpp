
#include "Module.hpp"

#define TILE_SIZE  32

Module::Module(GameEnvironment & data) : gameData(data),  _choice(-1)
{
	//	sigaction(SIGWINCH, NULL, &this->_oldSIGWINCH);

	this->_window_H = 0;
	this->_window_W = 0;

	SDL_Window *window;
    SDL_Renderer *renderer;

	// Refresh and clear stdscr
	clear();
	refresh();

	// Get max X and Y
	getmaxyx(stdscr, this->_window_H, this->_window_W);

	this->_padX = 1;
	this->_padY = 1;

	// Game area
	
	    this->gameWindow = SDL_CreateWindowAndRenderer(this->_window_H, this->_window_W, SDL_WINDOW_RESIZABLE, &window, &renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);  //display what has been rendered

	atexit(SDL_Quit);

	SDL_Renderer* renderer = NULL;
	SDL_Surface*  field_surface = NULL;
	SDL_Surface*  fruit_surface = NULL;
	SDL_Surface*  shead_surface = NULL;
	SDL_Surface*  snake_surface = NULL;
	SDL_Texture*  field_texture = NULL;
	SDL_Texture*  fruit_texture = NULL;
	SDL_Texture*  shead_texture = NULL;
	SDL_Texture*  snake_texture = NULL;

    fruit_surface = SDL_LoadBMP("apple.bmp");
    shead_surface = SDL_LoadBMP("head.bmp");
    snake_surface = SDL_LoadBMP("snake.bmp");
    field_surface = SDL_LoadBMP("field.bmp");
    fruit_texture = SDL_CreateTextureFromSurface(renderer, fruit_surface);
    shead_texture = SDL_CreateTextureFromSurface(renderer, shead_surface);
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    field_texture = SDL_CreateTextureFromSurface(renderer, field_surface);

	refresh();
}

Module::~Module()
{
	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

Module::Module(const Module & src) : gameData(src.gameData)
{
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	//std::cout << "Module::Assignation Operator" << std::endl; //debug
	this->_gameWindow = rhs._gameWindow;
	this->_window_W = rhs._window_W;
	this->_window_H = rhs._window_H;

	return (*this);
}



// Member functions
t_input		Module::getInput(int accept)
{

	SDL_Event event;
//	const Uint8 *state = SDL_GetKeyboardState(NULL);                     a different way to check key input
// 	SDL_PumpEvents();

    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit( -1 );
    }

	if( !SDL_SetVideoMode( 320, 200, 0, 0 ) ){
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

	SDL_EnableUNICODE( 1 );

	while( SDL_PollEvent( &event ) ){           
        switch( event.type ){
            case SDLK_KEYUP:
				return UP;
			case SDLK_KEYDOWN:
				return DOWN;
            case SDLK_KEYLEFT:
				return LEFT;
			case SDLK_KEYRIGHT:
				return RIGHT;
			case SDLK_KEYQ:
				return QUIT;
			case SDLK_KEYP:
				return PAUSE;
			case SDLK_KEY1:
				return MOD1;
			case SDLK_KEY2:
				return MOD2;
			case SDLK_KEY3:
				return MOD3;

            case SDLK_QUIT:
                quit = 1;
                break;

            default:
                break;
        }
	}

	if (choice != -1 && this->_choice != choice)
		this->_choice = event;
	if (accept == 1)
	{
		choice = this->_choice;
		this->_choice = -1;
		if (this->gameData.paused)
			switch(event.type)
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

	clear(this->_gameWindow);


	for (y = 0; y < this->gameData.mapHeight; ++y)	
	{
		x = 0;
		//wmove(this->_gameWindow, y + this->_padY, x + this->_padX);
		for (; x < this->gameData.mapWidth; ++x)
		{
			switch (this->gameData.map[y][x])
			{
				case MAP_NONE:
					break;
				case MAP_WALL:
					SDL_Rect rect;
   					rect.h = TILE_SIZE;
  					rect.w = TILE_SIZE;
  					rect.x = x * TILE_SIZE;
  					rect.y = y * TILE_SIZE;
  					SDL_RenderCopy(renderer, field_surface, NULL, &rect);
					break;
				case MAP_FOOD:
    				SDL_Rect rect;
    				rect.h = TILE_SIZE;
    				rect.w = TILE_SIZE;
    				rect.x = x * TILE_SIZE;
    				rect.y = y * TILE_SIZE;
    				SDL_RenderCopy(renderer, fruit_texture, NULL, &rect);
					break;
				case MAP_PLAYER:
					SDL_Rect rect;
   					rect.h = TILE_SIZE;
  					rect.w = TILE_SIZE;
  					rect.x = x * TILE_SIZE;
  					rect.y = y * TILE_SIZE;
  					SDL_RenderCopy(renderer, shead_texture, NULL, &rect);
					break;
			}
			if (this->gameData.map[y][x] == this->gameData.snakeLength + 9)
			{
				SDL_Rect rect;
    			rect.h = TILE_SIZE;
    			rect.w = TILE_SIZE;
    			rect.x = x * TILE_SIZE;
    			rect.y = y * TILE_SIZE;
    			SDL_RenderCopy(renderer, snake_surface, NULL, &rect);
			}
			else if ((this->gameData.map[y][x] > MAP_PLAYER) &&
				(this->gameData.map[y][x] < this->gameData.snakeLength + 9))
			{
				SDL_Rect rect;
    			rect.h = TILE_SIZE;
    			rect.w = TILE_SIZE;
    			rect.x = x * TILE_SIZE;
    			rect.y = y * TILE_SIZE;
    			SDL_RenderCopy(renderer, snake_surface, NULL, &rect);
			}
		}
	}

	SDL_RenderPresent(renderer);

	return (1);
}

IModule*	create_module(GameEnvironment & data) 
{
	return new Module(data);
}

void		destroy_module(IModule* module)
{
	delete module;
	std::cout << "Module::Class Factory::delete_module()::MODULE DELETED" << std::endl; //debug

}