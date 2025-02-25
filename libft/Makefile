# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 11:20:05 by mmiilpal          #+#    #+#              #
#    Updated: 2025/02/25 16:07:07 by mmiilpal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
			ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c ft_putendl_fd.c ft_striteri.c \
			get_next_line.c ft_printf.c ft_format_print.c ft_free_tab.c\
			ft_isspace.c ft_strcmp.c ft_lstadd_back.c ft_lstadd_front.c\
			ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
			ft_lstnew.c ft_lstsize.c ft_atoi_long.c ft_strndup.c\

BONUS_SRCS	=   ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS    = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
HDRS    = libft.h
NAME    = libft.a
RM  = rm -rf
GCC = gcc
AR  = ar -crs
FLAGS   = -Wall -Wextra -Werror

NO_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
CYAN = \033[0;96m
RESET	=	\033[00m

.c.o:
		@$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)
#@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"

$(NAME):	$(OBJS) $(HDRS)
			@$(AR) $(NAME) $(OBJS)
# @echo "$(GREEN)libft compiled!$(RESET)"

all:	$(NAME)

bonus:	$(OBJS) $(BONUS_OBJS) $(HDRS)
		@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
#@echo "$(GREEN)libft BONUS compiled!$(RESET)"

re:		clean fclean all
#@echo "$(GREEN)libft RE compiled!$(RESET)"

clean:
		@$(RM) $(OBJS) $(BONUS_OBJS)
#@echo "$(BLUE)libft object files cleaned!$(RESET)"


fclean:
		@$(RM) $(NAME)
#@echo "$(CYAN)libft executable files cleaned!$(RESET)"
.PHONY:
		all clean fclean re bonus
