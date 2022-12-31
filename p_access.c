#include	<stdio.h>
#include	<unistd.h>
#include	"inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	char	**paths;
	int		i;

	paths = ft_split(av[1], ':');
	if (ac < 2)
	{
		printf("Too few arguments\n");
		return (-1);
	}
	(void) env;
	i = -1;
	while (paths[++i])
	{
		printf("\n\033[1;95mFile: \033[1;93m%s\033[0m\n\n", paths[i]);
		printf("\t\033[1;94mF_OK: \033[1;9%im%i\033[0m\n",  2 + access(paths[i], F_OK), access(paths[i], F_OK));
		printf("\t\033[1;94mW_OK: \033[1;9%im%i\033[0m\n", 2 + access(paths[i], W_OK), access(paths[i], W_OK));
		printf("\t\033[1;94mR_OK: \033[1;9%im%i\033[0m\n", 2 + access(paths[i], R_OK), access(paths[i], R_OK));
		printf("\t\033[1;94mX_OK: \033[1;9%im%i\033[0m\n", 2 + access(paths[i], X_OK), access(paths[i], X_OK));
		printf("\n");
	}
	ft_free(paths, 1);
	return (0);
}
