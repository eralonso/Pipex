#include	<stdio.h>
#include	<string.h>
#include	<fcntl.h>
#include	<errno.h>
#include	<unistd.h>
#include	<stdlib.h>
#define malloc(size) NULL

int	main(int ac, char **av)
{
	char	*str;

	if (ac < 3)
	{
		open("prueba.txt", O_RDWR);
		perror("");
		printf("errno: %i\nstrerror: %s\n", errno, strerror(errno));
		return (1);
	}
	str = malloc(sizeof(char) * 100);
	if (!str)
	{
		perror("Ha fallado la reserva de memoria");
		printf("errno: %i\nstrerror: %s\n", errno, strerror(errno));
		return (1);
	}
	free(str);
	printf("%s\n", av[1]);
	return (0);
}
