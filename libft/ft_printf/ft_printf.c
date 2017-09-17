/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 02:49:17 by akaplyar          #+#    #+#             */
/*   Updated: 2017/04/01 16:45:52 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*make_line(char *format, t_form *form, int *size)
{
	size_t	len;
	char	*line;

	len = (*format == '{' ? 1 : 0);
	while (*(format + len) && *(format + len) != '%' && *(format + len) != '{')
		len++;
	line = ft_strsub(format, 0, len);
	*size += write(form->fd, line, ft_strlen(line));
	free(line);
	return (format + len);
}

static void	form_init(t_form *form, int fd)
{
	form->cl = 0;
	form->fd = fd;
	form->hash = 0;
	form->zero = 0;
	form->plus = 0;
	form->minus = 0;
	form->space = 0;
	form->quote = 0;
	form->dolla = 0;
	form->width = 0;
	form->press = -1;
	form->len = -1;
	form->type = -1;
	form->sign = 0;
	form->out = NULL;
}

static char	*parse_format(char *format, va_list argc, va_list tmp, int *size)
{
	t_form	form;
	int		type;

	form_init(&form, size[1]);
	if (*format == '%')
	{
		format = parse_percent(format, argc, tmp, &form);
		type = check_type(&form);
		if (type == 1 || type == 2)
			parse_int(&form, tmp, size, type);
		else if (type == 3)
			parse_str(&form, tmp, size);
		else if (type == 4)
			parse_pointer(&form, tmp, size);
		else if (type == 5)
			print_memory(&form, tmp, size);
		else if (type == 6)
			print_non_printable(&form, tmp, size);
	}
	else if (*format == '{')
		format = parse_brackets(format, &form, tmp, size);
	else
		format = make_line(format, &form, size);
	return (format);
}

int			ft_printf(const char *format, ...)
{
	va_list	argc;
	va_list	tmp;
	int		size[2];

	if (!format)
		return (0);
	size[0] = 0;
	size[1] = 1;
	va_start(argc, format);
	va_copy(tmp, argc);
	while (*format)
		if (!(format = parse_format((char *)format, argc, tmp, size)))
			return (0);
	va_end(tmp);
	va_end(argc);
	return (size[0]);
}
