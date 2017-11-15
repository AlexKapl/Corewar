/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:24 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:37:54 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		cor_aplly_params(t_cor *cor, char *str)
{
	if (!cor->warriors)
		cor_errors(ARG_ERR, str);
	if (cor->visual || cor->stop)
		cor->dump = 0;
	cor->pause = cor->stop;
	if (cor->visual)
		cor->verb = 0;
}

static int		cor_read_params(int ac, char **av, int *i)
{
	if (++*i == ac || !ft_strisdigit(av[*i]))
		cor_errors(ARG_ERR, *av);
	return (ft_atoi(av[*i]));
}

static int		cor_check_params(t_cor *cor, int ac, char **av, int *i)
{
	if (ft_strequ(av[*i], "-N"))
		cor->visual = 1;
	else if (ft_strequ(av[*i], "-a"))
		cor->aff = 1;
	else if (ft_strequ(av[*i], "-p"))
		cor->pl = 1;
	else if (ft_strequ(av[*i], "-d"))
		cor->dump = cor_read_params(ac, av, i);
	else if (ft_strequ(av[*i], "-s"))
		cor->stop = cor_read_params(ac, av, i);
	else if (ft_strequ(av[*i], "-v"))
		cor->verb = cor_read_params(ac, av, i);
	else
	{
		if (ft_strequ(av[*i], "-n"))
		{
			if (++*i == ac || !ft_strisdigit(av[*i]) || *(i + 1) == ac)
				cor_errors(ARG_ERR, *av);
			return (FIRST);
		}
		else
			return (SECOND);
	}
	return (NONE);
}

void			cor_parse_params(t_cor *cor, int ac, char **av)
{
	int			i;
	int			ret;
	int			num[2];
	t_war		*wars[MAX_PLAYERS];

	i = 0;
	num[0] = 0;
	while (++i < ac)
	{
		if (cor->warriors == MAX_PLAYERS)
			cor_errors(MANY_ARG, NULL);
		ret = cor_check_params(cor, ac, av, &i);
		if (ret == FIRST)
		{
			num[1] = ft_atoi(av[i++]);
			wars[cor->warriors++] = cor_read(cor, av[i], -num[1]);
		}
		else if (ret == SECOND)
			wars[cor->warriors++] = cor_read(cor, av[i], -(++num[0]));
	}
	cor_aplly_params(cor, *av);
	cor_struct_wars(cor, wars);
}
