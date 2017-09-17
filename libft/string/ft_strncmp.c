/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:43:40 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 14:41:07 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	if (!*s1)
		return ((unsigned const char)*s1 - (unsigned const char)*s2);
	while (*s1 && n)
	{
		if (*s1 != *s2)
			return ((unsigned const char)*s1 - (unsigned const char)*s2);
		s1++;
		s2++;
		n--;
	}
	if (!n)
		return (0);
	else
		return ((unsigned const char)*s1 - (unsigned const char)*s2);
}
