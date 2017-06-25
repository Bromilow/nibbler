# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbromilo <rbromilo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 03:17:50 by kbam7             #+#    #+#              #
#    Updated: 2017/06/25 10:35:29 by rbromilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB			= lib4_SDL.so

SRCS		= Module.cpp
OBJS		= $(SRCS:%.cpp=%.o)

INCLUDES	= -I ../core/include $(SDL2I)
CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++11 -fPIC
LDFLAGS		= $(SDL2L) -shared

SDL2I_		= $(shell sdl2-config --cflags | cut -d" " -f1 | sed 's/-I//g')
SDL2L_		= $(shell sdl2-config --libs | cut -d" " -f1 | sed 's/-L//g')

SDL2I		= $(shell sdl2-config --cflags)
SDL2L		= $(shell sdl2-config --libs)

INSTALLED	= $(findstring include/SDL2, $(SDL2I_))

.PHONY: all clean fclean re

#/bin/sh: sdl2-config: command not found
#/nfs/zfs-student-6/users/rbromilo/.brew/include/SDL2

#-- RULES --#
all: check $(LIB)

check:
ifeq ($(INSTALLED),)
	echo "NOOOPE!!!!!!!!!!"
	echo "\033[01;36m$(LIB) \t-- \033[00;32minstalling and linking sdl2\033[0m\n"
	brew install sdl2
	brew link sdl2
else
	echo "YESS!!"
endif

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[01;36m$(LIB) \t-- \033[00;32m>>\033[0m $@"

$(LIB): $(OBJS)
	@$(CXX) $(LDFLAGS) -o $(LIB) $(OBJS)
	@echo "\033[01;36m$(LIB) \t-- \033[00;32mCOMPILED\033[0m\n"

clean:
	@rm -f $(OBJS)
	@echo "\033[01;36m$(LIB) \t-- \033[00;32mREMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(LIB)
	@echo "\033[01;36m$(LIB) \t-- \033[00;32mREMOVED EXECUTABLE\033[0m\n"

re: fclean all