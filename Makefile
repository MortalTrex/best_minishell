# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2024/08/29 16:23:28 by rbalazs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
LIBFTDIR = libft/
OBJ_DIR = build/
INC = -Iinc -Isrcs
LDLIBS = -lreadline

LIBS = -L$(LIBFTDIR) -lft

SRCS = srcs/main.c srcs/builtins/echo.c\
	srcs/utils/pipex.c \
	srcs/utils/errors.c\
	srcs/lexing/lexer.c\
	srcs/lexing/tokenize.c\
	srcs/lexing/stack_utils.c\
	srcs/lexing/grammar_check.c\
	srcs/builtins/env.c\
	srcs/builtins/pwd.c

INDI	=	\033[38;5;213m
GREEN	=	\033[0;32m
RESET	=	\033[00m

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

all: create_dirs $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s -C $(LIBFTDIR)
	@$(CC) $(FLAGS) -lm $(OBJS) $(LIBS) -o $(NAME) $(LDLIBS)
	@echo "$(INDI)The best minishell on the world is compiled!$(RESET)"

create_dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean create_dirs re



