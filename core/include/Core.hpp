/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 15:42:18 by kbam7             #+#    #+#             */
/*   Updated: 2017/06/23 19:19:22 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_HPP
# define CORE_HPP

# include "GameEnvironment.hpp"
# include "ModuleController.hpp"
# include <signal.h>
# include <time.h>
# include <sys/time.h>

# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif

class Core {
	public:
		Core(const unsigned int w, const unsigned int h, const int lib);
		Core(Core const & src);
		Core & operator=(Core const & rhs);
		~Core(void);

		GameEnvironment*	gameData;
		ModuleController*	moduleController;
		const char			*modulePaths[N_MODULES];

		int     gameLoop(void);
		void	loadNewModule(const char *libPath);
		int     handleAction(t_input action);
		void	current_utc_time(struct timespec *ts);

	private:
		Core(void);
		struct sigaction	_oldSIGQUIT;
		struct sigaction    _oldSIGINT;
        struct sigaction    _oldSIGSEGV;
};

void	_shutdown(int signal, siginfo_t *info, void *data);

#endif /* CORE_HPP */