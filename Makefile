# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 03:17:50 by kbam7             #+#    #+#              #
#    Updated: 2017/06/12 16:17:09 by kbam7            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-- Names of items to make
PROG		= nibbler
MOD_MENU	= mod_MainMenu.so
MOD_NCRS	= mod_NCurses.so

#-- Core Program
SRCS		= core/src/main.cpp core/src/GameEnvironment.cpp core/src/ModuleController.cpp
OBJS		= $(SRCS:%.cpp=%.o)

#-- OpenGL Module
#-- SDL Module

#-- Compiler, libs, flags
INCLUDES	= -I core/include
WFLAGS		= -Wall -Wextra -Werror -g3 -std=c++11
CXX			= clang++
CXXFLAGS	= $(WFLAGS) $(INCLUDES)

.PHONY: clean fclean re run

#-- RULES --#
all: $(PROG) $(MOD_MENU) $(MOD_NCRS)

#-- Core Program
core/src/%.o : core/src/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "\033[01;36m$(PROG) -- \033[00;32m>>\033[0m $@"

$(PROG): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -ldl -o $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mCOMPILED\033[0m"

#-- MainMenu Module
$(MOD_MENU) :
	@$(MAKE) -s -C main_menu/

#-- NCurses Module
$(MOD_NCRS):
	@$(MAKE) -s -C module_1/

#-- OpenGL Module
#-- SDL Module

#-- General rules
clean:
	@rm -f $(OBJS)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED OBJECT FILES\033[0m"
	@$(MAKE) -s -C main_menu/ clean
	@$(MAKE) -s -C module_1/ clean

fclean: clean
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@$(MAKE) -s -C main_menu/ fclean
	@$(MAKE) -s -C module_1/ fclean

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@$(MAKE) -s all
	./$(PROG) 640 480
