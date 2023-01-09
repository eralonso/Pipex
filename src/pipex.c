/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/09 19:34:59 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"pipex.h"
#include	<stdio.h>

int	main(int ac, char **av, char **env)
{
	t_pix	pix;

	if (ac != 5)
		return (ft_error(NUM_ARG));
	if (!ft_init_pipex(&pix, ac, av, env))
		return (ft_error(pix.err));
	if (!ft_open_file(&pix, 0))
		exit(ft_error(ERR_OPEN));
	pix.pid = fork();
	dprintf(2, "Aquí\n");
	if (pix.pid < 0)
		ft_error(ERR_FORK);
	else if (!pix.pid)
		ft_chd_proc(&pix);
	if (waitpid(pix.pid, &pix.c_stat, 0) == -1 || pix.c_stat)
		ft_error(ERR_WAIT);
	if (dup2(pix.fd[0], 0) == -1)
		exit(ft_error(ERR_DUP));
	if (close(pix.fd[0]) == ERR_CLOSE)
		exit(ft_error(ERR_CLOSE));
	if (close(pix.fd[1]) == ERR_CLOSE)
		exit(ft_error(ERR_CLOSE));
	ft_prt_proc(&pix);
	return (0);
}

void	ft_chd_proc(t_pix *pix)
{
	pix->paths = ft_found_paths(pix);
	if (!pix->paths)
		exit(1);
	if (!ft_check_cmd(pix, 2))
		exit(1);
	if (!ft_check_cmd_path(pix))
		exit(1);
	pix->cmd_args[0] = pix->cmd_path;
	if (dup2(pix->infl, 0) == -1)
		exit(ft_error(ERR_DUP));
	if (dup2(pix->fd[1], 1) == -1)
		exit(ft_error(ERR_DUP));
	dprintf(2, "pix->cmd == %s\n", pix->cmd);
	dprintf(2, "pix->cmd_args[0] == %s\n", pix->cmd_args[0]);
	dprintf(2, "pix->cmd_args[1] == %s\n", pix->cmd_args[1]);
	execve(pix->cmd_path, pix->cmd_args, pix->env);
	exit(1);
}

void	ft_prt_proc(t_pix *pix)
{
	pix->paths = ft_found_paths(pix);
	if (!pix->paths)
		exit(1);
	if (!ft_check_cmd(pix, 3))
		exit(1);
	if (!ft_check_cmd_path(pix))
		exit(1);
	pix->cmd_args[0] = pix->cmd_path;
	if (!ft_open_file(pix, 1))
		exit(ft_error(ERR_OPEN));
	//if (dup2(pix->infl, 0) == -1)
	//	exit(ft_error(ERR_DUP));
	dprintf(2, "pix->cmd == %s\n", pix->cmd);
	dprintf(2, "pix->cmd_args[0] == %s\n", pix->cmd_args[0]);
	dprintf(2, "pix->cmd_args[1] == %s\n", pix->cmd_args[1]);
	execve(pix->cmd_path, pix->cmd_args, pix->env);
	exit(1);
}

int	ft_open_file(t_pix *pix, int file)
{
	if (!file)
	{
		if (access(pix->av[1], F_OK | R_OK) == -1)
			return (0);
		pix->infl = open(pix->av[1], O_RDONLY);
		if (pix->infl == -1)
			return (0);
		if (dup2(pix->infl, 0) == -1)
			return (0);
	}
	else if (file == 1)
	{
		if (!access(pix->av[pix->ac - 1], F_OK)
			&& access(pix->av[pix->ac - 1], W_OK))
			return (0);
		pix->outfl = open(pix->av[pix->ac - 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0666);
		if (pix->outfl == -1)
			return (0);
		if (dup2(pix->outfl, 1) == -1)
			return (0);
	}
	return (1);
}
