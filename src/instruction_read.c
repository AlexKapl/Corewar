/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:34:23 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:34:24 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		cor_check_types(t_ins *ins)
{
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	while (++i < ins->argc)
	{
		if (ins->types[i] == IND_CODE)
			ins->types[i] = T_IND;
		if (ins->types[i] == T_REG)
			ins->sizes[i] = 1;
		else if (ins->types[i] == T_DIR || ins->types[i] == T_IND)
			ins->sizes[i] = (ins->types[i] == T_DIR ? ins->dir : 2);
		if (!(ins->types[i] & ins->args[i]))
			flag = 1;
	}
	return (flag);
}

static int		cor_decode_args(t_cor *cor, t_ins *ins, int pc)
{
	int			i;

	if (ins->size == 2)
	{
		ins->octal = (unsigned char)ARENA(pc + 1);
		ins->types[0] = (ins->octal & 0xc0) >> 6;
		if (ins->argc > 1)
			ins->types[1] = (ins->octal & 0x30) >> 4;
		if (ins->argc == 3)
			ins->types[2] = (ins->octal & 0xc) >> 2;
	}
	if (cor_check_types(ins))
	{
		i = -1;
		while (++i < ins->argc)
			ins->size += ins->sizes[i];
		return (1);
	}
	else
		return (0);
}

static int		cor_check_ins(t_cor *cor, t_ins *ins, int pc)
{
	int			i;

	i = -1;
	while (++i < ins->argc)
	{
		if (ins->types[i] == T_REG)
		{
			if (ins->args[i] < 1 || ins->args[i] > REG_NUMBER)
				return (1);
			ins->args[i]--;
		}
		else if (ins->types[i] == T_IND && ins->opcode != ST)
		{
			if (ins->opcode == LLD || ins->opcode == LLDI)
				ins->args[i] = cor_read_indir(cor, pc + ins->args[i]);
			else
				ins->args[i] = cor_read_indir(cor, pc + ins->args[i] % IDX_MOD);
		}
		if ((short)ins->args[i] < 0 &&
			((ins->types[i] != T_IND && ins->dir == 2) || ins->opcode == ST))
			ins->args[i] |= 0xffff0000;
	}
	return (0);
}

static void		cor_read_args(t_cor *cor, t_ins *ins, int pc)
{
	int			i;
	int			j;
	int			size;

	i = -1;
	while (++i < ins->argc)
	{
		j = -1;
		ins->args[i] = 0;
		size = ins->sizes[i];
		if (ins->types[i] == T_REG)
			ins->args[i] = ARENA(pc + ins->size++);
		else
			while (++j < size)
			{
				ins->args[i] <<= 8;
				ins->args[i] |= (unsigned char)ARENA(pc + ins->size++);
			}
	}
}

int				cor_read_ins(t_cor *cor, t_proc *proc)
{
	if (cor_decode_args(cor, proc->ins, proc->pc))
		return (0);
	cor_read_args(cor, proc->ins, proc->pc);
	if (cor_check_ins(cor, proc->ins, proc->pc))
		return (0);
	return (1);
}
