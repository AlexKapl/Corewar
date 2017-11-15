/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:51:31 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/17 18:26:46 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		asm_check_rest(t_asm *as, char *str)
{
	size_t		x;

	x = 0;
	while (str[as->j] && str[as->j] != '\n')
	{
		if (str[as->j] == '#')
			return ;
		else if (!ft_isspace(str[as->j]))
		{
			while (str[as->j + x] && str[as->j + x] != '\n')
				x++;
			asm_line_err(as, SYNTAX, ft_strsub(str, (unsigned int)as->j, x));
		}
		as->j++;
	}
	if (!str[as->j])
		asm_line_err(as, END_LINE, NULL);
}

static void		asm_check_char(t_asm *as, char c, int quotes, int mod)
{
	if (!quotes)
	{
		if (c == '\n' || c == '#')
			asm_line_err(as, NO_NAME,
					mod ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		else if (!ft_isspace(c))
			asm_line_err(as, NO_QUOTE_1, NULL);
	}
	else if (c == '#')
		asm_line_err(as, NO_QUOTE_2, NULL);
	if (c == '\n')
	{
		as->j = -1;
		if (++as->i == as->len)
			asm_line_err(as, NO_QUOTE_2, NULL);
	}
}

static size_t	asm_check_value(t_asm *as, char *str, int mod)
{
	int			quotes;
	int			i;
	size_t		size;

	i = as->j;
	size = 0;
	quotes = 0;
	while (str[i] && quotes < 2)
	{
		if (str[i] == '"')
			quotes++;
		else
			asm_check_char(as, str[i], quotes, mod);
		size++;
		i++;
		as->j++;
	}
	asm_check_rest(as, as->input[as->i]);
	return (size);
}

void			asm_find_name(t_asm *as)
{
	int			i;
	int			j;
	size_t		size;

	if (as->name)
		asm_line_err(as, NAME_TWICE, NAME_CMD_STRING);
	as->j += as->name_len;
	as->j += ft_space_skip_i(as->input[as->i] + as->j);
	i = as->i;
	j = as->j + 1;
	size = asm_check_value(as, as->input[as->i], FIRST) - 2;
	if (size > NAME_LEN)
		asm_line_err(as, NAME_LONG, NULL);
	if (!(as->name = ft_strnew(NAME_LEN)))
		asm_errors(MLC_ERR, NULL);
	as->name = ft_strncpy(as->name, as->input[i] + j, size);
}

void			asm_find_comment(t_asm *as)
{
	int			i;
	int			j;
	size_t		size;

	if (as->comm)
		asm_line_err(as, NAME_TWICE, COMMENT_CMD_STRING);
	as->j += as->comm_len;
	as->j += ft_space_skip_i(as->input[as->i] + as->j);
	i = as->i;
	j = as->j + 1;
	size = asm_check_value(as, as->input[as->i], SECOND) - 2;
	if (size > COMM_LEN)
		asm_line_err(as, COMM_LONG, NULL);
	if (!(as->comm = ft_strnew(COMM_LEN)))
		asm_errors(MLC_ERR, NULL);
	as->comm = ft_strncpy(as->comm, as->input[i] + j, size);
}
