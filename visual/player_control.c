/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 12:28:50 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 12:29:53 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void			vis_player_info(t_cor *cor, t_win *info)
{
	int			i;

	cor->vis->pl = 0;
	wattron(info->win, A_BOLD);
	i = -1;
	while (++i < cor->warriors && i < MAX_PL)
	{
		mvwprintw(info->win, PL_LINE(i), 4, "Player ");
		wattron(info->win, PAIR(i));
		wprintw(info->win, "%6d : %.40s ",
				cor->warrior[i]->pl, cor->warrior[i]->name);
		wattroff(info->win, PAIR(i));
		mvwprintw(info->win, PL_LINE(i) + 1, 6, "Processes :");
		mvwprintw(info->win, PL_LINE(i) + 2, 6, "Last life :");
		mvwprintw(info->win, PL_LINE(i) + 3, 6,
				"Lives in current period :");
	}
	wattroff(info->win, A_BOLD);
	wrefresh(info->win);
}

static void		vis_print_reg(t_vis *vis)
{
	int			i;
	t_win		*det;

	det = vis->det;
	det->y = 0;
	det->x = 13;
	wattron(det->win, PAIR(vis->war));
	while (det->y < REG_NUMBER)
	{
		wmove(det->win, det->y + 6, det->x);
		i = -1;
		while (++i < REG_SIZE)
		{
			if (vis->proc)
				wprintw(det->win, "%02x ",
						(unsigned char)vis->proc->r[det->y][i]);
			else
				wprintw(det->win, "   ");
		}
		det->y++;
	}
	wattroff(det->win, PAIR(vis->war));
	wrefresh(det->win);
}

static void		vis_get_process(t_cor *cor, t_vis *vis, int mode)
{
	if (mode == FIRST)
	{
		if (++vis->war == cor->warriors)
			vis->war = 0;
		vis->proc = cor->process;
		while (vis->proc && vis->proc->war != vis->war)
			vis->proc = vis->proc->next;
	}
	else if (mode == SECOND)
	{
		if (vis->proc)
		{
			vis->proc = vis->proc->next;
			while (vis->proc && vis->proc->war != vis->war)
				vis->proc = vis->proc->next;
		}
		if (!vis->proc)
		{
			vis->proc = cor->process;
			while (vis->proc && vis->proc->war != vis->war)
				vis->proc = vis->proc->next;
		}
	}
}

void			vis_refresh_detail(t_cor *cor, t_vis *vis, int mode)
{
	vis_get_process(cor, vis, mode);
	wattron(vis->det->win, PAIR(vis->war) | A_BOLD);
	mvwprintw(vis->det->win, 1, I_TAB + 11, "%6d",
			cor->warrior[vis->war]->pl);
	if (vis->proc)
	{
		mvwprintw(vis->det->win, 2, I_TAB + 11, "%6d", vis->proc->id);
		mvwprintw(vis->det->win, 3, I_TAB + 11, "%6d", vis->proc->pc);
		mvwprintw(vis->det->win, 4, I_TAB + 11, "%6d", vis->proc->carry);
	}
	else
	{
		mvwprintw(vis->det->win, 2, I_TAB + 11, "  NONE");
		mvwprintw(vis->det->win, 3, I_TAB + 11, "  NONE");
		mvwprintw(vis->det->win, 4, I_TAB + 11, "  NONE");
	}
	wattroff(vis->det->win, PAIR(vis->war) | A_BOLD);
	vis_print_reg(vis);
}

void			vis_detail_init(t_cor *cor, t_vis *vis)
{
	t_win		*det;

	if (!(det = ft_memalloc(sizeof(t_win))))
		cor_errors(MLC_ERR, NULL);
	det->h = D_H;
	det->w = D_W;
	det->win = newwin(det->h, det->w, I_D + 1, F_W);
	vis->det = det;
	vis->war = cor->warriors - 1;
	vis->proc = cor->process;
	wattron(det->win, A_BOLD);
	mvwprintw(det->win, 1, I_TAB, "Player  : ");
	mvwprintw(det->win, 2, I_TAB, "Process : ");
	mvwprintw(det->win, 3, I_TAB, "PC      : ");
	mvwprintw(det->win, 4, I_TAB, "Carry   : ");
	mvwprintw(det->win, 5, I_TAB, "Registry");
	wattroff(det->win, A_BOLD);
	vis_refresh_detail(cor, vis, NONE);
	vis_print_reg(vis);
}
