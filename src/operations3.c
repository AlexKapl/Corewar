/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:13 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:28:13 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void				cor_sti(t_cor *cor, t_proc *proc)
{
	int				x;
	int				i;
	int				reg;

	reg = proc->ins->args[0];
	x = proc->pc + cor_bits_get_args(proc, STI) % IDX_MOD;
	proc->out = x;
	if (cor->visual)
		cor->vis->pos = corsize(x);
	i = 0;
	while (i < REG_SIZE)
		ARENA(x++) = proc->r[reg][i++];
	if (cor->visual)
		vis_refresh_map(cor, cor->vis, proc);
	cor_operation_out(cor, proc);
}

void				cor_fork(t_cor *cor, t_proc *proc)
{
	t_proc			*new;

	cor->warrior[proc->war]->proc_count++;
	new = cor_new_process(cor, proc, proc->ins->args[0] % IDX_MOD);
	new->next = cor->process;
	cor->process = new;
	proc->out = new->pc;
	if (cor->vis)
		vis_move_pc(cor, new, NONE);
	cor_operation_out(cor, proc);
}

void				cor_lld(t_cor *cor, t_proc *proc)
{
	int				x;
	int				i;
	int				reg;
	t_ins			*ins;

	ins = proc->ins;
	reg = ins->args[1];
	x = ins->args[0];
	i = -1;
	while (++i < REG_SIZE)
		proc->r[reg][i] = (char)(x >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !x;
	cor_operation_out(cor, proc);
}

void				cor_lldi(t_cor *cor, t_proc *proc)
{
	int				x;
	int				i;
	int				reg;
	int				carry;

	reg = proc->ins->args[2];
	x = proc->pc + cor_bits_get_args(proc, LDI);
	proc->out = x;
	i = 0;
	carry = 0;
	while (i < REG_SIZE)
	{
		proc->r[reg][i] = ARENA(x++);
		carry += proc->r[reg][i++];
	}
	proc->carry = !carry;
	cor_operation_out(cor, proc);
}

void				cor_lfork(t_cor *cor, t_proc *proc)
{
	t_proc			*new;

	cor->warrior[proc->war]->proc_count++;
	new = cor_new_process(cor, proc, proc->ins->args[0]);
	new->next = cor->process;
	cor->process = new;
	proc->out = proc->pc + proc->ins->args[0];
	if (cor->vis)
		vis_move_pc(cor, new, NONE);
	cor_operation_out(cor, proc);
}
