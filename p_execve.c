#include	<unistd.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<errno.h>
#include	<string.h>
#include	"inc/pipex.h"

int main(int ac, char **av, char **env)
{
	char	*cmd;
	char	**new_av;
	int		i;
	int		stat;
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
	{
		execve(cmd, new_av, env);
		perror("Error");
		printf("errno: %i\nstrerror: %s\n", errno, strerror(errno));
		exit(1);
	}
	else
	{
		printf("a\nb\nc\n");
		free(new_av);
		free(cmd);
	}
	waitpid(cpid, &stat, 0);
	printf("Status del hijo: %i\n", stat);
	return (0);
}
// "/Users/eralonso/Documents/github/pipex_gh/"
