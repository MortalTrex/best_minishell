# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2024/12/06 22:59:41 by dagudelo         ###   ########.fr        #
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

SRCS = srcs/main.c\
	srcs/builtins/builtins_launch.c\
	srcs/builtins/builtins_utils.c\
	srcs/builtins/echo.c\
	srcs/builtins/env.c\
	srcs/builtins/pwd.c\
	srcs/builtins/unset.c\
	srcs/builtins/export.c\
	srcs/builtins/exit.c\
	srcs/builtins/cd.c\
	srcs/exec/exec_cases.c\
	srcs/exec/exec_core.c\
	srcs/exec/exec_read.c\
	srcs/exec/exec_heredoc.c\
	srcs/exec/exec_redirs.c\
	srcs/exec/utils.c\
	srcs/lexing/tokenize_check.c\
	srcs/lexing/tokenize_malloc_1.c\
	srcs/lexing/tokenize_malloc_2.c\
	srcs/lexing/tokenize_parsing.c\
	srcs/lexing/tokenize_print.c\
	srcs/lexing/tokenize.c\
	srcs/lexing/append.c\
	srcs/lexing/stack_utils.c\
	srcs/lexing/grammar_check.c\
	srcs/parsing/ast.c\
	srcs/parsing/create_node.c\
	srcs/parsing/expand_and_clean.c\
	srcs/parsing/expand_env_var.c\
	srcs/parsing/get_clean_argv.c\
	srcs/parsing/handle_quotes.c\
	srcs/parsing/parse_s_command.c\
	srcs/parsing/remove_quotes.c\
	srcs/parsing/shell_list_expand_1.c\
	srcs/parsing/shell_list_expand_2.c\
	srcs/parsing/shell_list_malloc_1.c\
	srcs/parsing/shell_list_malloc_2.c\
	srcs/parsing/shell_list_malloc_3.c\
	srcs/parsing/shell_list_print.c\
	srcs/parsing/shell_list.c\
	srcs/parsing/utils_parser.c\
	srcs/signal/signal.c\
	srcs/utils/errors.c\
	srcs/utils/free.c\

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
	@echo -e "$(INDI)The best minishell in the world is compiled!$(RESET)"

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
