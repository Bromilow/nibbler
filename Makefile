# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/23 08:55:42 by dmather           #+#    #+#              #
#    Updated: 2017/05/28 09:15:26 by kbamping         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_retro
NC			= \033[0m
CR			= \033[31m
CB			= \033[34m
CP			= \033[38;5;128m
CY			= \033[33m
FLAGS		= -Wall -Wextra -Werror -lncurses -g3

SRCS		=	main.cpp		\
				Player.cpp		\
				GameObject.cpp	\
				Bullet.cpp		\
				Entity.cpp

all: $(NAME)

$(NAME):
	@clang++ $(FLAGS) $(SRCS) -o $(NAME)
#	@echo "$(CR)Terminal Broken!$(NC)"
#	@sleep 2
#	@echo "Just Kidding ;)"
#	@sleep 1
	@echo "$(CB)$(NAME) ==> Made '$(NAME)'$(NC)"

clean:
	@rm -f $(NAME)
	@echo "$(CR)$(NAME) ==> Removed '$(NAME)'$(NC)"

fclean: clean

re: clean all
