/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:00:40 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 18:14:11 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*new;
	char	*ptr;

	if (!s)
		return (NULL);
	if (!(new = (char*)malloc(len + 1)))
		return (NULL);
	ptr = new;
	s += start;
	while (len--)
		*ptr++ = *s++;
	*ptr = '\0';
	return (new);
}
