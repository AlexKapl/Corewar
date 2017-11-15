/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 12:28:14 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 12:28:43 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void			vis_map_attr_off(t_cor *cor, t_vis *vis)
{
	int			i;
	int			attr;
	t_win		*f;
	t_attr_v	*at;

	at = (t_attr_v*)dequeue(&vis->queue);
	f = vis->f;
	f->y = PC_Y(at->pc);
	f->x = PC_X(at->pc);
	i = 0;
	while (i < REG_SIZE)
	{
		vis->field[at->pc].fresh = NONE;
		attr = COLOR(at->pc) | vis->field[at->pc].pc
			| vis->field[at->pc].live;
		vis_print_hex(cor, vis, at->pc, attr);
		at->pc = corsize(++at->pc);
		i++;
	}
	ft_memdel((void**)&at);
}

void			vis_move_pc(t_cor *cor, t_proc *proc, int delta)
{
	int			pc;
	int			attr;
	t_vis		*vis;

	pc = proc->pc;
	vis = cor->vis;
	vis->f->y = PC_Y(pc);
	vis->f->x = PC_X(pc);
	if (delta)
	{
		vis->field[pc].pc = NONE;
		attr = COLOR(pc) | vis->field[pc].fresh | vis->field[pc].live;
		vis_print_hex(cor, vis, pc, attr);
		if (delta < 0)
			return ;
		pc = corsize(pc + delta);
		vis->f->y = PC_Y(pc);
		vis->f->x = PC_X(pc);
	}
	vis->field[pc].pc = A_REVERSE;
	attr = COLOR(pc) | A_REVERSE;
	vis_print_hex(cor, vis, pc, attr);
	wrefresh(vis->f->win);
}

void			vis_show_live(t_cor *cor, t_vis *vis, t_proc *proc)
{
	int			pos;
	int			attr;
	int			live;

	pos = proc->pc;
	vis->f->y = PC_Y(pos);
	vis->f->x = PC_X(pos);
	live = A_BOLD | A_UNDERLINE | A_REVERSE;
	vis->field[pos].live = live;
	attr = live | COLOR(pos);
	vis_print_hex(cor, vis, pos, attr);
	wrefresh(vis->f->win);
	vis->pos = pos;
	vis_queue_attr(cor, proc, FIRST);
}

void			vis_refresh_map(t_cor *cor, t_vis *vis, t_proc *proc)
{
	int			i;
	int			pos;
	int			attr;

	pos = corsize(vis->pos);
	vis->f->y = PC_Y(pos);
	vis->f->x = PC_X(pos);
	i = 0;
	while (i < REG_SIZE)
	{
		vis->field[pos].color = proc->war;
		vis->field[pos].fresh = A_BOLD;
		attr = COLOR(pos) | vis->field[pos].pc | vis->field[pos].live | A_BOLD;
		vis_print_hex(cor, vis, pos, attr);
		pos = corsize(++pos);
		i++;
	}
	wrefresh(vis->f->win);
	vis_queue_attr(cor, proc, SECOND);
}

void			vis_fill_field(t_cor *cor, t_vis *vis, int war_num)
{
	int			i;
	int			pos;
	int			color;
	t_war		*war;

	i = -1;
	war = cor->warrior[war_num];
	pos = war->process->pc;
	vis->f->y = PC_Y(pos);
	vis->f->x = PC_X(pos);
	color = PAIR(war_num);
	while (++i < (int)war->size)
	{
		vis_print_hex(cor, vis, pos + i, color);
		vis->field[pos + i].color = war_num;
	}
	wrefresh(vis->f->win);
}
