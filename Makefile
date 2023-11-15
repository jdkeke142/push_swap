# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 15:13:41 by kjimenez          #+#    #+#              #
#    Updated: 2023/11/15 19:53:42 by kjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_BIN		:= bin
DIR_OBJ		:= build

NAME		:= $(DIR_BIN)/push_swap

SRC			:= push_swap.c indexing.c markup.c markup_head.c actions.c
OBJ			:= $(addprefix $(DIR_OBJ)/,$(SRC:c=o))

LIBS_PATH	:= libs
LIBFT_PATH	:= $(LIBS_PATH)/libft

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror -I$(LIBFT_PATH)/include -Iinclude -g
LDFLAGS		:= -L$(LIBFT_PATH)/bin -lft_list -lft_stdlib -lft_stdio -lft_string -g -pg

GIT			:= git

MKDIR		:= mkdir -p

INIT_SUB	:= $(shell $(GIT) submodule init)
UPDATE_SUB	:= $(shell $(GIT) submodule update)
BUILD_LIBFT	:= $(shell $(MAKE) -C $(LIBFT_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(DIR_OBJ)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

vpath %.c src:src/markup
