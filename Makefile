# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 15:13:41 by kjimenez          #+#    #+#              #
#    Updated: 2023/11/19 14:31:01 by kjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_BIN		:= bin
DIR_OBJ		:= build

NAME		:= $(DIR_BIN)/push_swap

SRC			:= push_swap.c indexing.c markup.c markup_head.c single_actions.c \
				multiple_actions.c move.c print_moveset.c simplify_moveset.c stack_b_to_a.c \
				stack_a_align.c stack_a.c stack_a_to_b.c stack_boundaries.c \
				markup_builder.c parsing_utils.c parsing.c
OBJ			:= $(addprefix $(DIR_OBJ)/,$(SRC:c=o))

LIBS_PATH	:= libs
LIBFT_PATH	:= $(LIBS_PATH)/libft

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror -I$(LIBFT_PATH)/include -Iinclude -g
LDFLAGS		:= -L$(LIBFT_PATH)/bin -lft_list -lft_stdlib -lft_stdio -lft_string -lft_ctype -g

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

vpath %.c src:src/markup:src/move:src/stack_b_to_a:src/actions:src/parsing
