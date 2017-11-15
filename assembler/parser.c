/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:52:18 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:52:19 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		asm_check_command(t_asm *as, t_ins *ins, char *str)
{
	int			i;
	int			start;
	char		*name;

	start = as->j;
	while (str[as->j] && !ft_isspace(str[as->j]) && str[as->j] != '#')
		as->j++;
	if (!(name = ft_strsub(str, (unsigned int)start, (size_t)as->j - start)))
		asm_errors(MLC_ERR, 0);
	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_op[i].name, name))
		{
			ins->comm = &g_op[i];
			break ;
		}
		i++;
	}
	if (i == 16)
		asm_command_err(as, INV_COMM, name);
	ft_strdel(&name);
}

static void		asm_find_label(t_asm *as, t_ins *ins, char *str)
{
	int			j;

	j = as->j;
	while (str[as->j] && str[as->j] != LABEL_CHAR && !ft_isspace(str[as->j]))
	{
		asm_check_label(as, str[as->j]);
		as->j++;
	}
	if (str[as->j] != LABEL_CHAR)
	{
		as->j = j;
		return ;
	}
	if (!(ins->label = ft_strsub(str, (unsigned int)j, (size_t)as->j++)))
		asm_errors(MLC_ERR, 0);
}

void			asm_find_command(t_asm *as)
{
	t_ins		ins;
	char		*str;

	if (!as->name)
		asm_line_err(as, NO_LINE, NAME_CMD_STRING);
	else if (!as->comm)
		asm_line_err(as, NO_LINE, COMMENT_CMD_STRING);
	ins.line = as->i;
	ins.label = NULL;
	str = as->input[as->i];
	asm_find_label(as, &ins, str);
	if (!asm_not_empty_line(as, str + as->j))
	{
		ft_lst_push_back(&as->tmp, ft_lstnew_struct(&ins, 0, asm_new_ins));
		return ;
	}
	asm_check_command(as, &ins, str);
	as->j += ft_space_skip_i(str + as->j);
	if (str[as->j] == '\n' || str[as->j] == '#')
		asm_command_err(as, NO_ARGS, ins.comm->name);
	else if (!str[as->j])
		asm_line_err(as, END_LINE, NULL);
	asm_check_args(as, &ins, str);
}
