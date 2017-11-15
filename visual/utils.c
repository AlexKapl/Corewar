/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 12:30:00 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 12:30:19 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void			vis_hide_live(t_cor *cor, t_vis *vis)
{
	int			attr;
	t_attr_v	*at;

	at = (t_attr_v*)dequeue(&vis->queue);
	vis->f->y = PC_Y(at->pc);
	vis->f->x = PC_X(at->pc);
	vis->field[at->pc].live = NONE;
	attr = COLOR(at->pc) | vis->field[at->pc].pc | vis->field[at->pc].fresh;
	vis_print_hex(cor, vis, at->pc, attr);
	ft_memdel((void**)&at);
}

void			vis_print_info(t_win *info)
{
	wattron(info->win, A_BOLD);
	mvwprintw(info->win, 4, I_TAB, "Cycles/Seconds limit : 0");
	mvwprintw(info->win, 6, I_TAB, "Cycles : 0");
	mvwprintw(info->win, 12, I_TAB, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvwprintw(info->win, 14, I_TAB, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(info->win, 16, I_TAB, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(info->win, 18, I_TAB, "MAX_CHECKS : %d", MAX_CHECKS);
	wattron(info->win, A_UNDERLINE);
	mvwprintw(info->win, 8, I_TAB, "Cycle  : 0");
	wattroff(info->win, A_BOLD | A_UNDERLINE);
}

void			vis_queue_attr(t_cor *cor, t_proc *proc, int type)
{
	t_attr_v	*at;

	(void)proc;
	if (!(at = (t_attr_v*)malloc(sizeof(t_attr_v))))
		cor_errors(MLC_ERR, NULL);
	at->pc = corsize(cor->vis->pos);
	at->end = cor->cycles + 49;
	at->type = type;
	enqueue(&cor->vis->queue, at, NONE);
}

void			vis_intit_pc(t_cor *cor)
{
	int			i;

	i = 0;
	while (i < cor->warriors)
	{
		vis_move_pc(cor, cor->warrior[i]->process, NONE);
		i++;
	}
}

void			vis_print_hex(t_cor *cor, t_vis *vis, int pos, int attr)
{
	pos = corsize(pos);
	if (vis->f->x >= vis->f->w - 2)
	{
		if (++vis->f->y >= vis->f->h - 2)
			vis->f->y = PC_Y(NONE);
		vis->f->x = PC_X(NONE);
	}
	wattron(vis->f->win, attr);
	mvwprintw(vis->f->win, vis->f->y, vis->f->x, "%02x",
			(unsigned char)ARENA(pos));
	wattroff(vis->f->win, attr);
	vis->f->x += 3;
}
