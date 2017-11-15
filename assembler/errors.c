/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:50:03 by akaplyar          #+#    #+#             */
/*   Updated: 2017/10/16 16:51:03 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			asm_errors(int err, char *str)
{
	ft_printf("{red}");
	if (err == INP_ERR)
		ft_printf("Usage: ./asm [-a] <champion.s>\n");
	else if (err == FILE_ERR)
		ft_printf("Can't read source file \"%s\"\n", str);
	else if (err == MLC_ERR)
		ft_printf("Can't allocate memory\n");
	else if (err == OPEN_ERR)
		ft_printf("Can't open/create file \"%s\"\n", str);
	else if (err == NAME_ERR)
		ft_printf("Invalid file name \"%s\"\nFile must ends with '.s'\n", str);
	exit(err);
}

static void		asm_command_err_sec(t_asm *as, int err, char *str)
{
	if (err == INV_COUNT)
		ft_printf("Incorrect %s \"%s\" at line[%03d]\n",
				"arguments count for instruction", str, as->i + 1);
	else if (err == INV_LABEL)
		ft_printf("No such label \"%s\" for instruction \"%s\" at line[%03d]\n",
				str, as->name, as->i + 1);
	exit(err);
}

void			asm_command_err(t_asm *as, int err, char *str)
{
	ft_printf("{red}");
	if (err == INV_CHAR)
		ft_printf("Invalid char at [%03d:%03d] - '%c'\n",
				as->i + 1, as->j + 1, *str);
	else if (err == INV_COMM)
		ft_printf("Invalid instruction at [%03d:%03d] - \"%s\"",
				as->i + 1, as->j + 1, str);
	else if (err == NO_COMM)
		ft_printf("Champion don't have any instruction!\n%s\n", str);
	else if (err == NO_ARGS)
		ft_printf("Missing arguments for instruction \"%s\" at [%03d:%03d]\n",
				str, as->i + 1, as->j + 1);
	else if (err == INV_ARG)
		ft_printf("Invalid argument at [%03d:%03d] - \"%s\"\n",
				as->i + 1, as->j + 1, str);
	else if (err == INV_REG)
		ft_printf("Invalid registry number at [%03d:%03d] - \"%s\"\n",
				as->i + 1, as->j + 1, str);
	else if (err & INV_TYPE)
		ft_printf("Invalid parameter type for parameter [%d] for instruction "
			"\"%s\" on line [%03d]\n", (err ^ INV_TYPE) + 1, str, as->i + 1);
	else
		asm_command_err_sec(as, err, str);
	exit(err);
}

void			asm_line_err(t_asm *as, int err, char *str)
{
	ft_printf("{red}");
	if (err == NO_LINE)
		ft_printf("Error: missing command \"%s\"\n", str);
	else if (err == END_LINE)
		ft_printf("Error: missing newline at the end of input\n");
	else if (err == NAME_LONG)
		ft_printf("Champion label too long. Max length - %d\n", NAME_LEN);
	else if (err == COMM_LONG)
		ft_printf("Champion comment too long. Max length - %d\n", COMM_LEN);
	else if (err == NO_NAME)
		ft_printf("Error: missing value for command \"%s\" at [%03d:%03d]\n",
				str, as->i + 1, as->j + 1);
	else if (err == NO_QUOTE_1)
		ft_printf("Error: missing quotes before value at [%03d:%03d]\n",
				as->i + 1, as->j + 1);
	else if (err == NO_QUOTE_2)
		ft_printf("Error: missing quotes after value at [%03d:%03d]\n",
				as->i + 1, as->j + 1);
	else if (err == NAME_TWICE)
		ft_printf("command \"%s\" used twice at line[%03d]\n", str, as->i + 1);
	else if (err == SYNTAX)
		ft_printf("Syntax error at [%03d:%03d] INSTRUCTION \"%s\"\n",
				as->i + 1, as->j + 1, str);
	exit(err);
}
