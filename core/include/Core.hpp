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

class Core {

	public:
		Core(const unsigned int w, const unsigned int h, const int lib);
		Core(Core const & src);
		Core & operator=(Core const & rhs);
		~Core(void);

		GameEnvironment*	gameData;			/* map array, food, food position */
		ModuleController*	moduleController;	/* load, initialize, manage, uninitialize, unload library */
		const char			*modulePaths[N_MODULES];

		int     gameLoop(void);
		void	loadNewModule(const char *libPath);

	private:
		Core(void);
		struct sigaction	_oldSIGQUIT;
		struct sigaction    _oldSIGINT;
        struct sigaction    _oldSIGSEGV;
};

void	_shutdown(int signal, siginfo_t *info, void *data);

#endif /* CORE_HPP */