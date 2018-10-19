#include <fcntl.h>
#include "../includes/vm_corewar.h"

unsigned int	rev(int fd)
{
	unsigned int rev;
	unsigned int magic;
	unsigned char *rev_mag = (unsigned char *)&magic;
	unsigned char *rev_int = (unsigned char *)&rev;
	
	read(fd, &magic, 4);
	rev_int[3] = rev_mag[0];
	rev_int[2] = rev_mag[1];
	rev_int[1] = rev_mag[2];
	rev_int[0] = rev_mag[3];
	return (rev);
}

void		ft_error(char *str)
{
	write(2, str, ft_strlen(str) + 1);
	exit(0);
}

void		exec_get(int fd, header_t *tanya)
{
	int				i;
	unsigned char	temp;
	t_game			*g;
	
	i = -1;
	g = (t_game *)malloc(sizeof(t_game));
	while (++i <= tanya->prog_size)
	{
		read(fd, &temp, 1);
		g->map[i].byte = temp;
	}
}

int	main(int ac, char **av)
{
	ac--;
	int				fd;
	int				i;
	header_t		*tanya;
	unsigned char	*str;
	unsigned int	temp;

	tanya = (header_t *)malloc(sizeof(header_t));
	fd = open(av[1], O_RDONLY);
	tanya->magic = rev(fd);
	if (tanya->magic != COREWAR_EXEC_MAGIC)
		ft_error("No magic header!\n");
	ft_strclr(tanya->prog_name);
	i = 0;
	while (i + 4 <= PROG_NAME_LENGTH)
	{
		read(fd, &temp, 4);
		str = (unsigned char *)&temp;
		ft_strncpy(tanya->prog_name + i, (const char *)str, 4);
		i += 4;
	}
	ft_printf("%s\n", tanya->prog_name);
	
	read(fd, &temp, 4);
	tanya->prog_size = rev(fd);
	ft_printf("%u\n", tanya->prog_size);
	if (tanya->prog_size > CHAMP_MAX_SIZE)
		ft_error("Too big exec\n");
	i = 0;
	ft_strclr(tanya->comment);
	while (i + 4 <= COMMENT_LENGTH)
	{
		read(fd, &temp, 4);
		str = (unsigned char *)&temp;
		ft_strncpy(tanya->comment + i, (const char *)str, 4);
		i += 4;
	}
	ft_printf("%s\n", tanya->comment);
	read(fd, &temp, 4);
	exec_get(fd, tanya);
	return (0);
}