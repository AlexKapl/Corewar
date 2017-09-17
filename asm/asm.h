#ifndef COREWAR_ASM_H
# define COREWAR_ASM_H

# include "../op.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>

# define INP_ERR 1
# define MLC_ERR 2
# define FILE_ERR 3
# define LINE_ERR 4

typedef struct	s_asm
{
	char		**input;
	char		*name;
	char		*comm;
	int			len;
}				t_asm;

int				asm_not_empty_line(char *line);
void			asm_input(t_asm *as, char *file);
void			asm_errors(int err, char *str, int line);
void			asm_find_name(t_asm *as, char *line, int num);
void			asm_find_comm(t_asm *as, char *line, int num);
#endif
