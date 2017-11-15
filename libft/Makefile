# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/29 11:15:59 by akaplyar          #+#    #+#              #
#    Updated: 2017/04/30 16:31:49 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS =	ft_printf.h libft.h hsv.h
HEADER =	$(addprefix ./includes/,$(HEADERS))
PRINTF_PATH = ./ft_printf/

CC = @gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re

OBJECT =	ft_tabcount.o ft_tabdel.o hsv.o hsv_colors.o stack.o queue.o

INT_O =		ft_abs.o ft_int_sort.o ft_intlen.o ft_atoi.o ft_atoi_base.o\
			ft_bit_swap.o
INT_OBJ =	$(addprefix ./int/,$(INT_O))

LIST_O =	ft_lstnew.o ft_lstadd.o ft_lstmap.o ft_lstiter.o ft_lstdelone.o\
			ft_lstdel.o ft_lstcount.o ft_lst_sort.o ft_lstnew_struct.o\
			ft_lst_push_back.o
LIST_OBJ =	$(addprefix ./list/,$(LIST_O))

CHAR_O =	ft_toupper.o ft_tolower.o ft_isprint.o ft_isalnum.o\
			ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isspace.o
CHAR_OBJ =	$(addprefix ./char/,$(CHAR_O))

MEM_O =		ft_memcpy.o ft_memcmp.o ft_memchr.o ft_memmove.o ft_memdel.o\
			ft_memset.o ft_memccpy.o ft_memalloc.o ft_bzero.o
MEM_OBJ =	$(addprefix ./memory/,$(MEM_O))

STR_O = 	ft_strdel.o ft_strclr.o ft_striter.o ft_strcat.o ft_strchr.o\
			ft_strstr.o ft_strrchr.o ft_strstr.o ft_strcmp.o ft_strncmp.o\
			ft_strlcat.o ft_strdup.o ft_strlen.o ft_strncpy.o ft_strnstr.o\
			ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o\
			ft_strmake.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_strnew.o\
			ft_strcpy.o ft_strsub.o ft_strconcat.o ft_strcount.o ft_strncat.o\
			ft_strcapitalizer.o ft_strisdigit.o ft_strrev.o ft_realloc.o\
			ft_llitoa.o ft_space_skip.o
STR_OBJ =	$(addprefix ./string/,$(STR_O))

READ_O =	get_next_line.o	ft_readfile.o
READ_OBJ =	$(addprefix ./reader/,$(READ_O))

PRINT_O =	ft_putstr.o ft_putnbr.o ft_putendl.o ft_putchar_fd.o ft_putstr_fd.o\
			ft_putendl_fd.o ft_putnbr_fd.o ft_putchar.o
PRINT_OBJ =	$(addprefix ./printer/,$(PRINT_O))

PRINTF_O =	ft_printf.o help_int.o parse_int.o parse_str.o finder.o\
			type_finder.o helper.o parse_wstr.o parse_brackets.o
P_OBJ =		$(addprefix $(PRINTF_PATH),$(PRINTF_O))

OBJ =		${OBJECT} ${INT_OBJ} ${LIST_OBJ} ${P_OBJ} ${STR_OBJ}
OBJ +=		${MEM_OBJ} ${CHAR_OBJ} ${READ_OBJ} ${PRINT_OBJ}

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(HEADER)
	@ranlib $(NAME)
	@echo "\n\x1B[32m\0lib_created\x1B[0m\0"

.c.o:
	@printf "\x1B[32m\0Compile %s\x1B[0m\0                                \r" $<
	@$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@rm -rf $(OBJ)
	@echo "\x1B[31m\0lib objects cleared\x1B[0m\0"

fclean: clean
	@rm -rf $(NAME)
	@echo "\x1B[31m\0lib deleted\x1B[0m\0"

re: fclean all
