/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 03:02:45 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 03:02:45 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		len_cast_u(t_form *form, va_list argc, uintmax_t *ubuff)
{
	if (form->len == hh)
		*ubuff = (unsigned char)va_arg(argc, unsigned int);
	else if (form->len == h)
		*ubuff = (unsigned short)va_arg(argc, unsigned int);
	else if (form->len == l)
		*ubuff = va_arg(argc, unsigned long);
	else if (form->len == ll)
		*ubuff = va_arg(argc, unsigned long long);
	else if (form->len == j)
		*ubuff = va_arg(argc, uintmax_t);
	else if (form->len == z)
		*ubuff = va_arg(argc, size_t);
	else
		*ubuff = va_arg(argc, unsigned int);
	if (!*ubuff && form->type != o && form->type != O)
		form->hash = 0;
}

static void		len_cast(t_form *form, va_list argc, intmax_t *buff)
{
	if (form->len == hh)
		*buff = (char)va_arg(argc, int);
	else if (form->len == h)
		*buff = (short)va_arg(argc, int);
	else if (form->len == l)
		*buff = va_arg(argc, long);
	else if (form->len == ll)
		*buff = va_arg(argc, long long);
	else if (form->len == j)
		*buff = va_arg(argc, intmax_t);
	else if (form->len == z)
		*buff = va_arg(argc, size_t);
	else
		*buff = va_arg(argc, int);
}

static void		apply_flags(t_form *form, int *size, int type)
{
	if (form->quote && type == 1)
		fill_quote(form);
	if (form->press >= 0)
	{
		form->zero = 0;
		fill_zero(form);
	}
	if (form->hash && type == 2)
		fill_hash_u(form, (form->type == x || form->type == X) ? 1 : 0);
	if ((form->sign || form->plus || form->space) && type == 1)
		fill_sign(form);
	fill_width(form);
	if (form->type == X)
		ft_strcapitalizer(form->out);
	*size += write(form->fd, form->out, ft_strlen(form->out));
	free(form->out);
}

void			print_memory(t_form *form, va_list argc, int *size)
{
	uintmax_t	mem;

	mem = va_arg(argc, unsigned long long);
	form->out = ft_llitoa_base(mem, 16);
	if (!form->press && !mem)
		ft_bzero(form->out, ft_strlen(form->out));
	if (form->press >= 0)
		fill_zero(form);
	form->hash = 1;
	fill_hash_u(form, 1);
	fill_width(form);
	*size += write(form->fd, form->out, ft_strlen(form->out));
	free(form->out);
}

void			parse_int(t_form *form, va_list argc, int *size, int type)
{
	intmax_t	buff;
	uintmax_t	ubuff;

	if (type == 1)
	{
		len_cast(form, argc, &buff);
		form->out = ft_llitoa(buff);
		if (buff < 0)
			form->sign = 1;
	}
	else
	{
		len_cast_u(form, argc, &ubuff);
		if (form->type == u || form->type == U)
			form->out = ft_llitoa_base(ubuff, 10);
		else if (form->type == b)
			form->out = ft_llitoa_base(ubuff, 2);
		else if (form->type == o || form->type == O)
			form->out = ft_llitoa_base(ubuff, 8);
		else if (form->type == x || form->type == X)
			form->out = ft_llitoa_base(ubuff, 16);
	}
	if (!form->press && (type == 1 ? !buff : !ubuff))
		ft_bzero(form->out, ft_strlen(form->out));
	apply_flags(form, size, type);
}
