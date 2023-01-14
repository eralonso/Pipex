/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:32:57 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/13 12:54:04 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	ft_error(int err, int ext)
{
	if (err > 0)
		ft_printf(2, "ERROR: ");
	if (err == ERR_ARG)
		ft_printf(2, "Invalid number of arguments:\n");
	else if (err == ERR_MC)
		ft_printf(2, "error trying to allocate memory:\n");
	else if (err == ERR_CNF)
		ft_printf(2, "command not found:\n");
	else if (err == ERR_PERM)
		ft_printf(2, "permission denied:\n");
	else if (err == ERR_PERR)
		perror("");
	return (ext);
}

int	ft_init_pipex(t_pix *pix, int ac, char **av, char **env)
{
	pix->ac = ac;
	pix->av = av;
	pix->env = env;
	pix->err = 0;
	pix->paths = ft_found_paths(pix);
	if (!pix->paths)
		return (0);
	if (pipe(pix->fd) == -1)
		return (*(int *)ft_free(pix->paths, 1));
	return (1);
}

char	**ft_found_paths(t_pix *pix)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	while (!ft_strnstr(pix->env[i], PATH, ft_strlen(PATH)))
		i++;
	paths = ft_split((pix->env[i]) + ft_strlen(PATH), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
		i++;
	while (--i >= 0)
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/\0");
		ft_free(&tmp, 2);
		if (!paths[i])
			return (ft_free(paths, 1));
	}
	return (paths);
}

int	ft_clean_pix(t_pix *pix, int err)
{
	ft_free(pix->paths, 1);
	ft_free(pix->cmd_args, 1);
	return (err);
}

int	ft_isscaped(char *str, int i)
{
	int	n;

	if (!i)
		return (0);
	n = 0;
	while (--i >= 0 && str[i] == '\\')
		n++;
	return (n % 2);
}
