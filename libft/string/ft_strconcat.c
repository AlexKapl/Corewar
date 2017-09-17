/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:04:05 by akaplyar          #+#    #+#             */
/*   Updated: 2017/04/02 20:04:07 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char			*ft_strconcat(int count, ...)
{
	va_list		argc;
	char		*str[count];
	char		*ptr;
	char		*ptr1;
	int			i;

	i = 0;
	if (count < 3)
		return (NULL);
	va_start(argc, count);
	if (!(ptr = ft_strdup(va_arg(argc, char*))))
		return (NULL);
	while (++i < count)
	{
		str[i] = va_arg(argc, char*);
		if (!(ptr1 = ft_strjoin(ptr, str[i])))
		{
			free(ptr);
			return (NULL);
		}
		free(ptr);
		ptr = ptr1;
	}
	va_end(argc);
	return (ptr);
}
