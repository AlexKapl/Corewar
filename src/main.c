/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:27:37 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:35:15 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		cor_print_help(char *str)
{
	ft_printf("Usage: %s [-d N -s N -v N -p | -n] [-a] <champion1.cor> <...>\n"
	"-a  \t: Prints output from \"aff\" (Default is to hide it)\n"
	"#### TEXT OUTPUT MODE ##################################################\n"
	"-d N\t: Dumps memory after N cycles then exits\n"
	"-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n"
	"-p  \t: With -v show player num before process id\n"
	"-v N\t: Verbosity levels, can be added together to enable several\n"
	"\t\t- 0 : Show only essentials\n"
	"\t\t- 1 : Show lives\n"
	"\t\t- 2 : Show cycles\n"
	"\t\t- 4 : Show operations (Params are NOT litteral ...)\n"
	"\t\t- 8 : Show deaths\n"
	"\t\t- 16 : Show PC movements (Except for jumps)\n"
	"#### NCURSES OUTPUT MODE ###############################################\n"
	"-N\t: Ncurses output mode\n"
	"########################################################################\n"
			, str);
}

void			cor_errors(int err, char *str)
{
	ft_printf("{red}");
	if (err == ARG_ERR)
		cor_print_help(str);
	else if (err == MANY_ARG)
		ft_printf("Too many champions\n");
	else if (err == OPEN_ERR)
		ft_printf("Can't open source file \"%s\"\n", str);
	else if (err == MLC_ERR)
		ft_printf("Can't allocate memory\n");
	else if (err == READ_ERR)
		ft_printf("Can't read source file \"%s\"\n", str);
	else if (err == HEADER_ERR)
		ft_printf("File \"%s\" has an invalid header\n", str);
	else if (err == SIZE_ERR)
		ft_printf("File \"%s\" has a code size,"
				" that differ from designated in the header\n", str);
	else if (err == LARGE_SIZE)
		ft_printf("The champion from file \"%s\" has too large size\n", str);
	exit(err);
}

static void		cor_fill_field(t_cor *cor)
{
	int			i;
	int			j;
	int			pos;

	if (!cor->visual)
		ft_printf("Introducing warriors\n");
	i = -1;
	while (++i < cor->warriors)
	{
		pos = corsize((MEM_SIZE / cor->warriors) * i);
		cor->warrior[i]->process->pc = pos;
		j = -1;
		while (++j < (int)cor->warrior[i]->size)
			cor->field[pos + j] = cor->warrior[i]->code[j];
		if (!cor->visual)
		{
			ft_printf("Player %d, weighting %u bytes, named \"%s\" ",
					-cor->warrior[i]->pl, cor->warrior[i]->size,
					cor->warrior[i]->name);
			ft_printf("with glorious roar (\"%s\")\n", cor->warrior[i]->comm);
		}
		else
			vis_fill_field(cor, cor->vis, i);
	}
}

int				main(int ac, char **av)
{
	t_cor		*cor;

	if (ac < 2)
		cor_errors(ARG_ERR, *av);
	if (!(cor = (t_cor*)ft_memalloc(sizeof(t_cor))))
		cor_errors(MLC_ERR, NULL);
	if (!(cor->field = (char*)ft_memalloc(MEM_SIZE)))
		cor_errors(MLC_ERR, NULL);
	cor_parse_params(cor, ac, av);
	if (cor->visual)
		vis_init(cor);
	cor_fill_field(cor);
	cor_start_game(cor);
	return (0);
}
