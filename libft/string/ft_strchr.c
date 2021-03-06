/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:58:32 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/06 21:29:51 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strchr_space(const char *s)
{
	char	*str;

	str = (char*)s;
	while (*str)
	{
		if (ft_isspace(*str))
			return (str);
		str++;
	}
	return (NULL);
}

char		*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (!c ? str : NULL);
}
