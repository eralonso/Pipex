/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:32:57 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/03 19:28:28 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	ft_error(int err)
{
	if (err == NUM_ARG)
		ft_printf(2, "El número de parámetros és incorrecto.\n");
	else if (err == ERR_ARG)
		ft_printf(2, "Los parámetros introducidos són incorrecto.\n");
	else if (err == ERR_MC)
		ft_printf(2, "Ha habido un error a la hora de reservar memoria\n");
	else if (err == ERR_PRT)
		ft_printf(2, "Ha habido un error a la hora de imprimir por pantalla.\n");
	else if (err == ERR_OPEN || err == ERR_CLOSE || err == ERR_ACS
		|| err == ERR_PIPE || err == ERR_FORK || err == ERR_PATH)
		perror("");
	return (1);
}

int	ft_init_pipex(t_pix *pix, int ac, char **av, char **env)
{
	if (pipe(pix->fd) == -1)
	{
		pix->err = ERR_PIPE;
		return (0);
	}
	pix->ac = ac;
	pix->av = av;
	pix->env = env;
	pix->paths = ft_found_paths(pix);
	if (!pix->paths)
	{
		ft_close_file(pix->fd[0]);
		ft_close_file(pix->fd[1]);
		pix->err = ERR_MC;
		ft_free(pix->paths, 1);
		return (0);
	}
	pix->err = 0;
	return (1);
}

char	**ft_found_paths(t_pix *pix)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(pix->env[i], PATH, ft_strlen(PATH)))
		i++;
	paths = ft_split((pix->env[i]) + ft_strlen(PATH), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
		paths[i] = ft_malloc_strjoin(paths[i], "/\0");
	return (paths);
}

int	ft_close_file(int fd)
{
	if (close(fd) == -1)
		return (ERR_CLOSE);
	return (0);
}
