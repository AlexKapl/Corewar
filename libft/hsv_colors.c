/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 19:37:07 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/24 19:37:38 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/hsv.h"

#define C_R colors->r
#define C_G colors->g
#define C_B colors->b

static void			y_rainbow(t_rgb *colors, int num)
{
	if ((num >= 0 && num < 3) || num == 7)
	{
		colors->r = num == 1 ? 128 : 0;
		colors->g = (num == 0 || num == 7) ? 255 : 0;
		colors->b = 255;
	}
	else
	{
		colors->r = num == 4 ? 0 : 255;
		if (num == 6)
			colors->g = 0;
		else if (num == 5)
			colors->g = 128;
		else
			colors->g = 255;
		colors->b = 0;
	}
}

static void			rainbow(t_rgb *colors, int num)
{
	if ((num >= 0 && num < 3) || num == 7)
	{
		colors->r = 255;
		if (!(colors->g = num == 1 ? 128 : 0))
			colors->g = num == 2 ? 255 : 0;
		colors->b = 0;
	}
	else
	{
		colors->r = num == 6 ? 128 : 0;
		colors->g = (num > 4 ? 0 : 255);
		colors->b = (num == 3 ? 0 : 255);
	}
}

static void			other_low_colors(t_rgb *colors, t_name name)
{
	if (name == COLDY)
		colors->r = 0;
	else
		colors->r = (name == GREENY ? 128 : 255);
	colors->g = 255;
	if (name == GREENY)
		colors->b = 255;
	else
		colors->b = 0;
}

static void			low_colors(t_rgb *colors, int num, t_name name)
{
	if (num == 2)
	{
		colors->r = (name == COLDY ? 0 : 255);
		colors->g = (name == GREENY ? 255 : 0);
		colors->b = (name == COLDY ? 255 : 0);
	}
	else if (num == 1)
	{
		if (name == COLDY)
			colors->r = 0;
		else
			colors->r = (name == GREENY ? 191 : 255);
		colors->g = (name == GREENY ? 255 : 128);
		colors->b = (name == COLDY ? 255 : 0);
	}
	else
		other_low_colors(colors, name);
}

t_rgb				*pallette_colors(t_name name)
{
	t_rgb			*colors;
	int				mode;

	if (!(mode = name == RAINBOW ? 1 : 0))
		mode = name == YODA_RAINBOW ? 2 : 0;
	colors = (t_rgb*)malloc(sizeof(t_rgb) * (mode ? 8 : 4));
	if (!mode)
	{
		low_colors(&colors[0], 0, name);
		low_colors(&colors[1], 1, name);
		low_colors(&colors[2], 2, name);
		low_colors(&colors[3], 3, name);
	}
	else
	{
		mode == 1 ? rainbow(&colors[0], 0) : y_rainbow(&colors[0], 0);
		mode == 1 ? rainbow(&colors[1], 1) : y_rainbow(&colors[1], 1);
		mode == 1 ? rainbow(&colors[2], 2) : y_rainbow(&colors[2], 2);
		mode == 1 ? rainbow(&colors[3], 3) : y_rainbow(&colors[3], 3);
		mode == 1 ? rainbow(&colors[4], 4) : y_rainbow(&colors[4], 4);
		mode == 1 ? rainbow(&colors[5], 5) : y_rainbow(&colors[5], 5);
		mode == 1 ? rainbow(&colors[6], 6) : y_rainbow(&colors[6], 6);
		mode == 1 ? rainbow(&colors[7], 7) : y_rainbow(&colors[7], 7);
	}
	return (colors);
}
