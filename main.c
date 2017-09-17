#include "corewar.h"

void		cor_errors(int err)
{
	if (err == ARG_ERR)
		ft_printf("Usage: ./corewar [...] [-a]<champion1.cor> <...>\n");
	exit(err);
}

static void	cor_init(t_cor *cor)
{
	cor->r = ft_memalloc(REG_NUMBER * REG_SIZE);
}

int			main(int ac, char **av)
{
	t_cor	cor;

	cor_init(&cor);
	if (ac < 2)
		cor_errors(ARG_ERR);

	return (0);
}