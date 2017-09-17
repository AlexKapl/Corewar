#include "asm.h"

void			asm_errors(int err, char *str, int line)
{
	if (err == INP_ERR)
		ft_printf("Usage: ./asm [-a] <champion.s>\n");
	else if (err == FILE_ERR)
		ft_printf("Can't read source file %s\n", str);
	else if (err == MLC_ERR)
		ft_printf("Can't allocate memory\n");
	else if (err == LINE_ERR)
		ft_printf("%s %d\n", str);
	exit(err);
}

void			out(t_asm *as)
{
	int 		i;

	i = -1;
	while (++i < as->len)
		ft_printf("%s #| %d\n", as->input[i], i);
}

void			asm_parse(t_asm *as)
{
	int			i;

	out(as);
	i = -1;
	while (++i < as->len)
		if (asm_not_empty_line(as->input[i]))
		{
			if (ft_strncmp(as->input[i], ".name", 5))
				asm_find_name(as, as->input[i], i);
			else if (ft_strncmp(as->input[i], ".comment", 8))
				asm_find_comm(as, as->input[i], i);
		}
}

void			asm_init(t_asm *as)
{
	as->len = 0;
	as->name = NULL;
	as->comm = NULL;
	as->input = NULL;
}

int				main(int ac, char **av)
{
	t_asm		as;

	if (ac != 2)
		asm_errors(INP_ERR, NULL, NONE);
	asm_init(&as);
	asm_input(&as, av[1]);
	asm_parse(&as);
	return (0);
}