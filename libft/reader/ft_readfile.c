/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:11:19 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/15 12:11:20 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_readfile(const int fd)
{
	ssize_t	ret;
	char	*buff;
	char	*str;

	str = ft_strnew(1);
	buff = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
		{
			ft_strdel(&str);
			ft_strdel(&buff);
			return (NULL);
		}
		buff[ret] = '\0';
		str = ft_strmake(&str, &buff, FIRST);
	}
	ft_strdel(&buff);
	return (str);
}
