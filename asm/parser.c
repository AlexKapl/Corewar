#include "asm.h"

int				asm_not_empty_line(char *line)
{
	char		*str;

	str = line;
	while (*str)
	{
		if (!ft_isspace(*str) && *str != '#')
			return (1);
		else if (*str == '#')
			return (0);
		str++;
	}
	return (0);
}

void			asm_find_name(t_asm *as, char *line, int num)
{
	if (as->name)
		asm_errors(LINE_ERR, "Error: command \".name used\" twice at", num);
}

void			asm_find_comm(t_asm *as, char *line, int num)
{
	if (as->name)
		asm_errors(LINE_ERR, "Error: command \".comment used\" twice at", num);

}
