/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 16:31:27 by akaplyar          #+#    #+#             */
/*   Updated: 2017/04/30 16:33:16 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_tabdel(char **tab, int count)
{
	int i;

	i = 0;
	if (count < 0)
		while (tab[i])
			free(tab[i++]);
	else
		while (i < count)
			free(tab[i++]);
	free(tab);
}
