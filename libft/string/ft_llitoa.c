/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 18:46:35 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/31 02:49:04 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void		make_str_base(uintmax_t value, char *str, int base, int *i)
{
	static char	tmp[] = "0123456789abcdef";

	if (value >= (uintmax_t)base)
		make_str_base(value / base, str, base, i);
	str[(*i)++] = tmp[value % base];
}

static void		make_str_dec(intmax_t value, char *str, int *i)
{
	static char	tmp[] = "0123456789";

	if (value > 9 || value < -9)
		make_str_dec(value / 10, str, i);
	str[(*i)++] = tmp[value < 0 ? -(value % 10) : (value % 10)];
}

char			*ft_llitoa(intmax_t value)
{
	int			i;
	char		*str;

	i = 0;
	if (!(str = (char*)malloc(32)))
		return (NULL);
	make_str_dec(value, str, &i);
	str[i] = '\0';
	return (str);
}

char			*ft_llitoa_base(uintmax_t value, int base)
{
	int			i;
	char		*str;

	i = 0;
	if (base < 2 || base > 16 || !(str = (char*)malloc(32)))
		return (NULL);
	make_str_base(value, str, base, &i);
	str[i] = '\0';
	return (str);
}
