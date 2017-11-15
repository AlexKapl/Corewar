/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:31 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:44:48 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			cor_move_pc(t_cor *cor, t_proc *proc)
{
	int			i;
	int			pc;

	pc = proc->pc + proc->ins->size;
	if (cor->vis)
		vis_move_pc(cor, proc, proc->ins->size);
	if (cor->verb & 0x10)
	{
		i = 0;
		if (cor->pl)
			ft_printf("P %4d | ", proc->id);
		ft_printf("ADV %2d (", proc->ins->size);
		proc->pc ? ft_printf("%0#6x -> ", proc->pc) : ft_printf("0x0000 -> ");
		pc ? ft_printf("%0#6x)", pc) : ft_printf("0x0000)");
		while (i < proc->ins->size)
		{
			ft_printf(" %02x", (unsigned char)ARENA(proc->pc + i));
			i++;
		}
		ft_printf("\n");
	}
	proc->pc = corsize(pc);
}

void			cor_show_live(t_cor *cor, t_proc *proc)
{
	int			i;
	t_war		**war;

	war = cor->warrior;
	if (proc->ins->args[0] != war[proc->war]->pl)
	{
		i = -1;
		while (++i < cor->warriors)
			if (war[i]->pl == proc->ins->args[0])
			{
				war[i]->live++;
				war[i]->last = cor->cycle;
				if (cor->verb & 0x1)
					ft_printf("Player %d (%s) is said to be alive\n",
							-war[i]->pl, war[i]->name);
				break ;
			}
	}
	else if (cor->verb & 0x1)
		ft_printf("A process shows that player %d (%s) is alive.\n",
				-war[proc->war]->pl, war[proc->war]->name);
}

void			cor_show_death(t_cor *cor, t_proc *proc)
{
	if (cor->pl)
		ft_printf("Pl %4d | ", cor->warrior[proc->war]->pl);
	ft_printf("Process %4d didn't live for %4d cycles (CTD %4d)\n",
			proc->id, cor->cycles - proc->last, cor->cycle_to_die);
}

int				cor_cycle_decrement(t_cor *cor, int lives, int checks)
{
	cor->cycle = 0;
	if (lives >= NBR_LIVE || ++checks == MAX_CHECKS)
	{
		checks = 0;
		cor->cycle_to_die -= CYCLE_DELTA;
		if (cor->verb & 0x2)
			ft_printf("Cycle to die now is  %d\n", cor->cycle_to_die);
	}
	return (checks);
}

void			cor_cycle_increment(t_cor *cor)
{
	cor->cycle++;
	cor->cycles++;
	if (cor->verb & 0x2)
		ft_printf("Current cycle  %d\n", cor->cycles);
}
