/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/24 16:19:31 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pix	pix;

	if (ac != 5)
		return (ft_error(ERR_ARG, 1, NULL));
	if (!ft_init_pipex(&pix, ac, av, env))
		return (ft_error(ERR_MC, 1, NULL));
	pix.pid1 = fork();
	if (pix.pid1 < 0)
		exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	else if (!pix.pid1)
		ft_chd_proc(&pix, 2);
	pix.pid2 = fork();
	if (pix.pid2 < 0)
		exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	else if (!pix.pid2)
		ft_prt_proc(&pix, 3);
	if (ft_clean_pix(&pix, -1) == 1)
		exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	waitpid(pix.pid1, &pix.stat1, 0);
	waitpid(pix.pid2, &pix.stat2, 0);
	return (WEXITSTATUS(pix.stat2));
}

void	ft_chd_proc(t_pix *pix, int n_cmd)
{
	if (ft_close(&pix->fd[0]))
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (!pix->av[n_cmd] || !*pix->av[n_cmd])
		exit(ft_clean_pix(pix, ft_error(ERR_CNF, 127, pix->av[n_cmd])));
	if (!ft_clean_args(pix->av[n_cmd], pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix, -1);
	if (dup2(pix->fd[1], 1) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (ft_close(&pix->fd[1]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (pix->err != -2)
		execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, ft_error(-1, 1, NULL)));
}

void	ft_prt_proc(t_pix *pix, int n_cmd)
{
	if (ft_close(&pix->fd[1]))
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	pix->err = ft_open_file(pix, 1);
	if (pix->err >= 0)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, pix->err, NULL)));
	if (dup2(pix->fd[0], 0) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (ft_close(&pix->fd[0]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (ft_close(&pix->outfl) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (!pix->av[n_cmd] || !*pix->av[n_cmd])
		exit(ft_clean_pix(pix, ft_error(ERR_CNF, 127, pix->av[n_cmd])));
	if (!ft_clean_args(pix->av[n_cmd], pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix, -1);
	execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, 1));
}

int	ft_open_file(t_pix *pix, int file)
{
	if (!file)
	{
		if (access(pix->av[1], F_OK) == -1)
			return (ft_error(ERR_NFD, -2, pix->av[1]));
		if (access(pix->av[1], R_OK) == -1)
			return (ft_error(ERR_PERM, -2, pix->av[1]));
		pix->infl = open(pix->av[1], O_RDONLY);
		if (pix->infl == -1)
			return (1);
		if (dup2(pix->infl, 0) == -1)
			return (1);
	}
	else if (file == 1)
	{
		if (!access(pix->av[pix->ac - 1], F_OK)
			&& access(pix->av[pix->ac - 1], W_OK))
			exit(ft_clean_pix(pix,
					ft_error(ERR_PERM, 0, pix->av[pix->ac - 1])));
		pix->outfl = open(pix->av[pix->ac - 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0666);
		if (pix->outfl == -1 || dup2(pix->outfl, 1) == -1)
			return (1);
	}
	return (-1);
}

int	ft_close(int *fd)
{
	if (*fd != 0 && close(*fd) == -1)
	{
		*fd = 0;
		return (-1);
	}
	*fd = 0;
	return (0);
}
