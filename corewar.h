#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include "libft/libft.h"
# include "op.h"

# define ARG_ERR 0

typedef struct	s_cor
{
	char		**r;
	char		pc;
	t_bool		carry;
}				t_cor;
#endif
