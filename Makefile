# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 13:39:46 by mmiilpal          #+#    #+#              #
#    Updated: 2025/02/28 18:58:12 by mmiilpal         ###   ########.fr        #
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
	srcs/builtins/env_set_free.c\
	srcs/builtins/env_init.c\
	srcs/builtins/env_utils.c\
	srcs/builtins/echo.c\
	srcs/builtins/env.c\
	srcs/builtins/pwd.c\
	srcs/builtins/unset.c\
	srcs/builtins/export.c\
	srcs/builtins/exit.c\
	srcs/builtins/cd.c\
	srcs/builtins/export_utils.c\
	srcs/exec/exec_cmd.c\
	srcs/exec/exec_open.c\
	srcs/exec/exec.c\
	srcs/exec/exec_redirs.c\
	srcs/exec/exec_fds_utils.c\
	srcs/exec/shlvl.c\
	srcs/exec/utils.c\
	srcs/lexing/expand.c\
	srcs/lexing/grammar_check.c\
	srcs/lexing/heredoc.c\
	srcs/lexing/lex.c\
	srcs/lexing/redir_types.c\
	srcs/lexing/remove_quotes.c\
	srcs/lexing/string_utils.c\
	srcs/lexing/syntax_check.c\
	srcs/parsing/create_command.c\
	srcs/parsing/parse.c\
	srcs/parsing/redirs_utils.c\
	srcs/parsing/tokens_utils.c\
	srcs/signal/signal.c\
	srcs/utils/errors.c\
	srcs/utils/stack_utils.c\
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
