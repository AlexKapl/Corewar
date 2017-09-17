/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:56:53 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/01 20:45:14 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	count(const char *s, char c)
{
	size_t		j;
	size_t		flag;

	j = 0;
	flag = 0;
	while (*s != '\0')
	{
		while (*s && *s != c)
		{
			s++;
			flag = 1;
		}
		if (*s && *s == c)
		{
			j++;
			flag = 0;
			s++;
		}
	}
	return (j + 2);
}

static size_t	get_len(const char *s, char c)
{
	size_t		j;

	j = 0;
	while (*s && *s != c)
	{
		j++;
		s++;
	}
	return (j);
}

static char		**fill_tab(char **tab, const char *s, char c)
{
	int			x;
	int			j;

	x = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			j = 0;
			tab[x] = (char*)malloc(sizeof(*tab) * get_len(s, c));
			while (*s && *s != c)
				tab[x][j++] = *s++;
			tab[x++][j] = '\0';
		}
	}
	tab[x] = 0;
	return (tab);
}

char			**ft_strsplit(const char *s, char c)
{
	char		**tab;

	if (s)
	{
		tab = (char**)malloc(sizeof(tab) * (count(s, c)));
		if (!tab)
			return (0);
		else
			return (fill_tab(tab, s, c));
	}
	else
		return (0);
}
