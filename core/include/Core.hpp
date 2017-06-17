/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 15:42:18 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/17 14:58:42 by kbam7            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_HPP
# define CORE_HPP

/*# include <curses.h>
# include <string>
# include <cstdio>
# include <cstdlib>
# include <ctime>
*/

# include "GameEnvironment.hpp"
# include "ModuleController.hpp"
# include <signal.h>

# define MIN_MAP_W    		0
# define MIN_MAP_H    		0
# define MAX_MAP_W    		225
# define MAX_MAP_H    		68
# define DEFAULT_GAME_FPS	60
# define ONE_NANOSEC		1000000000
# define N_MODULES			3

class Core {

	public:
		Core(const unsigned int w, const unsigned int h, const int lib);
		Core(Core const & src);
		Core & operator=(Core const & rhs);
		~Core(void);

		GameEnvironment*	gameData;			/* map array, food, food position */
		ModuleController*	moduleController;	/* load, initialize, manage, uninitialize, unload library */
		const char			*modulePaths[N_MODULES];
		unsigned int		gameFPS;			/* default: 60fps     */
		unsigned int		gameSpeed;			/* gameSpeed = (ONE_NANOSEC / gameFPS) / 100; gameSpeed *= 100; gameSpeed is now rounded to hundreds */

		int     gameLoop(void);
		void	loadNewModule(const char *libPath);

	private:
		Core(void);
		struct sigaction	_oldSIGQUIT;
		struct sigaction    _oldSIGINT;
        struct sigaction    _oldSIGSEGV;

		void	_shutdown(int signal, siginfo_t *info, void *data);

};

#endif /* CORE_HPP */

/*
# include <string>
# include "GameEnvironment.hpp"
# include "Player.hpp"

# define DEFAULT_SPEED	1.0f
# define SPEED_INC		30.0f
# define MAX_SPEED		0.10f
# define MULTINOM_RATE	10

class GraphicsHandler;

typedef enum		e_action
{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PAUSE,
	QUIT,
	LIB1,
	LIB2,
	LIB3
}					t_action;

class Snake
{
public:
	static Snake *		instance;
	GameEnvironment *				GameEnvironment;
	Player				player;
	float				speed;
	bool				paused;
	float				clockCountdown;
	bool				stop;
	GraphicsHandler *	ghandler;

	Snake();
	~Snake();

	void				loadLevel(unsigned, unsigned);
	void				loadLevel(const std::string);
	void				loadLibrary(const std::string);
	void				startLevel();
	void				gameOver();
	void				generateNom();
	void				generateNom(unsigned);
	void				removeNoms();
	void				launch();
	void				update();
	void				handleAction();
	void				dump(bool = false) const;
};

#endif

*/