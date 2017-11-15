/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:27:32 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:27:33 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static t_opt	g_opt[16] =
{
	{1, "live", {T_DIR}, 10, 0, 4},
	{2, "ld", {T_DIR | T_IND, T_REG}, 5, 1, 4},
	{2, "st", {T_REG, T_IND | T_REG}, 5, 1, 4},
	{3, "add", {T_REG, T_REG, T_REG}, 10, 1, 4},
	{3, "sub", {T_REG, T_REG, T_REG}, 10, 1, 4},
	{3, "and", {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{3, "or", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{3, "xor", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{1, "zjmp", {T_DIR}, 20, 0, 2},
	{3, "ldi", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2},
	{3, "sti", {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2},
	{1, "fork", {T_DIR}, 800, 0, 2},
	{2, "lld", {T_DIR | T_IND, T_REG}, 10, 1, 4},
	{3, "lldi", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2},
	{1, "lfork", {T_DIR}, 1000, 0, 2},
	{1, "aff", {T_REG}, 2, 1, 4}
};

void			cor_make_ins(t_cor *cor, t_proc *proc)
{
	int			i;
	int			num;

	num = (unsigned char)ARENA(proc->pc);
	if (num < 1 || num > 16)
	{
		if (cor->vis)
			vis_move_pc(cor, proc, 1);
		proc->pc = corsize(++proc->pc);
		proc->cycle = 0;
		return ;
	}
	proc->cycle++;
	proc->ins->opcode = num--;
	proc->ins->name = g_opt[num].name;
	proc->ins->argc = g_opt[num].argc;
	i = -1;
	while (++i < proc->ins->argc)
		proc->ins->args[i] = g_opt[num].args[i];
	proc->ins->types[0] = g_opt[num].args[0];
	proc->ins->size = g_opt[num].octal + 1;
	proc->ins->cycles = g_opt[num].cycles;
	proc->ins->dir = g_opt[num].dir;
}
