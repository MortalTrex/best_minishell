# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2024/07/15 12:06:33 by rbalazs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g 
LIBFTDIR = libft/
OBJ_DIR = objs/
INC = -Iincs

LIBS = -L$(LIBFTDIR) -lft

SRCS = srcs/main.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))


INDI	=	\033[38;5;213m
GREEN	=	\033[0;32m
RESET	=	\033[00m

all: create_dirs $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -s -C $(LIBFTDIR)
	$(CC) $(FLAGS) -lreadline -lm $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(INDI)The best minishell on the world compiled!$(RESET)"

create_dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s -C $(LIBFTDIR) fclean

re: clean all

.PHONY: all clean fclean create_dirs re



