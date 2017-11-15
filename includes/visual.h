/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 17:20:05 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 17:21:15 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VISUAL_H
# define COREWAR_VISUAL_H

# include "op.h"
# include "corewar.h"
# include "../libft/includes/libft.h"
# include <ncurses.h>
# include <panel.h>

# define CLEAN (-1)
# define MAX_PL 4
# define BORDER 9
# define EMPTY 10
# define COLOR_GREY COLOR_MAGENTA
# define BYTE_PER_LINE 64
# define MICROSEC 1000000
# define I (cor->vis->pl + i)
# define LIVE(x) ((x) + 4)
# define MODULO(x) (((x) % 4) + 1)
# define PAIR(x) (COLOR_PAIR (MODULO(x)))
# define NOTH(x) (vis->field[(x)].live ? 4 : 0)
# define PAIR_C(x) (COLOR_PAIR((MODULO(vis->field[(x)].color) + NOTH(x))))
# define COLOR(x) (vis->field[(x)].color >= 0 ? PAIR_C(x) : COLOR_PAIR(EMPTY))

# define F_W ((BYTE_PER_LINE * 3) + 5)
# define F_H ((MEM_SIZE / BYTE_PER_LINE) + 4)
# define I_W 60
# define I_H F_H
# define I_D 42
# define D_W (I_W - 1)
# define D_H ((I_H - I_D) - 2)
# define I_TAB (4)

# define PL_LINE(x) (((x) * 5) + 22)
# define PC_Y(x) (((x) / BYTE_PER_LINE) + 2)
# define PC_X(x) ((((x) % BYTE_PER_LINE) * 3) + 3)

typedef struct s_visual	t_vis;
typedef struct s_proc	t_proc;
typedef struct s_cor	t_cor;

typedef struct		s_vis_attr
{
	int				pc;
	int				type;
	int				end;
}					t_attr_v;

typedef struct		s_field
{
	int				pc;
	int				live;
	int				fresh;
	int				color;
}					t_field;

typedef struct		s_window
{
	WINDOW			*win;
	int				w;
	int				h;
	int				x;
	int				y;
}					t_win;

struct				s_visual
{
	int				pl;
	int				pos;
	int				war;
	unsigned		limit;
	unsigned		microsec;
	t_bool			run;
	t_win			*det;
	t_win			*info;
	t_win			*f;
	t_list			*queue;
	t_proc			*proc;
	t_field			*field;
};

void				vis_init(t_cor *cor);
void				vis_intit_pc(t_cor *cor);
void				vis_break_cycle(t_cor *cor);
void				vis_print_info(t_win *info);
void				vis_hide_live(t_cor *cor, t_vis *vis);
void				vis_detail_init(t_cor *cor, t_vis *vis);
void				vis_player_info(t_cor *cor, t_win *info);
void				vis_map_attr_off(t_cor *cor, t_vis *vis);
void				vis_move_pc(t_cor *cor, t_proc *proc, int delta);
void				vis_queue_attr(t_cor *cor, t_proc *proc, int type);
void				vis_show_live(t_cor *cor, t_vis *vis, t_proc *proc);
void				vis_fill_field(t_cor *cor, t_vis *vis, int war_num);
void				vis_refresh_detail(t_cor *cor, t_vis *vis, int mode);
void				vis_refresh_map(t_cor *cor, t_vis *vis, t_proc *proc);
void				vis_print_hex(t_cor *cor, t_vis *vis, int pos, int attr);
#endif
