/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 12:27:40 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 12:28:08 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

static void		vis_refresh_field(t_cor *cor)
{
	t_attr_v	*at;

	at = (t_attr_v*)queue_peek(&cor->vis->queue);
	while (at)
	{
		if (at->end != cor->cycles)
		{
			wrefresh(cor->vis->f->win);
			return ;
		}
		if (at->type == FIRST)
			vis_hide_live(cor, cor->vis);
		else
			vis_map_attr_off(cor, cor->vis);
		at = (t_attr_v*)queue_peek(&cor->vis->queue);
	}
	wrefresh(cor->vis->f->win);
}

static void		vis_refresh_info(t_cor *cor, t_win *info)
{
	int			i;

	wattron(info->win, A_BOLD);
	i = -1;
	while (++i < MAX_PL && I < cor->warriors)
	{
		wattron(info->win, PAIR(I));
		mvwprintw(info->win, PL_LINE(i), 11, "%6d : %-38.38s ",
				cor->warrior[I]->pl, cor->warrior[I]->name);
		wattroff(info->win, PAIR(i));
		mvwprintw(info->win, PL_LINE(i) + 1, 33, "%8d",
				cor->warrior[I]->proc_count);
		mvwprintw(info->win, PL_LINE(i) + 2, 33, "%8d", cor->warrior[I]->last);
		mvwprintw(info->win, PL_LINE(i) + 3, 33, "%8d", cor->warrior[I]->live);
	}
	mvwprintw(info->win, 2, I_TAB, "%11s",
			cor->vis->run ? "|-RUNNING-|" : "|-PAUSED-|");
	mvwprintw(info->win, 4, I_TAB + 23, "%4u", cor->vis->limit);
	mvwprintw(info->win, 6, I_TAB + 9, "%4d", cor->cycles);
	mvwprintw(info->win, 12, I_TAB + 15, "%4d", cor->cycle_to_die);
	wattron(info->win, A_UNDERLINE);
	mvwprintw(info->win, 8, I_TAB + 9, "%4d", cor->cycle);
	wattroff(info->win, A_BOLD | A_UNDERLINE);
	wrefresh(info->win);
}

static void		vis_change_limit(t_cor *cor, int mode)
{
	if (mode == FIRST)
	{
		if (cor->vis->limit + 10 <= 1000)
			cor->vis->limit += 10;
	}
	else if (mode == SECOND)
	{
		if (cor->vis->limit > 10)
			cor->vis->limit -= 10;
	}
	else if (mode == KEY_UP)
	{
		if (cor->vis->pl > 0)
			cor->vis->pl--;
	}
	else
	{
		if (cor->vis->pl + 4 < cor->warriors)
			cor->vis->pl++;
	}
	cor->vis->microsec = MICROSEC / cor->vis->limit;
	vis_refresh_info(cor, cor->vis->info);
}

static int		vis_key_hook(t_cor *cor)
{
	int			key;

	key = getch();
	if (key == ' ')
		cor->vis->run = !cor->vis->run;
	else if (key == 's')
	{
		cor->vis->run = FALSE;
		return (1);
	}
	else if (key == 43)
		vis_change_limit(cor, FIRST);
	else if (key == 45)
		vis_change_limit(cor, SECOND);
	else if (key == KEY_UP)
		vis_change_limit(cor, key);
	else if (key == KEY_DOWN)
		vis_change_limit(cor, key);
	else if (key == 9)
		vis_refresh_detail(cor, cor->vis, FIRST);
	else if (key == 127)
		vis_refresh_detail(cor, cor->vis, SECOND);
	return (0);
}

void			vis_break_cycle(t_cor *cor)
{
	vis_refresh_info(cor, cor->vis->info);
	vis_refresh_field(cor);
	vis_refresh_detail(cor, cor->vis, NONE);
	if (cor->vis->run)
	{
		vis_key_hook(cor);
		usleep(cor->vis->microsec);
	}
	else
		while (!cor->vis->run)
			if (vis_key_hook(cor))
				break ;
}
