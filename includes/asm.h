/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 17:10:17 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 17:10:32 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ASM_H
# define COREWAR_ASM_H

# include "op.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>

# define NAME_LEN PROG_NAME_LENGTH
# define COMM_LEN COMMENT_LENGTH
# define INP_ERR 1
# define MLC_ERR 2
# define FILE_ERR 3
# define OPEN_ERR 4
# define NAME_ERR 5

# define SYNTAX 10
# define NO_LINE 11
# define NO_NAME 12
# define NO_QUOTE_1 13
# define NO_QUOTE_2 14
# define NAME_TWICE 15
# define NAME_LONG 16
# define COMM_LONG 17
# define END_LINE 18

# define NO_COMM 20
# define INV_CHAR 21
# define NO_ARGS 22
# define INV_COMM 23
# define INV_ARG 24
# define INV_REG 25
# define INV_COUNT 26
# define INV_LABEL 28
# define INV_TYPE 128

typedef struct	s_op
{
	char		*name;
	int			argc;
	int			args[3];
	char		opcode;
	char		octal;
	char		dir;
}				t_op;

typedef struct	s_ins
{
	int			line;
	char		*types;
	char		*label;
	char		**args;
	t_op		*comm;
}				t_ins;

typedef struct	s_out
{
	int			*val;
	short		*args;
	char		opcode;
	short		octal;
	size_t		pos;
	size_t		size;
}				t_out;

typedef struct	s_asm
{
	int			a;
	int			i;
	int			j;
	int			len;
	char		*name;
	char		*comm;
	char		*file;
	char		**input;
	size_t		name_len;
	size_t		comm_len;
	size_t		size_out;
	size_t		magic;
	t_list		*tmp;
	t_ins		**ins;
	t_out		**out;
}				t_asm;

int				asm_new_ins(const void *data, size_t size, t_list **begin);
void			asm_encode(t_asm *as);
void			asm_sub_args(t_ins *ins);
void			asm_find_name(t_asm *as);
void			asm_find_comment(t_asm *as);
void			asm_find_command(t_asm *as);
void			asm_struct_commands(t_asm *as);
void			asm_errors(int err, char *str);
void			asm_check_label(t_asm *as, char c);
void			asm_print_out(t_asm *as, char *file);
void			asm_line_err(t_asm *as, int err, char *str);
void			asm_command_err(t_asm *as, int err, char *str);
void			asm_check_args(t_asm *as, t_ins *ins, char *str);
char			*asm_not_empty_line(t_asm *as, char *line);

t_op			g_op[16];
#endif
