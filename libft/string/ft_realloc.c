/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:52:36 by akaplyar          #+#    #+#             */
/*   Updated: 2017/01/24 18:18:13 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_realloc(char *str, size_t len)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = str;
	str = (char*)malloc(sizeof(str) * len);
	if (!str)
		return (NULL);
	str = ft_strcpy(str, ptr);
	free(ptr);
	return (str);
}
