/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:02 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:36:01 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void				cor_live(t_cor *cor, t_proc *proc)
{
	t_war			**war;

	war = cor->warrior;
	proc->live++;
	proc->last = cor->cycles;
	war[proc->war]->live++;
	if (proc->ins->args[0] == war[proc->war]->pl)
		war[proc->war]->last = cor->cycle;
	cor_operation_out(cor, proc);
	cor_show_live(cor, proc);
	if (cor->visual)
		vis_show_live(cor, cor->vis, proc);
}

void				cor_ld(t_cor *cor, t_proc *proc)
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

void				cor_st(t_cor *cor, t_proc *proc)
{
	int				x;
	int				i;
	int				reg;

	i = -1;
	reg = proc->ins->args[0];
	if (proc->ins->types[1] == T_REG)
	{
		x = proc->ins->args[1];
		while (++i < REG_SIZE)
			proc->r[x][i] = proc->r[reg][i];
	}
	else
	{
		x = proc->pc + proc->ins->args[1] % IDX_MOD;
		proc->out = corsize(x);
		if (cor->visual)
			cor->vis->pos = corsize(x);
		while (++i < REG_SIZE)
			ARENA(x++) = proc->r[reg][i];
		if (cor->visual)
			vis_refresh_map(cor, cor->vis, proc);
	}
	cor_operation_out(cor, proc);
}

void				cor_add(t_cor *cor, t_proc *proc)
{
	int				i;
	int				r1;
	int				r2;
	int				r3;
	int				res;

	r1 = cor_read_reg(proc, proc->ins->args[0]);
	r2 = cor_read_reg(proc, proc->ins->args[1]);
	r3 = proc->ins->args[2];
	res = r1 + r2;
	i = -1;
	while (++i < REG_SIZE)
		proc->r[r3][i] = (char)(res >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !res;
	cor_operation_out(cor, proc);
}

void				cor_sub(t_cor *cor, t_proc *proc)
{
	int				i;
	int				r1;
	int				r2;
	int				r3;
	int				res;

	r1 = cor_read_reg(proc, proc->ins->args[0]);
	r2 = cor_read_reg(proc, proc->ins->args[1]);
	r3 = proc->ins->args[2];
	res = r1 - r2;
	i = -1;
	while (++i < REG_SIZE)
		proc->r[r3][i] = (char)(res >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->carry = !res;
	cor_operation_out(cor, proc);
}
