/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:39 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:29:28 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void				cor_struct_wars(t_cor *cor, t_war *wars[])
{
	int				i;

	i = 0;
	if (!(cor->warrior = (t_war**)ft_memalloc(sizeof(t_war*) * cor->warriors)))
		cor_errors(MLC_ERR, NULL);
	while (i < cor->warriors)
	{
		cor->warrior[i] = wars[i];
		cor->warrior[i]->process->war = i;
		i++;
	}
	cor->cycle_to_die = CYCLE_TO_DIE;
}

static void			cor_read_int(t_war *war, int fd, char *file, int mod)
{
	unsigned		magic;

	if (read(fd, &magic, 0) < 0)
		cor_errors(READ_ERR, file);
	if (mod == FIRST)
	{
		read(fd, &magic, 4);
		if (ft_bit_swap(magic) != COREWAR_EXEC_MAGIC)
			cor_errors(HEADER_ERR, file);
	}
	else if (mod == SECOND)
	{
		read(fd, &war->size, 4);
		war->size = ft_bit_swap(war->size);
	}
	else
		read(fd, &magic, 4);
}

static void			cor_process_init(t_cor *cor, t_war **warrior, int war_num)
{
	int				i;
	t_proc			*proc;

	if (!(proc = (t_proc*)ft_memalloc(sizeof(t_proc))))
		cor_errors(MLC_ERR, NULL);
	if (!(proc->r = (char**)ft_memalloc(sizeof(char*) * REG_NUMBER)))
		cor_errors(MLC_ERR, NULL);
	if (!(proc->ins = (t_ins*)ft_memalloc(sizeof(t_ins))))
		cor_errors(MLC_ERR, NULL);
	i = -1;
	while (++i < REG_NUMBER)
		if (!(proc->r[i] = (char*)ft_memalloc(REG_SIZE)))
			cor_errors(MLC_ERR, NULL);
	i = -1;
	while (++i < REG_SIZE)
		proc->r[0][i] = (char)(war_num >> ((REG_SIZE - i - 1) << 3) & 0xff);
	proc->id = ++cor->proc_num;
	proc->next = cor->process;
	cor->process = proc;
	(*warrior)->process = proc;
}

static void			cor_player_init(t_cor *cor, t_war **warrior, int war_num)
{
	t_war			*war;

	if (!(war = (t_war*)ft_memalloc(sizeof(t_war))))
		cor_errors(MLC_ERR, NULL);
	if (!(war->name = ft_strnew(PROG_NAME_LENGTH)))
		cor_errors(MLC_ERR, NULL);
	if (!(war->comm = ft_strnew(COMMENT_LENGTH)))
		cor_errors(MLC_ERR, NULL);
	war->pl = war_num;
	war->proc_count = 1;
	cor_process_init(cor, &war, war_num);
	*warrior = war;
}

t_war				*cor_read(t_cor *cor, char *file, int war_num)
{
	int				fd;
	t_war			*war;

	if ((fd = open(file, O_RDONLY)) < 0)
		cor_errors(OPEN_ERR, file);
	cor_player_init(cor, &war, war_num);
	cor_read_int(war, fd, file, FIRST);
	read(fd, war->name, PROG_NAME_LENGTH);
	cor_read_int(war, fd, file, NONE);
	cor_read_int(war, fd, file, SECOND);
	if (war->size >= CHAMP_MAX_SIZE)
		cor_errors(LARGE_SIZE, file);
	read(fd, war->comm, COMMENT_LENGTH);
	cor_read_int(war, fd, file, NONE);
	if (!(war->code = ft_strnew(war->size)))
		cor_errors(MLC_ERR, NULL);
	if (read(fd, war->code, war->size) < war->size)
		cor_errors(SIZE_ERR, file);
	if (read(fd, war->code, 1))
		cor_errors(SIZE_ERR, file);
	close(fd);
	return (war);
}
