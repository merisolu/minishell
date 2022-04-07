# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 16:25:00 by jumanner          #+#    #+#              #
#    Updated: 2022/04/07 09:38:51 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

INCLUDE_DIR = ./include

SRC_FILES = ft_tolower.c ft_toupper.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c \
		ft_strlen.c ft_strdup.c ft_strnew.c ft_strdel.c ft_strclr.c ft_strncmp.c ft_strcmp.c \
		ft_strncpy.c ft_strcpy.c ft_strncat.c ft_strcat.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strstr.c ft_strnequ.c ft_strequ.c \
		ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
		ft_strtolower.c ft_strtoupper.c \
		ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memichr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
		ft_putchar_fd.c ft_putcharn_fd.c ft_putstr_fd.c ft_putstrn_fd.c ft_putendl_fd.c ft_putchar.c ft_putcharn.c ft_putstr.c ft_putstrn.c ft_putendl.c \
		ft_putnbr_fd.c ft_putnbr.c ft_putnbrn_fd.c ft_putnbrn.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
		ft_itoa.c ft_itoa_base.c ft_atoi.c \
		ft_getdigits.c ft_getdigits_base.c ft_getnumlen.c ft_getsign.c \
		ft_bzero.c ft_realloc.c \
		ft_sort.c \
		ft_max.c ft_min.c \
		ft_abs.c ft_abs_float.c \
		ft_pow.c \
		ft_fmod.c ft_modf.c ft_frexp.c ft_round.c ft_getexponent.c ft_getmantissa.c ft_isinfinite.c ft_isnan.c \
		ft_is_whitespace.c \
		ft_free_array.c ft_rev_array.c ft_null_array.c ft_null_array_properties.c ft_null_array_free.c \
		ft_dstchr.c \
		ft_get_next_line.c \
		ft_file.c ft_dir.c ft_path.c ft_path_validity.c
SRC_DIR = ./src
SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

TEMP_LIB = .templib

GCC_FLAGS = -O3 -Wall -Wextra -Werror

$(NAME): $(OBJS) $(FT_PRINTF_LIB)
	ar rcs $(TEMP_LIB) $(OBJS)
	libtool -static -o $(NAME) $(TEMP_LIB) $(FT_PRINTF_LIB)
	rm -f $(TEMP_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(GCC_FLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(FT_PRINTF_LIB):
	make -C $(FT_PRINTF_DIR)
