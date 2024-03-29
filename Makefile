# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 15:13:41 by kjimenez          #+#    #+#              #
#    Updated: 2023/11/21 15:36:49 by kjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_BIN			:= bin
DIR_OBJ			:= build

NAME			:= $(DIR_BIN)/push_swap
CHECKER_NAME	:= $(DIR_BIN)/checker

SRC				:= push_swap.c indexing.c markup.c markup_head.c actions.c actions_rotate.c \
					move.c print_moveset.c stack_b_to_a.c stack_a_align.c prepare_stack_a.c\
					stack_a.c stack_a_to_b.c stack_boundaries.c moveset.c prepare_stack_b.c \
					markup_builder.c parsing_utils.c parsing.c
CHECKER_SRC		:= actions.c actions_rotate.c indexing.c parsing_utils.c parsing.c checker.c
OBJ				:= $(addprefix $(DIR_OBJ)/,$(SRC:c=o))
CHECKER_OBJ		:= $(addprefix $(DIR_OBJ)/,$(CHECKER_SRC:c=o))

LIBS_PATH		:= libs
LIBFT_PATH		:= $(LIBS_PATH)/libft

CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -I$(LIBFT_PATH)/include -Iinclude -g
LDFLAGS			:= -L$(LIBFT_PATH)/bin -lft_list -lft_stdlib -lft_stdio -lft_string -lft_ctype -g

GIT				:= git

MKDIR			:= mkdir -p

INIT_SUB		:= $(shell $(GIT) submodule init)
UPDATE_SUB		:= $(shell $(GIT) submodule update)
BUILD_LIBFT		:= $(shell $(MAKE) -C $(LIBFT_PATH))

all: push_swap checker

push_swap: $(NAME)

checker: $(CHECKER_NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(CHECKER_NAME): $(CHECKER_OBJ)
	$(CC) $(CHECKER_OBJ) $(LDFLAGS) -o $(CHECKER_NAME)

$(DIR_OBJ)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(CHECKER_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME) $(CHECKER_NAME)

.PHONY: all push_swap checker clean fclean re

vpath %.c src:src/markup:src/move:src/stack_b_to_a:src/parsing:src/actions
