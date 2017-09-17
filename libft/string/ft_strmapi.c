/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:41:09 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 18:12:58 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (s && f)
	{
		str = (char *)malloc(ft_strlen(s) + 1);
		if (!str)
			return (NULL);
		i = 0;
		if (s)
			while (s[i])
			{
				str[i] = f(i, s[i]);
				i++;
			}
		str[i] = '\0';
		return (str);
	}
	else
		return (NULL);
}
