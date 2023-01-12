/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:32:57 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/12 19:55:05 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	ft_error(int err, int ext)
{
	ft_printf(2, "ERROR: ");
	if (err == NUM_ARG)
		ft_printf(2, "El número de parámetros és incorrecto.\n");
	else if (err == ERR_ARG)
		ft_printf(2, "Los parámetros introducidos són incorrecto.\n");
	else if (err == ERR_MC)
		ft_printf(2, "Ha habido un error a la hora de reservar memoria\n");
	else if (err == ERR_PRT)
		ft_printf(2, "Ha habido un error a la hora de imprimir por pantalla.\n");
	else
		perror("");
	return (ext);
}

int	ft_init_pipex(t_pix *pix, int ac, char **av, char **env)
{
	if (pipe(pix->fd) == -1)
		return (0);
	pix->ac = ac;
	pix->av = av;
	pix->env = env;
	pix->paths = ft_found_paths(pix);
	if (!pix->paths)
	{
		ft_close_pipes(pix->fd[0], pix->fd[1]);
		return (0);
	}
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
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/\0");
		if (!paths[i])
			return (ft_free(paths, 1));
		ft_free(&tmp, 2);
	}
	return (paths);
}

int	ft_close_pipes(int fd1, int fd2)
{
	if (close(fd1))
		return (1);
	if (close(fd2))
		return (1);
	return (1);
}

int	ft_clean_pix(t_pix *pix, int err)
{
	ft_free(pix->paths, 1);
	ft_free(pix->cmd_args, 1);
	return (err);
}
