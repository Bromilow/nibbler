# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbam7 <kbam7@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 03:17:50 by kbam7             #+#    #+#              #
#    Updated: 2017/06/16 12:22:58 by kbam7            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB			= lib3_NCurses.so

SRCS		= Module.cpp
OBJS		= $(SRCS:%.cpp=%.o)

INCLUDES	= -I ../core/include
CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++11 -fPIC
LDFLAGS		= -shared -fPIC -lncurses

.PHONY: clean fclean re

#-- RULES --#
all: $(LIB)

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
