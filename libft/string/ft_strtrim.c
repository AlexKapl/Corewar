/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:29:30 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 14:24:43 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_is_whitespace(char c)
{
	int			a;

	a = 0;
	return (a += (c == ' ' || c == '\n' || c == '\t' ? 1 : 0));
}

static size_t	get_start(const char *str)
{
	size_t		a;

	a = 0;
	while (ft_is_whitespace(str[a]))
		a++;
	return (a);
}

static size_t	get_end(const char *str)
{
	size_t		a;

	a = 0;
	a = ft_strlen(str);
	a--;
	while (ft_is_whitespace(str[a]))
		a--;
	return (++a);
}

char			*ft_strtrim(const char *s)
{
	char		*new;
	char		*ptr;
	size_t		start;
	size_t		end;

	if (!s)
		return (0);
	start = get_start(s);
	end = get_end(s);
	if (!*s || start == ft_strlen(s))
	{
		new = (char*)malloc(1);
		new[0] = '\0';
		return (new);
	}
	new = (char*)malloc(end - start + 1);
	if (!new)
		return (0);
	ptr = new;
	while (start < end)
		*ptr++ = s[start++];
	*ptr = '\0';
	return (new);
}
