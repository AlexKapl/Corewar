/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:56:11 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 18:21:37 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	temp;

	if (!str)
		return (0);
	len = ft_strlen(str);
	i = -1;
	while (++i < --len)
	{
		temp = *(str + i);
		*(str + i) = *(str + len);
		*(str + len) = temp;
	}
	return (str);
}
