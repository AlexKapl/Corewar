/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:46:26 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:47:11 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int		asm_label_arg(t_asm *as, char *str, int i)
{
	as->j = ++i;
	while (str[as->j] && str[as->j] != SEPARATOR_CHAR &&
			!ft_isspace(str[as->j]))
	{
		asm_check_label(as, str[as->j]);
		as->j++;
	}
	if (!str[as->j])
		asm_line_err(as, END_LINE, NULL);
	return (as->j);
}

static int		asm_check_reg(t_asm *as, char *str, int i)
{
	int			reg;

	reg = ft_atoi(str + ++i);
	while (str[i] && str[i] != '#' && !ft_isspace(str[i])
			&& str[i] != SEPARATOR_CHAR)
	{
		if (!ft_isdigit(str[i]))
			asm_command_err(as, INV_ARG,
				ft_strsub(str, (unsigned int)as->j, (size_t)(i - as->j + 1)));
		i++;
	}
	if (reg > REG_NUMBER)
		asm_command_err(as, INV_REG,
				ft_strsub(str, (unsigned int)as->j, (size_t)(i - as->j)));
	return (i);
}

static void		asm_check_chars(t_asm *as, char *str, int i)
{
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '#')
			return ;
		else if (str[i] == SEPARATOR_CHAR)
			as->j = ++i;
		else if (str[i] == 'r')
			i = asm_check_reg(as, str, i);
		else if (str[i] == LABEL_CHAR)
			i = asm_label_arg(as, str, i);
		else if (str[i] != DIRECT_CHAR && !ft_isdigit(str[i])
				&& !ft_isspace(str[i]))
			asm_command_err(as, INV_ARG,
				ft_strsub(str, (unsigned int)as->j, (size_t)(i - as->j + 1)));
		else
			i++;
	}
	as->j = i;
}

static void		asm_check_type(t_asm *as, t_ins *ins)
{
	int			i;

	if (!(ins->types = (char*)malloc((size_t)ins->comm->argc)))
		asm_errors(MLC_ERR, NULL);
	i = 0;
	while (i < ins->comm->argc)
	{
		if (ins->args[i][0] == 'r')
			ins->types[i] = T_REG;
		else if (ins->args[i][0] == '%')
			ins->types[i] = T_DIR;
		else
			ins->types[i] = T_IND;
		if (!(ins->types[i] & ins->comm->args[i]))
			asm_command_err(as, (INV_TYPE | i), ins->comm->name);
		if (ins->types[i] == T_IND)
			ins->types[i] = IND_CODE;
		i++;
	}
}

void			asm_check_args(t_asm *as, t_ins *ins, char *str)
{
	int			i;
	char		*tmp;

	i = as->j;
	asm_check_chars(as, str, as->j);
	if (!(tmp = ft_strsub(str, (unsigned int)i, (size_t)(as->j - i))))
		asm_errors(MLC_ERR, NULL);
	if (!(ins->args = ft_strsplit(tmp, ',')))
		asm_errors(MLC_ERR, NULL);
	ft_strdel(&tmp);
	if (ft_tabcount(ins->args) != ins->comm->argc)
		asm_command_err(as, INV_COUNT, ins->comm->name);
	asm_sub_args(ins);
	asm_check_type(as, ins);
	ft_lst_push_back(&as->tmp, ft_lstnew_struct(ins, 1, asm_new_ins));
}
