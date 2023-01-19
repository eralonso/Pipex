#include	<unistd.h>
#include	<stdio.h>
#include	<fcntl.h>

int	main(int ac, char **av)
{
	int	fd;

	if (ac < 4)
	{
		printf("Too few arguments.\n");
		return (1);
	}
	//printf("open == %i\n", open(av[1], O_CREAT | O_WRONLY));
	//printf("open == %i\n", open(av[2], O_CREAT | O_WRONLY | O_TRUNC));
	//printf("open == %i\n", open(av[3], O_CREAT | O_WRONLY | O_TRUNC, 0666));
	//printf("open == %i\n", open(av[3], O_RDONLY));
	//printf("open == %i\n", open(av[3], O_RDONLY));
	//printf("open == %i\n", open(av[3], O_RDONLY));
	fd = open(av[3], O_RDONLY);
	printf("open == %i\n", fd);
	printf("close == %i\n", close(fd));
	printf("fd == %i\n", fd);
	printf("close == %i\n", close(fd));
	return (0);
}
