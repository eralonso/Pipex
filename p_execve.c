#include	<unistd.h>
#include	<stdio.h>
#include	"inc/pipex.h"

int main(int ac, char **av, char **env)
{
	char	*cmd;
	char	**new_av;
	int		i;
	int		pip[2];
	pid_t	cpid;

	if (ac < 2)
		return (1);
	//cmd = ft_strjoin("/Users/eralonso/Documents/github/pipex_gh/", av[1]);
	cmd = ft_strjoin("/bin/", av[1]);
	new_av = ft_calloc(sizeof(char *), ac);
	if (!new_av)
		return (1);
	new_av[0] = cmd;
	i = 0;
	while (++i < ac)
		new_av[i] = av[i + 1];
	if (pipe(pip) == -1)
	{
		dprintf(2, "ERROR");
		return (1);
	}
	cpid = fork();
	if (cpid == 0)
		printf("return value of execve function == %d", execve(cmd, new_av, env));
	else
	{
		printf("a\nb\nc");
		free(new_av);
	}
	waitpid(cpid, NULL, 0);
	return (0);
}
// "/Users/eralonso/Documents/github/pipex_gh/"
