/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:49:27 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:49:55 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		asm_encrypt(t_asm *as, t_ins *ins, t_out *out)
{
	int			i;
	int			shift;

	i = 0;
	shift = 6;
	out->pos = as->size_out;
	out->octal = 0;
	out->opcode = ins->comm->opcode;
	out->size = (ins->comm->octal ? 2 : 1);
	while (i < ins->comm->argc)
	{
		if (ins->comm->octal)
			out->octal |= (ins->types[i] << shift);
		if (ins->types[i] == REG_CODE)
			out->size++;
		else if (ins->types[i] == IND_CODE)
			out->size += 2;
		else
			out->size += ins->comm->dir;
		shift -= 2;
		i++;
	}
	as->size_out += out->size;
}

static int		asm_find_label(t_asm *as, t_ins *ins, t_out *out, int type)
{
	int			i;
	char		*name;

	if (ins->args[as->i][0] == ':' || ins->args[as->i][1] == ':')
	{
		name = ins->args[as->i] + type + 1;
		i = 0;
		while (as->ins[i])
		{
			if (ft_strequ(as->ins[i]->label, name))
				return ((int)as->out[i]->pos - (int)out->pos);
			i++;
		}
		as->i = ins->line;
		as->name = ins->comm->name;
		asm_command_err(as, INV_LABEL, name);
	}
	else
		return (ft_atoi(ins->args[as->i] + type));
	return (-1);
}

static void		asm_dir_encrypt(t_asm *as, t_ins *ins, t_out *out, int val)
{
	int			size;
	unsigned	value;

	value = 0;
	size = (ins->types[as->i] == DIR_CODE ? ins->comm->dir : 2);
	if (val < 0)
		value = (unsigned int)(1 << (size << 3));
	value += val;
	while (--size >= 0)
		out->args[as->j++] = (short)((value >> (size << 3)) & 255);
	out->val[as->i] = val;
}

static void		asm_args_encrypt(t_asm *as, t_ins *ins, t_out *out)
{
	int			value;

	as->i = 0;
	as->j = 0;
	if (!(out->args = (short*)malloc(sizeof(short) * out->size)))
		asm_errors(MLC_ERR, NULL);
	if (!(out->val = (int*)malloc(sizeof(int) * out->size)))
		asm_errors(MLC_ERR, NULL);
	while (as->i < ins->comm->argc)
	{
		if (ins->types[as->i] == REG_CODE)
		{
			out->val[as->i] = ft_atoi(ins->args[as->i] + 1);
			out->args[as->j++] = (char)out->val[as->i];
		}
		else
		{
			value = asm_find_label(as, ins, out,
					(ins->types[as->i] == DIR_CODE ? 1 : 0));
			asm_dir_encrypt(as, ins, out, value);
		}
		as->i++;
	}
}

void			asm_encode(t_asm *as)
{
	int			i;

	i = 0;
	while (as->ins[i])
	{
		if (as->out[i]->size)
			asm_encrypt(as, as->ins[i], as->out[i]);
		else
			as->out[i]->pos = as->size_out;
		i++;
	}
	i = 0;
	while (as->ins[i])
	{
		if (as->out[i]->size)
			asm_args_encrypt(as, as->ins[i], as->out[i]);
		i++;
	}
}
