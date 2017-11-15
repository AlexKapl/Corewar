/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:52:30 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:53:07 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void			asm_print_header(t_asm *as, int fd, unsigned size)
{
	int				i;

	write(fd, &as->magic, 4);
	i = 0;
	while (i < NAME_LEN)
		write(fd, &as->name[i++], 1);
	i = 0;
	write(fd, &i, 4);
	size = ft_bit_swap(size);
	write(fd, &size, 4);
	while (i < COMM_LEN)
		write(fd, &as->comm[i++], 1);
	i = 0;
	write(fd, &i, 4);
}

static void			asm_print_instructions(t_asm *as, int fd)
{
	int				i;
	int				j;
	size_t			size;

	i = 0;
	while (as->out[i])
	{
		if (as->out[i]->size)
		{
			j = 0;
			size = as->out[i]->size - (as->out[i]->octal ? 2 : 1);
			write(fd, &as->out[i]->opcode, 1);
			if (as->out[i]->octal)
				write(fd, &as->out[i]->octal, 1);
			while (j < (int)size)
				write(fd, &as->out[i]->args[j++], 1);
		}
		i++;
	}
}

static void			asm_dump_args(t_asm *as, t_ins *ins, t_out *out, int size)
{
	ft_printf("%-4d", out->opcode);
	out->octal ? ft_printf("%-6hu", out->octal) : ft_printf("      ");
	as->i = -1;
	as->j = 0;
	while (++as->i < ins->comm->argc)
	{
		if (ins->types[as->i] == REG_CODE)
			ft_printf("%-18d", out->args[as->j++]);
		else
		{
			size = (ins->types[as->i] == DIR_CODE ? ins->comm->dir : 2);
			while (--size >= 0)
				ft_printf("%-4hu", out->args[as->j++]);
			size = (ins->types[as->i] == DIR_CODE ? ins->comm->dir : 2);
			size == 2 ? ft_printf("          ") : ft_printf("  ");
		}
	}
	ft_printf("\n\t\t\t\t\t");
	ft_printf("%-4d", out->opcode);
	out->octal ? ft_printf("%-6hu", out->octal) : ft_printf("      ");
	as->i = 0;
	while (as->i < ins->comm->argc)
		ft_printf("%-18d", out->val[as->i++]);
}

static void			asm_print_dump(t_asm *as, char *name)
{
	int				i;
	int				j;

	ft_printf("Dumping program \"%s\" on standart output\n", name);
	ft_printf("Program size: %zu bytes\n", as->size_out);
	ft_printf("Name: \"%s\"\nComment: \"%s\"\n\n", as->name, as->comm);
	i = 0;
	while (as->out[i])
	{
		if (as->ins[i]->label)
			ft_printf("%-5zu\t  :\t%s:\n", as->out[i]->pos, as->ins[i]->label);
		if (as->out[i]->size)
		{
			ft_printf("%-5zu(%3zu) :\t\t", as->out[i]->pos, as->out[i]->size);
			ft_printf("%-10s", as->ins[i]->comm->name);
			j = 0;
			while (j < as->ins[i]->comm->argc)
				ft_printf("%-18s", as->ins[i]->args[j++]);
			ft_printf("\n\t\t\t\t\t");
			asm_dump_args(as, as->ins[i], as->out[i], NONE);
			ft_printf("\n\n");
		}
		i++;
	}
}

void				asm_print_out(t_asm *as, char *file)
{
	int				fd;
	int				len;

	len = (int)ft_strlen(file);
	if (file[len - 1] != 's' || file[len - 2] != '.')
		asm_errors(NAME_ERR, file);
	file = ft_strsub(file, 0, (size_t)(len - 2));
	file = ft_strmake(file, ".cor", FIRST);
	if (as->a)
		asm_print_dump(as, file);
	else
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC,
				S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
		if (fd < 0)
			asm_errors(OPEN_ERR, file);
		ft_printf("Writing output program to \"%s\"\n", file);
		asm_print_header(as, fd, as->size_out);
		asm_print_instructions(as, fd);
		close(fd);
	}
	ft_strdel(&file);
}
