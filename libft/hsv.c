/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:50:36 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/24 19:38:48 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/hsv.h"

#define S sector_basecolor[0]
#define N sector_basecolor[1]
#define P pall[name]
#define COLOR pall[name].colors

static t_pallete	*get_pallette(void)
{
	t_pallete		*c_pallete;

	if (!(c_pallete = (t_pallete*)malloc(sizeof(t_pallete) * 5)))
		return (NULL);
	c_pallete[0].colors = pallette_colors(RAINBOW);
	c_pallete[0].colors_total = 8;
	c_pallete[1].colors = pallette_colors(YODA_RAINBOW);
	c_pallete[1].colors_total = 8;
	c_pallete[2].colors = pallette_colors(SUNNY);
	c_pallete[2].colors_total = 4;
	c_pallete[3].colors = pallette_colors(COLDY);
	c_pallete[3].colors_total = 4;
	c_pallete[4].colors = pallette_colors(GREENY);
	c_pallete[4].colors_total = 4;
	return (c_pallete);
}

static int			*get_t(t_hsv *hsv, t_pallete *pall, t_name name, int *temp)
{
	int				diff;
	int				hues_sector[2];
	int				sector_basecolor[2];

	hues_sector[0] = 256 / pall[name].colors_total;
	hues_sector[1] = hsv->h % hues_sector[0];
	sector_basecolor[0] = hsv->h / hues_sector[0];
	N = (S == P.colors_total - 1) ? 0 : S + 1;
	diff = ((COLOR[N].r - COLOR[S].r) * hues_sector[1]) / hues_sector[0];
	if (COLOR[S].r + diff <= 255 && COLOR[S].r + diff >= 0)
		temp[0] = COLOR[S].r + diff;
	else
		temp[0] = (COLOR[S].r + diff) < 0 ? 0 : 255;
	diff = ((COLOR[N].g - COLOR[S].g) * hues_sector[1]) / hues_sector[0];
	if (COLOR[S].g + diff <= 255 && COLOR[S].g + diff >= 0)
		temp[1] = COLOR[S].g + diff;
	else
		temp[1] = (COLOR[S].g + diff) < 0 ? 0 : 255;
	diff = ((COLOR[N].b - COLOR[S].b) * hues_sector[1]) / hues_sector[0];
	if (COLOR[S].b + diff <= 255 && COLOR[S].b + diff >= 0)
		temp[2] = COLOR[S].b + diff;
	else
		temp[2] = (COLOR[S].b + diff) < 0 ? 0 : 255;
	return (temp);
}

void				hsv_to_rgb(t_hsv *hsv, t_rgb *rgb, t_name name)
{
	int					*temp;
	static t_pallete	*c_pallete;

	if (!c_pallete)
		if (!(c_pallete = get_pallette()))
			return ;
	if (!(temp = (int *)malloc(sizeof(int) * 3)))
		return ;
	get_t(hsv, c_pallete, name, temp);
	temp[0] = (255 - ((255 - temp[0]) * hsv->s) / 255);
	temp[1] = (255 - ((255 - temp[1]) * hsv->s) / 255);
	temp[2] = (255 - ((255 - temp[2]) * hsv->s) / 255);
	rgb->r = (temp[0] * hsv->v) / 255;
	rgb->g = (temp[1] * hsv->v) / 255;
	rgb->b = (temp[2] * hsv->v) / 255;
	free(temp);
}
