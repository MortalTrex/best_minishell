# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2024/09/12 17:55:36 by rbalazs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g3
LIBFTDIR = libft/
OBJ_DIR = build/
INC = -Iinc -Isrcs
LDLIBS = -lreadline

LIBS = -L$(LIBFTDIR) -lft

SRCS = srcs/main.c srcs/builtins/echo.c\
	srcs/utils/pipex.c \
	srcs/utils/errors.c\
	srcs/lexing/tokenize.c\
	srcs/lexing/append.c\
	srcs/lexing/stack_utils.c\
	srcs/lexing/lexer.c\
	srcs/lexing/grammar_check.c\
	srcs/builtins/env.c\
	srcs/builtins/pwd.c\
	srcs/parsing/parser.c\
	srcs/parsing/ast.c\
	srcs/builtins/export.c

INDI	=	\033[38;5;213m
GREEN	=	\033[0;32m
RESET	=	\033[00m

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

all: check $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s -C $(LIBFTDIR)
	@$(CC) $(FLAGS) -lm $(OBJS) $(LIBS) -o $(NAME) $(LDLIBS)
	@echo "$(INDI)The best minishell in the world is compiled!$(RESET)"

check:
	@if [ -f $(NAME) ]; then \
		latest_obj=$$(find $(OBJ_DIR) -type f -name '*.o' -newer $(NAME) | wc -l); \
		latest_src=$$(find srcs -type f -name '*.c' -newer $(NAME) | wc -l); \
		if [ "$$latest_obj" -eq 0 ] && [ "$$latest_src" -eq 0 ]; then \
			echo "no updates, using last version of minishell exec"; \
		fi \
	fi

create_dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean create_dirs re check



