/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 02:43:45 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 02:44:06 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*find_len(char *format, t_form *form)
{
	if (*format == 'h' && *(format + 1) == 'h')
		form->len = (form->len < hh ? hh : form->len);
	else if (*format == 'h')
		form->len = (form->len < h ? h : form->len);
	else if (*format == 'l' && *(format + 1) != 'l')
		form->len = (form->len < l ? l : form->len);
	else if (*format == 'l')
		form->len = (form->len < ll ? ll : form->len);
	else if (*format == 'j')
		form->len = (form->len < j ? j : form->len);
	else if (*format == 'z')
		form->len = (form->len < z ? z : form->len);
	if (*format == 'l' && *(format + 1) != 'l')
		form->cl = 1;
	if ((*format == 'h' && *(format + 1) == 'h') ||
			(*format == 'l' && *(format + 1) == 'l'))
		format += 2;
	else if (*format && ft_strchr("hljzL", *format))
		format++;
	return (format);
}

static char	*find_press(char *format, va_list argc, t_form *form)
{
	if (*format == '.')
	{
		format++;
		if (*format == '*')
		{
			form->press = va_arg(argc, int);
			format++;
		}
		else
		{
			form->press = ft_atoi(format);
			while (ft_isdigit(*format))
				format++;
		}
	}
	return (format);
}

static char	*find_width(char *format, va_list argc, t_form *form)
{
	if (*format == '*')
	{
		form->width = va_arg(argc, int);
		if (form->width < 0)
		{
			form->minus = 1;
			form->width *= -1;
		}
		format++;
	}
	else if (ft_isdigit(*format))
	{
		form->width = ft_atoi(format);
		while (ft_isdigit(*format))
			format++;
	}
	return (format);
}

static char	*find_flags(char *format, t_form *form)
{
	while (*format && check_flags(*format))
	{
		if (*format == '#')
			form->hash = 1;
		else if (*format == '\'')
			form->quote = 1;
		else if (*format == ' ' && !form->plus)
			form->space = 1;
		else if (*format == '0' && !form->minus)
			form->zero = 1;
		else if (*format == '+')
		{
			form->plus = 1;
			form->space = 0;
		}
		else if (*format == '-')
		{
			form->minus = 1;
			form->zero = 0;
		}
		format++;
	}
	return (format);
}

char		*parse_percent(char *format, va_list argc, va_list tmp,
							t_form *form)
{
	format++;
	format = find_dolla(format, form);
	while (*format && ft_strchr("0123456789+-*$#.'hljz ", *format))
	{
		format = find_flags(format, form);
		format = find_width(format, tmp, form);
		format = find_press(format, tmp, form);
		format = find_len(format, form);
		if (*format == '$')
			format++;
	}
	if (form->dolla)
		skip_va_list(argc, tmp, form);
	format = find_type(format, form);
	return (format);
}
