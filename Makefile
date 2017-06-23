# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 03:17:50 by kbam7             #+#    #+#              #
#    Updated: 2017/06/23 13:52:13 by kbamping         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-- Names of items to make
PROG		= nibbler
MOD_MENU	= lib0_MainMenu.so
MOD1		= lib1_NCurses.so
MOD2		= lib2_NCurses.so
MOD3		= lib3_NCurses.so

#-- Core Program
CORE_SRC	= core/src
SRCS		=	$(CORE_SRC)/main.cpp $(CORE_SRC)/GameEnvironment.cpp $(CORE_SRC)/ModuleController.cpp $(CORE_SRC)/Core.cpp
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
all: $(MOD_MENU) $(MOD1) $(MOD2) $(MOD3) $(PROG)

#-- Core Program
$(CORE_SRC)/%.o : $(CORE_SRC)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "\033[01;36m$(PROG) \t\t-- \033[00;32m>>\033[0m $@"

$(PROG): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -ldl -o $(PROG)
	@echo "\033[01;36m$(PROG) \t\t-- \033[00;32mCOMPILED\033[0m\n"

#-- MainMenu Module
$(MOD_MENU) :
	@$(MAKE) -s -C main_menu/

#-- NCurses Module
$(MOD1):
	@$(MAKE) -s -C module_1/

#-- NCurses Module 2
$(MOD2):
	@$(MAKE) -s -C module_2/

#-- NCurses Modue 3
$(MOD3):
	@$(MAKE) -s -C module_3/

#-- General rules
clean:
	@rm -f $(OBJS)
	@rm -f ./outerr.txt
	@echo "\033[01;36m$(PROG) \t\t-- \033[00;32mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) \t\t-- \033[00;32mREMOVED EXECUTABLE\033[0m\n"
	@$(MAKE) -s -C main_menu/ fclean
	@$(MAKE) -s -C module_1/ fclean
	@$(MAKE) -s -C module_2/ fclean
	@$(MAKE) -s -C module_3/ fclean

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) \t\t-- \033[00;32mREMOVED EXECUTABLE\033[0m\n"
	@$(MAKE) -s all
	./$(PROG) 30 30 2> outerr.txt

run_valgrind:
	valgrind --leak-check=full --show-reachable=yes ./nibbler 17 30