# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/29 11:15:59 by akaplyar          #+#    #+#              #
#    Updated: 2017/10/17 18:52:49 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = ./includes/corewar.h
LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a
MAKE_LIB = $(MAKE) -C $(LIB_PATH)
ASM_PATH = ./assembler/
MAKE_ASM = $(MAKE) -C $(ASM_PATH)

CC = @gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re

OBJECT =	main.o war_control.o utils.o game.o instruction_read.o\
			process_control.o instruction_control.o params_control.o\
			text_out.o operations.o operations2.o operations3.o operations4.o
VM_OBJ =		$(addprefix ./src/,$(OBJECT))

VISUAL =	init.o utils.o cycle_control.o field_control.o player_control.o
V_OBJ =		$(addprefix ./visual/,$(VISUAL))

OBJ = ${VM_OBJ} ${V_OBJ}
NAME = corewar

all:  asm $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I $(HEADER) $(LIB) -lncurses -lpanel
	@printf "\x1B[32m\0%s created\x1B[0m\0\n" ${NAME}

.c.o:
	@printf "\x1B[32m\0Compile %s\x1B[0m\0\n" $<
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

asm:
	$(MAKE_ASM)

clean:
	$(MAKE_ASM) clean
	@rm -rf $(OBJ) $(V_OBJ)
	@printf "\x1B[31m\0%s objects cleared\x1B[0m\0\n" ${NAME}

fclean: clean
	$(MAKE_ASM) fclean
	@rm -rf $(NAME)
	@printf "\x1B[31m\0%s deleted\x1B[0m\0\n" ${NAME}

re: fclean all
