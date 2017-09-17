/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 09:44:20 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 14:42:44 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int				ft_atoi(const char *str)
{
	int		i;
	int		nbr;

	nbr = 0;
	i = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		i = (*str == '-' ? -1 : 1);
		str++;
	}
	while (*str && *str >= 48 && *str <= 57)
		nbr = (nbr * 10) + (*str++ - 48);
	return (nbr * i);
}
