#include	<stdio.h>
#include	<unistd.h>
#include	"inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	char	**tab;
	int		i;

	if (ac < 2)
	{
		printf("Too few arguments.\n");
		return (1);
	}
	printf("av[1] == %s\n", av[1]);
	tab = ft_split(av[1], ' ');
	i = -1;
	while (tab[++i])
		printf("tab[%i] == %s\n", i, tab[i]);
	execve(ft_strjoin("/bin/\0", tab[0]), tab, env);
	printf("Ha fallado\n");
	return (0);
}
