#include "asm.h"

static int		asm_count_lines(const int fd)
{
	int			lines;
	ssize_t		ret;
	char		buff[BUFF_SIZE + 1];

	lines = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		lines += ft_strcount(buff, '\n');
	}
	lseek(fd, 0,SEEK_SET);
	return (lines);
}

void			asm_input(t_asm *as, char *file)
{
	int			i;
	int			fd;
	char		*buff;

	i = 0;
	buff = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		asm_errors(FILE_ERR, file, NONE);
	if ((as->len = asm_count_lines(fd)) < 0)
		asm_errors(FILE_ERR, file, NONE);
	if (!(as->input = (char**)malloc(sizeof(*as->input) * as->len)))
		asm_errors(MLC_ERR, NULL, NONE);
	while (get_next_line(fd, &buff))
	{
		as->input[i++] = buff;
		buff = NULL;
	}
	close(fd);
}