/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:36 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:34:00 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			cor_dump_out(t_cor *cor)
{
	int			i;
	int			hex;
	char		*tmp;

	i = -1;
	hex = BYTE_PER_LINE;
	ft_printf("0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (!(i % BYTE_PER_LINE) && i)
		{
			ft_printf("\n%0#6x :", hex);
			hex += BYTE_PER_LINE;
		}
		ft_printf(" %02x", (unsigned char)ARENA(i));
	}
	ft_printf("\n");
	if (cor->dump)
		exit(0);
	get_next_line(STD_IN, &tmp);
	ft_strdel(&tmp);
	cor->pause += cor->stop;
}

int				cor_bits_get_args(t_proc *proc, int mod)
{
	int			i;
	int			ret1;
	int			ret2;
	t_ins		*ins;

	i = mod == STI ? 1 : 0;
	ins = proc->ins;
	ret1 = ins->types[i] == T_REG ?
		cor_read_reg(proc, ins->args[i]) : ins->args[i] % IDX_MOD;
	if (ins->types[i] == T_REG)
	{
		ins->types[i] = T_DIR;
		ins->args[i] = ret1;
	}
	ret2 = ins->types[i + 1] == T_REG ?
		cor_read_reg(proc, ins->args[i + 1]) : ins->args[i + 1] % IDX_MOD;
	if (ins->types[i + 1] == T_REG)
	{
		ins->types[i + 1] = T_DIR;
		ins->args[i + 1] = ret2;
	}
	if (mod == AND || mod == OR)
		return (mod == AND ? ret1 & ret2 : ret1 | ret2);
	else
		return (mod ? ret1 + ret2 : ret1 ^ ret2);
}

int				cor_read_indir(t_cor *cor, int pc)
{
	int			j;
	int			ret;

	j = 0;
	ret = 0;
	while (j < REG_SIZE)
	{
		ret <<= 8;
		ret |= (unsigned char)ARENA(pc + j++);
	}
	return (ret);
}

int				cor_read_reg(t_proc *proc, int r)
{
	int			i;
	int			reg;

	i = 0;
	reg = 0;
	while (i < REG_SIZE)
	{
		reg <<= 8;
		reg |= (unsigned char)proc->r[r][i];
		i++;
	}
	return (reg);
}

int				corsize(int pos)
{
	if (pos < 0)
		return (pos + MEM_SIZE);
	else
		return (pos % MEM_SIZE);
}
