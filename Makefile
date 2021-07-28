# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2021/07/28 17:10:00 by tmatias          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Wextra -Werror 

SRC = pipex.c\
		main.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = pipex.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes

LIBFT_HDR = -I./libft/inc
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: check_libft $(NAME) $(HDRS)
	@echo "Compilation successful"

$(NAME): project $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(OBJS) $(LIB_BINARY) -o $@
	@echo "\t[ \033[0;32m✔\033[0m ] pipex executable"

check_libft:
	@echo "Checking libft..."
	@make -C libft

project:
	@echo "Checking project..."

$(OBJSFD):
	@mkdir $@
	@echo "\t[ $(GREEN)✔$(NONE) ] objs/ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"

clean:
	@rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
	@make -C ./libft fclean

re: fclean all

.PHONY: all check_libft project clean fclean re