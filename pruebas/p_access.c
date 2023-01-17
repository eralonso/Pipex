#include	<stdio.h>
#include	<unistd.h>
#include	"inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	char	**paths;
	int		i;

	if (ac < 2)
	{
		printf("Too few arguments\n");
		return (-1);
	}
	if (!ft_strncmp("paths", av[1], 5))
	{
		i = 0;
		while (!ft_strnstr(env[i], PATH, ft_strlen(PATH)))
			i++;
		paths = ft_split(&env[i][5], ':');
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
	}
	else
	{
		printf("\n\033[1;95mFile: \033[1;93m%s\033[0m\n\n", av[1]);
		printf("\t\033[1;94mF_OK && R_OK && W_OK && X_OK: \033[1;9%im%i\033[0m\n",  2 + access(av[1], F_OK | W_OK | R_OK | X_OK), access(av[1], F_OK | R_OK | W_OK | X_OK));
		printf("\n");
	}
	return (0);
}
