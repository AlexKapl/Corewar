/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:28:18 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:37:12 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void		cor_jump_out(t_proc *proc)
{
	ft_printf(" %d", proc->ins->args[0]);
	if (proc->ins->opcode == JUMP)
	{
		if (proc->carry)
			ft_printf(" OK\n");
		else
			ft_printf(" FAILED\n");
	}
	else
		ft_printf(" (%d)\n", proc->out);
}

static void		cor_index_out(t_proc *proc)
{
	ft_printf("       | -> ");
	if (proc->ins->opcode == STI)
		ft_printf("store to %d + %d = %d (with pc and mod %d)\n",
				proc->ins->args[1], proc->ins->args[2],
				proc->ins->args[1] + proc->ins->args[2], proc->out);
	else
		ft_printf("load from %d + %d = %d (with pc and mod %d)\n",
				proc->ins->args[0], proc->ins->args[1],
				proc->ins->args[0] + proc->ins->args[1], proc->out);
}

static void		cor_print_args(t_proc *proc)
{
	int			i;

	i = 0;
	while (i < proc->ins->argc)
	{
		if (proc->ins->types[i] == T_REG)
			ft_printf(" r%d", proc->ins->args[i] + 1);
		else
			ft_printf(" %d", proc->ins->args[i]);
		i++;
	}
	ft_printf("\n");
}

void			cor_operation_out(t_cor *cor, t_proc *proc)
{
	if (cor->verb & 0x4)
	{
		ft_printf("P %4d | %-4s", proc->id, proc->ins->name);
		if (proc->ins->opcode == JUMP || proc->ins->opcode == FORK
			|| proc->ins->opcode == LFORK)
			cor_jump_out(proc);
		else
			cor_print_args(proc);
		if (proc->ins->opcode == STI || proc->ins->opcode == LDI
			|| proc->ins->opcode == LLDI)
			cor_index_out(proc);
	}
}

void			cor_aff(t_cor *cor, t_proc *proc)
{
	int				reg;
	unsigned char	c;

	if (cor->aff)
	{
		reg = cor_read_reg(proc, proc->ins->args[0]);
		c = (unsigned char)(reg % 256);
		ft_printf("Aff: ");
		write(1, &c, 1);
		ft_printf("\n");
	}
	cor_operation_out(cor, proc);
}
