/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:08 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:28:09 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void				cor_and(t_cor *cor, t_proc *proc)
{
	int				i;
	int				x;
	int				reg;

	reg = proc->ins->args[2];
	x = cor_bits_get_args(proc, AND);
	i = -1;
	while (++i < REG_SIZE)
		proc->r[reg][i] = (char)(x >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !x;
	cor_operation_out(cor, proc);
}

void				cor_or(t_cor *cor, t_proc *proc)
{
	int				i;
	int				x;
	int				reg;

	reg = proc->ins->args[2];
	x = cor_bits_get_args(proc, OR);
	i = -1;
	while (++i < REG_SIZE)
		proc->r[reg][i] = (char)(x >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !x;
	cor_operation_out(cor, proc);
}

void				cor_xor(t_cor *cor, t_proc *proc)
{
	int				i;
	int				x;
	int				reg;

	reg = proc->ins->args[2];
	x = cor_bits_get_args(proc, XOR);
	i = -1;
	while (++i < REG_SIZE)
		proc->r[reg][i] = (char)(x >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !x;
	cor_operation_out(cor, proc);
}

void				cor_zjmp(t_cor *cor, t_proc *proc)
{
	if (proc->carry)
	{
		if (cor->vis)
			vis_move_pc(cor, proc, proc->ins->args[0] % IDX_MOD);
		proc->pc = corsize(proc->pc + proc->ins->args[0] % IDX_MOD);
		proc->ins->size = 0;
	}
	cor_operation_out(cor, proc);
}

void				cor_ldi(t_cor *cor, t_proc *proc)
{
	int				x;
	int				i;
	int				reg;

	reg = proc->ins->args[2];
	x = proc->pc + cor_bits_get_args(proc, LDI) % IDX_MOD;
	proc->out = corsize(x);
	i = 0;
	while (i < REG_SIZE)
		proc->r[reg][i++] = ARENA(x++);
	cor_operation_out(cor, proc);
}
