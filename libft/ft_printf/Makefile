# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:02:44 by jumanner          #+#    #+#              #
#    Updated: 2022/03/30 14:35:40 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

INCLUDE_DIR = ./include

LIB_DIR = ..
LIB_INCLUDE_DIR = ../include

SRC_FILES = ft_printf.c component_parsers.c dispatchers.c \
			text_handlers.c num_handlers.c unum_handlers.c \
			float_handlers.c float_helpers.c \
			double_writer.c double_writer_helpers.c \
			hex_handlers.c oct_handlers.c binary_handlers.c base36_handlers.c \
			written_chars_handler.c width.c color.c
SRC_DIR = ./src
SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -O3 -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re lib

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
