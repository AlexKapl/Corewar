/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:27:26 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:25:01 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void			cor_finish_game(t_cor *cor)
{
	if (cor->visual)
	{
		nodelay(stdscr, FALSE);
		wattron(cor->vis->det->win, A_BOLD | PAIR(cor->last));
		mvwprintw(cor->vis->det->win, 12, 4, "Player %d (%.30s) won\n",
				-cor->warrior[cor->last]->pl, cor->warrior[cor->last]->name);
		wattroff(cor->vis->det->win, A_BOLD | PAIR(cor->last));
		wattron(cor->vis->det->win, A_BOLD | COLOR_PAIR(1));
		mvwprintw(cor->vis->det->win, 13, 4, "Press q to exit\n");
		wattroff(cor->vis->det->win, A_BOLD | COLOR_PAIR(1));
		wrefresh(cor->vis->det->win);
		while (getch() != 'q')
			;
		endwin();
	}
	else
		ft_printf("Player %d (%s) won\n",
				-cor->warrior[cor->last]->pl, cor->warrior[cor->last]->name);
}

static void			cor_check_process_live(t_cor *cor)
{
	t_proc			*proc;
	t_proc			*prev;

	prev = NULL;
	proc = cor->process;
	while (proc)
	{
		if (!proc->live)
			cor_kill_process(cor, &proc, &prev);
		else
		{
			proc->live = 0;
			prev = proc;
			proc = proc->next;
		}
	}
}

static int			cor_check_lives(t_cor *cor)
{
	static int		checks = 0;
	int				i;
	int				live;
	int				lives;

	i = cor->warriors;
	lives = 0;
	while (--i >= 0)
	{
		live = cor->warrior[i]->live;
		if (live && cor->last <= cor->warrior[i]->last)
			cor->last = i;
		if (live > lives)
			lives = live;
		cor->warrior[i]->last = 0;
		cor->warrior[i]->live = 0;
	}
	cor_check_process_live(cor);
	checks = cor_cycle_decrement(cor, lives, checks);
	return (lives);
}

static void			cor_make_move(t_cor *cor, t_proc *proc)
{
	static t_oper_f	ins[16] =
	{cor_live, cor_ld, cor_st, cor_add, cor_sub, cor_and, cor_or,
		cor_xor, cor_zjmp, cor_ldi, cor_sti, cor_fork, cor_lld, cor_lldi,
		cor_lfork, cor_aff};

	while (proc)
	{
		if (!proc->cycle)
			cor_make_ins(cor, proc);
		else if (++proc->cycle && proc->cycle == proc->ins->cycles)
		{
			if (cor_read_ins(cor, proc))
				ins[proc->ins->opcode - 1](cor, proc);
			if (proc->ins->size)
				cor_move_pc(cor, proc);
			ft_bzero(proc->ins, sizeof(t_proc));
			proc->cycle = 0;
		}
		proc = proc->next;
	}
}

void				cor_start_game(t_cor *cor)
{
	if (cor->vis)
		vis_intit_pc(cor);
	while (1)
	{
		if (cor->visual)
			vis_break_cycle(cor);
		if ((cor->dump == cor->cycles || cor->pause == cor->cycles)
			&& cor->cycles)
			cor_dump_out(cor);
		if (cor->cycle >= cor->cycle_to_die)
			if (!(cor_check_lives(cor)))
				break ;
		cor_cycle_increment(cor);
		cor_make_move(cor, cor->process);
	}
	cor_finish_game(cor);
}
