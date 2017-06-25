
#include "Module.hpp"

#define TILE_SIZE  32

Module::Module(GameEnvironment & data) : gameData(data),  _choice(-1)
{
	//	sigaction(SIGWINCH, NULL, &this->_oldSIGWINCH);

	this->_window_H = 0;
	this->_window_W = 0;

	// Get max X and Y
	//getmaxyx(stdscr, this->_window_H, this->_window_W);

	this->_padX = 1;
	this->_padY = 1;

	// Game area
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        exit(-1);
    }
	
	//this->gameWindow = SDL_CreateWindow(this->_window_H, this->_window_W, SDL_WINDOW_RESIZABLE, &window, &renderer);
	this->_gameWindow = SDL_CreateWindow("SDL_nibbler", this->_padX, this->_padY, /*TILE_SIZE * this->_window_W*/640, /*TILE_SIZE * this->_window_H*/480, SDL_WINDOW_RESIZABLE);
	if (this->_gameWindow == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        exit(-1);
    }

    /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
    this->_renderer	 = SDL_CreateRenderer(this->_gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if (this->_renderer == NULL) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        exit(-1);
    }

	this->_fruit_surface = SDL_LoadBMP("apple.bmp");
    this->_shead_surface = SDL_LoadBMP("head.bmp");
    this->_snake_surface = SDL_LoadBMP("snake.bmp");
    this->_field_surface = SDL_LoadBMP("field.bmp");
    this->_fruit_texture = SDL_CreateTextureFromSurface(_renderer, this->_fruit_surface);
    this->_shead_texture = SDL_CreateTextureFromSurface(_renderer, this->_shead_surface);
    this->_snake_texture = SDL_CreateTextureFromSurface(_renderer, this->_snake_surface);
    this->_field_texture = SDL_CreateTextureFromSurface(_renderer, this->_field_surface);
	SDL_FreeSurface(this->_fruit_surface);
	SDL_FreeSurface(this->_shead_surface);
	SDL_FreeSurface(this->_snake_surface);
	SDL_FreeSurface(this->_field_surface);

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);  //display what has been rendered

	atexit(SDL_Quit);

	SDL_RenderClear(_renderer);
}

Module::~Module()
{
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_gameWindow);
	SDL_Quit();
}

Module::Module(const Module & src) : gameData(src.gameData)
{
	*this = src;
}

Module & Module::operator=(const Module & rhs)
{
	//std::cout << "Module::Assignation Operator" << std::endl; //debug
	this->_gameWindow = rhs._gameWindow;
	this->_renderer = rhs._renderer;
	this->_window_W = rhs._window_W;
	this->_window_H = rhs._window_H;

	return (*this);
}

t_input		Module::getInput(int accept)
{
    SDL_Event		choice;
	unsigned int	tmp;

	SDL_PollEvent(&choice);
	if (this->_choice != choice.type)
		this->_choice = choice.type;
	if (accept == 1)
	{
		tmp = this->_choice;
		this->_choice = -1;
		return (this->_handleInput(tmp));
	}
	return (NONE);
}

t_input		Module::_handleInput(unsigned int choice)
{
	if (this->gameData.paused)
		switch(choice)
		{
			case SDLK_ESCAPE:
			case SDLK_q:
				return QUIT;
			case SDLK_p:
				return PAUSE;
			case SDLK_1:
				return MOD1;
			case SDLK_2:
				return MOD2;
			case SDLK_3:
				return MOD3;
			case SDLK_UP:
			case SDLK_DOWN:
			case SDLK_LEFT:
			case SDLK_RIGHT:
			case SDLK_SPACE:
			default:
				return NONE;
		}
	switch(choice)
	{
		case SDLK_UP:
			return UP;
		case SDLK_DOWN:
			return DOWN;
		case SDLK_LEFT:
			return LEFT;
		case SDLK_RIGHT:
			return RIGHT;
		case SDLK_q:
			return QUIT;
		case SDLK_p:
			return PAUSE;
		case SDLK_1:
			return MOD1;
		case SDLK_2:
			return MOD2;
		case SDLK_3:
			return MOD3;
		case SDL_QUIT:
			return QUIT;
		case SDLK_SPACE:
			return (SUPACHOMP);
		default:
				break;
	}
	return NONE;
}

int		Module::updateDisplay(void)
{
	// Check game state
	if (this->gameData.paused)
		return (this->_gameIsPaused());

	// Prep screen for new output
	SDL_RenderClear(_renderer);

	// Update game window
	this->_updateGameWindow();

	return (1);
}

int     Module::_gameIsPaused(void)
{
	SDL_Rect		block;

	SDL_RenderClear(_renderer);
	block.h = TILE_SIZE;
	block.w = TILE_SIZE;
	block.x = SDL_WINDOWPOS_CENTERED;
	block.y = SDL_WINDOWPOS_CENTERED;
	SDL_RenderCopy(_renderer, this->_fruit_texture, NULL, &block);
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
	return(1);
}

void    Module::_updateGameWindow(void)
{
	unsigned int	y;
	unsigned int	x;
	SDL_Rect		block;

	for (y = 0; y < this->gameData.mapHeight; ++y)	
	{
		x = 0;
		for (; x < this->gameData.mapWidth; ++x)
		{
			std::cerr << this->gameData.map[y][x] << " ";
			switch (this->gameData.map[y][x])
			{
				case MAP_NONE:
					break;
				case MAP_WALL:
   					block.h = TILE_SIZE;
  					block.w = TILE_SIZE;
  					block.x = x * TILE_SIZE;
  					block.y = y * TILE_SIZE;
  					SDL_RenderCopy(_renderer, this->_field_texture, NULL, &block);
					break;
				case MAP_FOOD:
    				block.h = TILE_SIZE;
    				block.w = TILE_SIZE;
    				block.x = x * TILE_SIZE;
    				block.y = y * TILE_SIZE;
    				SDL_RenderCopy(_renderer, this->_fruit_texture, NULL, &block);
					break;
				case MAP_PLAYER:
   					block.h = TILE_SIZE;
  					block.w = TILE_SIZE;
  					block.x = x * TILE_SIZE;
  					block.y = y * TILE_SIZE;
  					SDL_RenderCopy(_renderer, this->_shead_texture, NULL, &block);
					break;
			}
			if (this->gameData.map[y][x] == this->gameData.snakeLength + 9)
			{
    				block.h = TILE_SIZE;
    				block.w = TILE_SIZE;
    				block.x = x * TILE_SIZE;
    				block.y = y * TILE_SIZE;
    				SDL_RenderCopy(_renderer, this->_snake_texture, NULL, &block);
			}
			else if ((this->gameData.map[y][x] > MAP_PLAYER) &&
				(this->gameData.map[y][x] < this->gameData.snakeLength + 9))
			{
    				block.h = TILE_SIZE;
    				block.w = TILE_SIZE;
    				block.x = x * TILE_SIZE;
    				block.y = y * TILE_SIZE;
    				SDL_RenderCopy(_renderer, this->_snake_texture, NULL, &block);
			}
		}
		std::cerr << std::endl;
	}
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
}

IModule*	create_module(GameEnvironment & data) 
{
	return new Module(data);
}

void		destroy_module(IModule* module)
{
	delete module;
}