/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_skip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:11:06 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:48:25 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int				ft_space_skip_i(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || !ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}

char			*ft_space_skip(char *str)
{
	while (*str)
	{
		if (*str == '\n' || !ft_isspace(*str))
			return (str);
		str++;
	}
	return (str);
}
