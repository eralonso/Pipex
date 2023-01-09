#include	"stdio.h"
#include	"inc/pipex.h"

int	ft_clean_size(char *cmd_tot)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (cmd_tot[i])
	{
		while (cmd_tot[i] && cmd_tot[i] != '\\')
		{
			if (!ft_strchr("\"\'\0", cmd_tot[i]))
				size++;
			i++;
		}
		if (cmd_tot[i] && cmd_tot[i + 1] && cmd_tot[i] == '\\'
			&& ft_strchr("\"\'\\\0", cmd_tot[i + 1]))
				size++;
		i += (cmd_tot[i] != '\0');
	}
	return (size);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 2)
		return (1);
	printf("av[1] == %s\n", av[1]);
	while (av[1][i] && av[1][i] != ' ')
		i++;
	while (av[1][i] == ' ')
		i++;
	printf("av[1][%i] == %s\n", i, &av[1][i]);
	printf("\n");
	printf("len == %i\n", ft_clean_size(&av[1][i]));
	return (0);
}
