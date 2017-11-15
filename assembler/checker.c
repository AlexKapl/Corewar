/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:47:32 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:59:37 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char					*asm_not_empty_line(t_asm *as, char *line)
{
	char				*str;

	str = ft_space_skip(line);
	as->j += ft_space_skip_i(line);
	if (*str != '#' && *str != '\n')
		return (str);
	else
		return (NULL);
}

void					asm_sub_args(t_ins *ins)
{
	int					i;
	char				*tmp;
	char				*find;

	i = -1;
	while (++i < ins->comm->argc)
	{
		tmp = ins->args[i];
		ins->args[i] = ft_space_skip(ins->args[i]);
		find = ft_strchr_space(ins->args[i]);
		if (find)
			ins->args[i] = ft_strsub(ins->args[i], 0, find - ins->args[i]);
		else
			ins->args[i] = ft_strdup(ins->args[i]);
		ft_strdel(&tmp);
	}
}

void					asm_check_label(t_asm *as, char c)
{
	static const char	label[] = LABEL_CHARS;
	char				*ptr;

	ptr = (char*)label;
	while (*ptr)
	{
		if (*ptr == c)
			return ;
		ptr++;
	}
	asm_command_err(as, INV_CHAR, &c);
}

void					asm_struct_commands(t_asm *as)
{
	int					i;
	t_list				*list;

	list = as->tmp;
	i = ((int)ft_lstcount(list) + 1);
	if (!(as->ins = (t_ins**)ft_memalloc(sizeof(t_ins*) * i)))
		asm_errors(MLC_ERR, NULL);
	if (!(as->out = (t_out**)ft_memalloc(sizeof(t_out*) * i)))
		asm_errors(MLC_ERR, NULL);
	i = 0;
	while (list)
	{
		if (!(as->out[i] = (t_out*)malloc(sizeof(t_out))))
			asm_errors(MLC_ERR, NULL);
		as->out[i]->size = (list->content_size ? 1 : 0);
		as->ins[i++] = (t_ins*)list->content;
		list = list->next;
	}
	ft_lstdel(&as->tmp, NULL);
}

int						asm_new_ins(const void *data,
						size_t size, t_list **node)
{
	t_ins				*ins;
	t_ins				*tmp;

	if (!(ins = (t_ins*)malloc(sizeof(*ins))))
		asm_errors(MLC_ERR, NULL);
	tmp = (t_ins*)data;
	ins->label = tmp->label;
	ins->line = tmp->line;
	if (!size)
	{
		ins->args = NULL;
		ins->comm = NULL;
		ins->types = NULL;
	}
	else
	{
		ins->args = tmp->args;
		ins->comm = tmp->comm;
		ins->types = tmp->types;
	}
	(*node)->content = (void*)ins;
	(*node)->content_size = size;
	return (1);
}
