/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 13:33:59 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 17:14:03 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include "op.h"
# include "visual.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>

/*
**		Different errors defines
*/
# define ARG_ERR 1
# define OPEN_ERR 2
# define MLC_ERR 3
# define READ_ERR 4
# define HEADER_ERR 5
# define SIZE_ERR 6
# define MANY_ARG 7
# define LARGE_SIZE 8

# define XOR 0
# define AND 1
# define OR 2
# define ST 0x3
# define JUMP 0x9
# define FORK 0xc
# define LDI 0xa
# define STI 0xb
# define LLD 0xd
# define LLDI 0xe
# define LFORK 0xf

/*
**	Get modulo address of core field
*/
# define ARENA(x) cor->field[corsize(x)]

typedef struct s_visual	t_vis;

typedef struct	s_opt
{
	int			argc;
	char		*name;
	int			args[3];
	int			cycles;
	int			octal;
	int			dir;
}				t_opt;

/*
**	struct for instructions to be executed
*/
typedef struct	s_ins
{
	char		*name;
	int			opcode;
	int			argc;
	int			args[3];
	int			sizes[3];
	int			types[3];
	int			cycles;
	int			octal;
	int			dir;
	int			size;
}				t_ins;

/*
**	struct for each champion's process
*/
typedef struct s_proc	t_proc;
struct			s_proc
{
	int			id;
	int			pc;
	int			war;
	int			live;
	int			last;
	int			cycle;
	int			out;
	char		**r;
	t_ins		*ins;
	t_bool		carry;
	t_proc		*next;
};

/*
**	struct for every executed champion
*/
typedef struct	s_warrior
{
	int			pl;
	int			live;
	int			last;
	int			proc_count;
	char		*name;
	char		*comm;
	char		*code;
	unsigned	size;
	t_proc		*process;
}				t_war;

/*
**	main project structure, contains all info
*/
typedef struct	s_cor
{
	int			pl;
	int			aff;
	int			dump;
	int			stop;
	int			verb;
	int			last;
	int			pause;
	int			visual;
	int			warriors;
	int			proc_num;
	int			cycle_to_die;
	int			cycle;
	int			cycles;
	char		*field;
	t_vis		*vis;
	t_proc		*process;
	t_war		**warrior;
}				t_cor;

/*
**	Start declaration of  operation fucntions
*/
typedef void	(*t_oper_f)(t_cor *, t_proc *);

void			cor_live(t_cor *cor, t_proc *proc);
void			cor_ld(t_cor *cor, t_proc *proc);
void			cor_st(t_cor *cor, t_proc *proc);
void			cor_add(t_cor *cor, t_proc *proc);
void			cor_sub(t_cor *cor, t_proc *proc);
void			cor_and(t_cor *cor, t_proc *proc);
void			cor_or(t_cor *cor, t_proc *proc);
void			cor_xor(t_cor *cor, t_proc *proc);
void			cor_zjmp(t_cor *cor, t_proc *proc);
void			cor_ldi(t_cor *cor, t_proc *proc);
void			cor_sti(t_cor *cor, t_proc *proc);
void			cor_fork(t_cor *cor, t_proc *proc);
void			cor_lld(t_cor *cor, t_proc *proc);
void			cor_lldi(t_cor *cor, t_proc *proc);
void			cor_lfork(t_cor *cor, t_proc *proc);
void			cor_aff(t_cor *cor, t_proc *proc);
/*
**	End of declarations
*/

int				corsize(int pos);
int				cor_read_reg(t_proc *proc, int r);
int				cor_read_indir(t_cor *cor, int pc);
int				cor_read_ins(t_cor *cor, t_proc *proc);
int				cor_bits_get_args(t_proc *proc, int mod);
int				cor_cycle_decrement(t_cor *cor, int lives, int checks);
void			cor_dump_out(t_cor *cor);
void			cor_start_game(t_cor *cor);
void			cor_errors(int err, char *str);
void			cor_cycle_increment(t_cor *cor);
void			cor_move_pc(t_cor *cor, t_proc *proc);
void			cor_make_ins(t_cor *cor, t_proc *proc);
void			cor_show_live(t_cor *cor, t_proc *proc);
void			cor_show_death(t_cor *cor, t_proc *proc);
void			cor_struct_wars(t_cor *cor, t_war *wars[]);
void			cor_operation_out(t_cor *cor, t_proc *proc);
void			cor_parse_params(t_cor *cor, int ac, char **av);
void			cor_kill_process(t_cor *cor, t_proc **del, t_proc **prev);
t_war			*cor_read(t_cor *cor, char *file, int war_num);
t_proc			*cor_new_process(t_cor *cor, t_proc *proc, int pc);

#endif
