/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 12:30:29 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:55:18 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

static void		vis_info_init(t_vis *vis)
{
	t_win		*info;

	if (!(info = (t_win*)ft_memalloc(sizeof(t_win))))
		cor_errors(MLC_ERR, NULL);
	info->h = I_H;
	info->w = I_W;
	info->win = newwin(info->h, info->w, info->y, vis->f->w);
	wattron(info->win, COLOR_PAIR(BORDER));
	mvwhline(info->win, info->y, info->x, ' ', info->w - 1);
	mvwhline(info->win, info->h - 1, info->x, ' ', info->w - 1);
	mvwvline(info->win, info->y, info->w - 1, ' ', info->h);
	mvwhline(info->win, 10, 0, ' ', info->w - 1);
	mvwhline(info->win, 20, 0, ' ', info->w - 1);
	mvwhline(info->win, 42, 0, ' ', info->w - 1);
	wattroff(info->win, COLOR_PAIR(BORDER));
	vis_print_info(info);
	wrefresh(info->win);
	vis->info = info;
}

static void		vis_field_init(t_vis *vis)
{
	t_win		*f;

	if (!(f = (t_win*)ft_memalloc(sizeof(t_win))))
		cor_errors(MLC_ERR, NULL);
	f->h = F_H;
	f->w = F_W;
	f->win = newwin(f->h, f->w, f->y, f->x);
	wattron(f->win, COLOR_PAIR(BORDER));
	mvwhline(f->win, f->y, f->x, ' ', f->w - 1);
	mvwhline(f->win, f->h - 1, f->x, ' ', f->w - 1);
	mvwvline(f->win, f->y, f->x, ' ', f->h - 1);
	mvwvline(f->win, f->y, f->w - 1, ' ', f->h);
	wattroff(f->win, COLOR_PAIR(BORDER));
	wrefresh(f->win);
	f->y = 1;
	f->x = 3;
	vis->f = f;
}

static void		vis_draw_field(t_cor *cor, t_vis *vis)
{
	int			i;

	i = 0;
	wattron(vis->f->win, COLOR_PAIR(EMPTY));
	while (i < MEM_SIZE)
	{
		if (!(i % BYTE_PER_LINE))
			wmove(vis->f->win, ++vis->f->y, vis->f->x);
		vis->field[i].color = -1;
		wprintw(vis->f->win, "%02x ", (unsigned char)ARENA(i));
		i++;
	}
	wattroff(vis->f->win, COLOR_PAIR(EMPTY));
	wrefresh(vis->f->win);
}

static void		vis_color_init(void)
{
	start_color();
	init_color(COLOR_GREY, 230, 230, 230);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(LIVE(1), COLOR_GREEN, COLOR_WHITE);
	init_pair(LIVE(2), COLOR_BLUE, COLOR_WHITE);
	init_pair(LIVE(3), COLOR_YELLOW, COLOR_WHITE);
	init_pair(LIVE(4), COLOR_CYAN, COLOR_WHITE);
	init_pair(BORDER, COLOR_BLACK, COLOR_GREY);
	init_pair(EMPTY, COLOR_GREY, COLOR_BLACK);
}

void			vis_init(t_cor *cor)
{
	t_vis		*vis;

	initscr();
	refresh();
	if (!(vis = (t_vis*)ft_memalloc(sizeof(t_vis))))
		cor_errors(MLC_ERR, NULL);
	if (!(vis->field = (t_field*)ft_memalloc(sizeof(t_field) * MEM_SIZE)))
		cor_errors(MLC_ERR, NULL);
	vis->limit = 50;
	vis->microsec = MICROSEC / vis->limit;
	cor->vis = vis;
	cbreak();
	noecho();
	curs_set(NONE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	vis_color_init();
	vis_field_init(vis);
	vis_info_init(vis);
	vis_draw_field(cor, vis);
	vis_player_info(cor, vis->info);
	vis_detail_init(cor, vis);
}
