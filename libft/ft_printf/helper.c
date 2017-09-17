/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 18:07:51 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 18:08:58 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			check_type(t_form *form)
{
	int		a;
	int		i;

	i = form->type;
	if (!(a = (i == d ? 1 : 0)))
		if (!(a = (i == o || i == O || i == x || i == X) ? 2 : 0))
			if (!(a = (i == b || i == u || i == U) ? 2 : 0))
				if (!(a = (i == c || i == C || i == s || i == S) ? 3 : 0))
					if (!(a = (i == n ? 4 : 0)))
						if (!(a = (i == p ? 5 : 0)))
							a = (i == r ? 6 : 0);
	if (i < 0 && *form->out)
		a = 3;
	return (a);
}

void		fill_char(t_form *form, int *size)
{
	size_t	width;
	size_t	i;
	char	*filler;

	width = (size_t)form->width - 1;
	i = 0;
	filler = (char*)ft_memalloc(width + 1);
	while (i < width)
		filler[i++] = (char)(form->zero ? '0' : ' ');
	filler[i] = '\0';
	if (form->minus)
	{
		*size += write(form->fd, form->out, 1);
		*size += write(form->fd, filler, ft_strlen(filler));
	}
	else
	{
		*size += write(form->fd, filler, ft_strlen(filler));
		*size += write(form->fd, form->out, 1);
	}
	free(filler);
}

int			check_flags(char c)
{
	int		a;

	a = 0;
	a += (c == '#' ? 1 : 0);
	a += (c == ' ' ? 1 : 0);
	a += (c == '+' ? 1 : 0);
	a += (c == '-' ? 1 : 0);
	a += (c == '0' ? 1 : 0);
	a += (c == '\'' ? 1 : 0);
	return (a);
}

void		parse_pointer(t_form *form, va_list argc, int *size)
{
	int		*ptr;

	(void)form;
	ptr = va_arg(argc, int*);
	if (!ptr)
		return ;
	*ptr = *size;
}
