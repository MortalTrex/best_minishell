# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2024/08/25 17:54:57 by mmiilpal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g
LIBFTDIR = libft/
OBJ_DIR = objs/
INC = -Iinc -Isrcs

LIBS = -L$(LIBFTDIR) -lft

SRCS = srcs/main.c srcs/builtins/echo.c\
	srcs/pipex.c \
	srcs/lexing/lexer.c srcs/lexing/ft_split_ms.c \
	srcs/errors.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))


INDI	=	\033[38;5;213m
GREEN	=	\033[0;32m
RESET	=	\033[00m

all: create_dirs $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -s -C $(LIBFTDIR)
	$(CC) $(FLAGS) -lreadline -lm $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(INDI)The best minishell on the world compiled!$(RESET)"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -s -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean create_dirs re



