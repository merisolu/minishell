# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/03/29 12:13:47 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ./libft
LIB_INCLUDE_DIR = ./libft/include

SRCS_FILES = main.c lexer.c parser.c token.c token_list.c debug.c
SRCS_DIR = ./src
SRCS := $(patsubst %, $(SRCS_DIR)/%, $(SRCS_FILES))

OBJS_DIR = ./obj
OBJS := $(patsubst %, $(OBJS_DIR)/%, $(SRCS_FILES:.c=.o))

GCC_FLAGS = -g -Wall -Wextra -Werror

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) -L $(LIB_DIR) -lft $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

.PHONY: all clean fclean re run

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -r $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)
