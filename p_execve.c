#include	<unistd.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<errno.h>
#include	<string.h>
#include	"includes/pipex.h"

int main(int ac, char **av, char **env)
{
	int		i;
	int		stat;
	int		pip[2];
	pid_t	cpid;
	char	**paths;
	char	**cmd_tot;
	char	*cmd;
	char	*pt_cmd;

	if (ac < 2)
		return (1);
	printf("ac == %i\n\n", ac);
	i = 0;
	if (pipe(pip) == -1)
	{
		dprintf(2, "ERROR");
		return (1);
	}
	cpid = fork();
	if (cpid == 0)
	{
		cmd_tot = ft_split(av[1], ' ');
		cmd = cmd_tot[0];
		i = -1;
		while (!ft_strnstr(env[++i], "PATH=", 5))
			;
		env[i] += 5;
		paths = ft_split(env[i], ':');
		i = -1;
		while (paths[++i])
			paths[i] = ft_strjoin(paths[i], "/\0");
		i = -1;
		while (paths[++i])
		{
			pt_cmd = ft_strjoin(paths[i], cmd);
			if (!access(pt_cmd, F_OK))
				break ;
		}
		if (access(pt_cmd, F_OK) == -1)
		{
			perror("access");
			exit (127);
		}
		printf("cmd == %s\n\n", pt_cmd);
		i = 0;
		while (cmd_tot[++i])
			printf("cmd_tot == %s\n", cmd_tot[i]);
		printf("\n");
		execve(pt_cmd, cmd_tot, env);
		perror("Error");
		printf("errno: %i\nstrerror: %s\n", errno, strerror(errno));
		exit(1);
	}
	else
	{
		printf("Retorno del waitpid == %i\n", waitpid(cpid, &stat, 0));
		printf("Status del hijo: %i\n", stat);
		printf("WIFEXITED == %i\n", WIFEXITED(stat));
		printf("WEXITSTATUS == %i\n", WEXITSTATUS(stat));
	}

	return (0);
}
// "/Users/eralonso/Documents/github/pipex_gh/"
