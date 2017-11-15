/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:27 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:38:20 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		cor_del_data(t_proc **del)
{
	int			i;
	t_proc		*proc;

	proc = *del;
	i = -1;
	while (++i < REG_NUMBER)
		ft_memdel((void**)&proc->r[i]);
	ft_memdel((void**)&proc->r);
	ft_memdel((void**)&proc->ins);
	ft_memdel((void**)del);
}

void			cor_kill_process(t_cor *cor, t_proc **del, t_proc **prev)
{
	cor->warrior[(*del)->war]->proc_count--;
	if (cor->verb & 0x8)
		cor_show_death(cor, *del);
	if (cor->visual)
		vis_move_pc(cor, *del, CLEAN);
	if (*prev)
	{
		(*prev)->next = (*del)->next;
		cor_del_data(del);
		*del = (*prev)->next;
	}
	else
	{
		*prev = *del;
		cor->process = cor->process->next;
		*del = cor->process;
		cor_del_data(prev);
	}
	if (cor->visual)
	{
		cor->vis->proc = cor->process;
		vis_refresh_detail(cor, cor->vis, SECOND);
	}
}

t_proc			*cor_new_process(t_cor *cor, t_proc *proc, int pc)
{
	int			i;
	t_proc		*new;

	if (!(new = (t_proc*)ft_memalloc(sizeof(t_proc))))
		cor_errors(MLC_ERR, NULL);
	if (!(new->r = (char**)ft_memalloc(sizeof(char*) * REG_NUMBER)))
		cor_errors(MLC_ERR, NULL);
	if (!(new->ins = (t_ins*)ft_memalloc(sizeof(t_ins))))
		cor_errors(MLC_ERR, NULL);
	i = -1;
	while (++i < REG_NUMBER)
	{
		if (!(new->r[i] = (char*)ft_memalloc(REG_SIZE)))
			cor_errors(MLC_ERR, NULL);
		new->r[i] = ft_memcpy(new->r[i], proc->r[i], REG_SIZE);
	}
	new->id = ++cor->proc_num;
	new->pc = corsize(proc->pc + pc);
	new->war = proc->war;
	new->carry = proc->carry;
	new->live = proc->live;
	new->last = proc->last;
	return (new);
}
