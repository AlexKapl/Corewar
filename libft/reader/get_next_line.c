/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:05:33 by akaplyar          #+#    #+#             */
/*   Updated: 2017/05/11 15:40:17 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		gnl_make_line(char **buffer, char **line)
{
	char		*end;
	char		*tmp;

	if ((end = ft_strchr(*buffer, '\n')))
	{
		*end = '\0';
		*line = ft_strdup(*buffer);
		tmp = *buffer;
		if (*(end + 1))
			*buffer = ft_strdup(end + 1);
		else
			*buffer = ft_strnew(0);
		free(tmp);
		return (1);
	}
	else if (**buffer)
	{
		*line = ft_strdup(*buffer);
		tmp = *buffer;
		*buffer = ft_strnew(0);
		free(tmp);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*buffer = NULL;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	if (!line || fd < 0)
		return (-1);
	if (!buffer)
		buffer = ft_strnew(0);
	while (!(ft_strchr(buffer, '\n')))
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!ret)
			return (gnl_make_line(&buffer, line));
		buff[ret] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(tmp, buff);
		free(tmp);
	}
	return (gnl_make_line(&buffer, line));
}
