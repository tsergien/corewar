#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char buf[100];
	unsigned int magic;
	int fd = open(av[1], O_RDONLY);
	read(fd, &magic, 4);

	unsigned int rev;
	unsigned char *rev_int = (unsigned char *)&rev;
	unsigned char *rev_mag = (unsigned char *)&magic;

	rev_int[3] = rev_mag[0];
	rev_int[2] = rev_mag[1];
	rev_int[1] = rev_mag[2];
	rev_int[0] = rev_mag[3];
	printf("%x\n", rev);
	printf("%d\n", rev);
	return (0);
}