# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 03:17:50 by kbam7             #+#    #+#              #
#    Updated: 2017/06/09 13:04:26 by kbam7            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-- Names of items to make
PROG		= nibbler
MOD_MENU	= mod_MainMenu.so
MOD_NCRS	= mod_NCurses.so

#-- Core Program
SRCS		= core/src/main.cpp core/src/GameLoop.cpp
OBJS		= $(SRCS:%.cpp=%.o)

#-- MainMenu Module
MOD_MENU_SRCS	= main_menu/main_menu.cpp 
MOD_MENU_OBJS	= $(MOD_MENU_SRCS:%.cpp=%.o)

#-- NCurses Module
MOD_NCRS_SRCS	= module_1/ModNCurses.cpp 
MOD_NCRS_OBJS	= $(MOD_NCRS_SRCS:%.cpp=%.o)

#-- OpenGL Module
#-- SDL Module

#-- Compiler, libs, flags
INCLUDES	= -I core/include
WFLAGS		= -Wall -Wextra -Werror -g
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
main_menu/%.o : main_menu/%.cpp
	@$(CXX) $(WFLAGS) -fPIC -c $< -o $@
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32m>>\033[0m $@"

$(MOD_MENU): $(MOD_MENU_OBJS)
	@$(CXX) -lncurses -shared -o $(MOD_MENU) $(MOD_MENU_OBJS)
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mCOMPILED\033[0m"

#-- NCurses Module
module_1/%.o : module_1/%.cpp
	@$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@
	@echo "\033[01;36m$(MOD_NCRS) -- \033[00;32m>>\033[0m $@"

$(MOD_NCRS): $(MOD_NCRS_OBJS)
	@$(CXX) $(CXXFLAGS) -lncurses -shared -o $(MOD_NCRS) $(MOD_NCRS_OBJS)
	@echo "\033[01;36m$(MOD_NCRS) -- \033[00;32mCOMPILED\033[0m"

#-- OpenGL Module
#-- SDL Module

#-- General rules
clean:
	@rm -f $(OBJS)
	@rm -f $(MOD_MENU_OBJS)
	@rm -f $(MOD_NCRS_OBJS)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED OBJECT FILES\033[0m"
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mREMOVED OBJECT FILES\033[0m"
	@echo "\033[01;36m$(MOD_NCRS) -- \033[00;32mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(PROG)
	@rm -f $(MOD_MENU)
	@rm -f $(MOD_NCRS)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@echo "\033[01;36m$(MOD_MENU) -- \033[00;32mREMOVED SHARED OBJECT\033[0m"
	@echo "\033[01;36m$(MOD_NCRS) -- \033[00;32mREMOVED SHARED OBJECT\033[0m"

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mREMOVED EXECUTABLE\033[0m"
	@$(MAKE) -s all
	./$(PROG) 640 480
