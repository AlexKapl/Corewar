/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:51:15 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:26:17 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_op			g_op[] =
{
	{"live", 1, {T_DIR}, 1, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"fork", 1, {T_DIR}, 12, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 0, 2},
	{"aff", 1, {T_REG}, 16, 1, 0},
};

static void		asm_input(t_asm *as, char *file)
{
	int			i;
	int			fd;
	char		*buff;

	i = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		asm_errors(FILE_ERR, file);
	if (!(as->file = ft_readfile(fd)))
		asm_errors(FILE_ERR, file);
	close(fd);
	as->len = ft_strcount(as->file, '\n');
	if (!(as->input = (char**)malloc(sizeof(*as->input) * as->len)))
		asm_errors(MLC_ERR, NULL);
	buff = as->file;
	while (i < as->len)
	{
		as->input[i++] = buff;
		buff = (ft_strchr(buff, '\n') + 1);
	}
	if (*(buff + 1) && *ft_space_skip(buff + 1))
		asm_line_err(as, END_LINE, NULL);
}

static void		asm_parse(t_asm *as)
{
	char		*str;

	while (as->i < as->len)
	{
		as->j = 0;
		if ((str = asm_not_empty_line(as, as->input[as->i])))
		{
			if (!ft_strncmp(str, COMMENT_CMD_STRING, as->comm_len))
				asm_find_comment(as);
			else if (!ft_strncmp(str, NAME_CMD_STRING, as->name_len))
				asm_find_name(as);
			else
				asm_find_command(as);
		}
		as->i++;
	}
	if (!as->tmp)
		asm_command_err(as, NO_COMM, "ARE YOU SERIOUS???");
	asm_struct_commands(as);
	ft_strdel(&as->file);
	ft_memdel((void*)&as->input);
}

static t_asm	*asm_init(void)
{
	t_asm		*as;

	if (!(as = (t_asm*)ft_memalloc(sizeof(t_asm))))
		asm_errors(MLC_ERR, NULL);
	as->magic = ft_bit_swap(COREWAR_EXEC_MAGIC);
	as->name_len = ft_strlen(NAME_CMD_STRING);
	as->comm_len = ft_strlen(COMMENT_CMD_STRING);
	return (as);
}

int				main(int ac, char **av)
{
	t_asm		*as;
	char		*file;

	as = asm_init();
	if (ac != 2)
	{
		if (ac == 3 && ft_strequ(av[1], "-a"))
			as->a = 1;
		else
			asm_errors(INP_ERR, NULL);
	}
	file = as->a ? av[2] : av[1];
	asm_input(as, file);
	asm_parse(as);
	asm_encode(as);
	asm_print_out(as, file);
	return (0);
}
