/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:05:50 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 03:05:57 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		skip_va_list(va_list argc, va_list tmp, t_form *form)
{
	va_end(tmp);
	va_copy(tmp, argc);
	while (--form->dolla)
		va_arg(tmp, void *);
}

char		*find_dolla(char *format, t_form *form)
{
	char	*tmp;

	if (ft_isdigit(*format))
	{
		if ((form->dolla = ft_atoi(format)))
		{
			tmp = format;
			while (*tmp && ft_isdigit(*tmp))
				tmp++;
			if (*tmp == '$')
			{
				tmp++;
				return (tmp);
			}
			form->dolla = 0;
		}
	}
	return (format);
}

char		*find_type(char *format, t_form *form)
{
	if (*format == 'd' || *format == 'D' || *format == 'i')
		form->type = d;
	else if (*format == 'o' || *format == 'O')
		form->type = (*format == 'o' ? o : O);
	else if (*format == 'u' || *format == 'U')
		form->type = (*format == 'u' ? u : U);
	else if (*format == 'x' || *format == 'X')
		form->type = (*format == 'x' ? x : X);
	else if (*format == 'c' || *format == 'C')
		form->type = (*format == 'c' ? c : C);
	else if (*format == 's' || *format == 'S')
		form->type = (*format == 's' ? s : S);
	else if (*format == 'b' || *format == 'n')
		form->type = (*format == 'b' ? b : n);
	else if (*format == 'p' || *format == 'r')
		form->type = (*format == 'p' ? p : r);
	else
		form->out = format;
	if (form->type == O || form->type == U || *format == 'D')
		form->len = (form->len < l ? l : form->len);
	else if ((form->type == c || form->type == s) && form->cl)
		form->type = (form->type == c ? C : S);
	return (*format ? format + 1 : format);
}
