/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:31:38 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:49 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*ptr;

	if (s)
	{
		str = (char *)malloc(ft_strlen(s) + 1);
		if (!str)
			return (NULL);
		ptr = str;
		if (s)
			while (*s)
				*ptr++ = f(*s++);
		*ptr = '\0';
		return (str);
	}
	else
		return (NULL);
}
