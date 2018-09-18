# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmkhwana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/18 11:11:05 by lmkhwana          #+#    #+#              #
#    Updated: 2018/09/18 11:36:04 by lmkhwana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRC =	cd_command.c \
		echo_command.c \
		execute_command.c \
		exit_commands.c \
		main.c \
		pwd_command.c \
		run.c \
		setenv_command.c \
		unsetenv_command.c \
		utilities.c

L_DIR = libft

LIBFT = $(L_DIR)/libft.a

all : $(NAME)

$(NAME):
	@echo "Building a minishell..."
	@make -C libft re
	@gcc -Wall -Wextra -Werror $(SRC) $(LIBFT) -o $(NAME)

clean:
	@echo "Cleaning up *.o files..."
	@make -C $(L_DIR) clean

fclean: clean
	@echo "Removing *.a files and executable..."
	@make -C $(L_DIR) fclean
	@rm -rf $(NAME)

re: fclean all
