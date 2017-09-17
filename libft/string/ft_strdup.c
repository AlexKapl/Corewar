/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:59:08 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 18:15:02 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	char	*ptr;

	if (!(new = (char *)malloc(ft_strlen(s1) + 1)))
		return (NULL);
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (new);
}
