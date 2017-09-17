/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:49:26 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/24 19:33:42 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSV_H
# define HSV_H
# include "libft.h"

/*
**	Color define
*/

# define WHITE 0xFFFFFF

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_hsv
{
	int			h;
	int			s;
	int			v;
}				t_hsv;

typedef struct	s_pallete
{
	t_rgb		*colors;
	int			colors_total;
}				t_pallete;

typedef enum
{
	RAINBOW,
	YODA_RAINBOW,
	SUNNY,
	COLDY,
	GREENY
}	t_name;

void			hsv_to_rgb(t_hsv *hsv, t_rgb *rgb, t_name name);
t_rgb			*pallette_colors(t_name name);

#endif
