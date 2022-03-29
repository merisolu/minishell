# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 16:25:00 by jumanner          #+#    #+#              #
#    Updated: 2022/03/25 13:21:58 by jumanner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

SRCSDIR = ./src
INCLUDESDIR = ./include

FILES = ft_tolower.c ft_toupper.c \
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
		ft_free_array.c ft_rev_array.c ft_free_null_array.c ft_null_array_len.c \
		ft_dstchr.c \
		ft_get_next_line.c \
		ft_file.c ft_dir.c ft_path.c ft_path_validity.c

SRCS = $(patsubst %, $(SRCSDIR)/%, $(FILES))
OBJS = $(FILES:.c=.o)

PRINTF_FILES = ft_printf.c \
		component_parsers.c \
		dispatchers.c \
		text_handlers.c \
		num_handlers.c unum_handlers.c \
		float_handlers.c float_helpers.c double_writer.c double_writer_helpers.c \
		hex_handlers.c oct_handlers.c binary_handlers.c base36_handlers.c \
		written_chars_handler.c \
		width.c color.c

PRINTF_SRCSDIR = ./ft_printf/srcs
PRINTF_INCLUDESDIR = ./ft_printf/includes

PRINTF_SRCS = $(patsubst %, $(PRINTF_SRCSDIR)/%, $(PRINTF_FILES))
PRINTF_OBJS = $(PRINTF_FILES:.c=.o)

$(NAME):
	gcc -O3 -Wall -Wextra -Werror -I $(INCLUDESDIR) -I $(PRINTF_INCLUDESDIR) -c $(SRCS) $(PRINTF_SRCS)
	ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
