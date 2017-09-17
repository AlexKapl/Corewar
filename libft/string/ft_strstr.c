/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 08:47:34 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 18:12:34 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char*)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] == big[i + j] && little[j])
			j++;
		if (j == ft_strlen((char*)little))
			return ((char*)&big[i]);
		i++;
	}
	return (0);
}
