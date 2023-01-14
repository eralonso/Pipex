/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/13 17:29:01 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pix	pix;

	if (ac != 5)
		return (ft_error(ERR_ARG, 1));
	if (!ft_init_pipex(&pix, ac, av, env))
		return (ft_error(ERR_MC, 1));
	pix.err = ft_open_file(&pix, 0);
	if (pix.err >= 0)
		exit(ft_error(ERR_PERR, ft_clean_pix(&pix, pix.err)));
	pix.pid = fork();
	if (pix.pid < 0)
		exit(ft_error(ERR_PERR, ft_clean_pix(&pix, 1)));
	else if (!pix.pid)
		ft_chd_proc(&pix);
	ft_prt_proc(&pix);
	if (waitpid(pix.pid, &pix.c_stat, 0) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(&pix, 1)));
	if (pix.c_stat)
		exit(ft_error(0, ft_clean_pix(&pix, WEXITSTATUS(pix.c_stat))));
	return (0);
}

void	ft_chd_proc(t_pix *pix)
{
	if (close(pix->fd[0]))
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (!ft_clean_args(pix->av[2], pix))
		exit(ft_error(ERR_MC, ft_clean_pix(pix, 1)));
	ft_check_cmd_path(pix);
	if (dup2(pix->infl, 0) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (dup2(pix->fd[1], 1) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (close(pix->fd[1]) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (close(pix->infl) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	execve(pix->cmd_args[0], pix->cmd_args, pix->env);
	exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
}

	//int i = -1;
	//while (pix->cmd_args[++i])
	//	dprintf(2, "pix->cmd_args[%i] == %s\n", i, pix->cmd_args[i]);
	//int i = -1;
	//while (pix->env[++i])
	//	dprintf(2, "pix->env[%i] == %s\n", i, pix->env[i]);

void	ft_prt_proc(t_pix *pix)
{
	if (close(pix->fd[1]))
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (!ft_clean_args(pix->av[3], pix))
		exit(ft_error(ERR_MC, ft_clean_pix(pix, 1)));
	ft_check_cmd_path(pix);
	if (dup2(pix->fd[0], 0) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	pix->err = ft_open_file(pix, 1);
	if (pix->err >= 0)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, pix->err)));
	if (close(pix->fd[0]) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	if (close(pix->outfl) == -1)
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	execve(pix->cmd_args[0], pix->cmd_args, pix->env);
	exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
}

int	ft_open_file(t_pix *pix, int file)
{
	if (!file)
	{
		if (access(pix->av[1], F_OK | R_OK) == -1)
			return (-1);
		pix->infl = open(pix->av[1], O_RDONLY);
		if (pix->infl == -1)
			return (-1);
		if (dup2(pix->infl, 0) == -1)
			return (-1);
	}
	else if (file == 1)
	{
		if (!access(pix->av[pix->ac - 1], F_OK)
			&& access(pix->av[pix->ac - 1], W_OK))
			return (0);
		pix->outfl = open(pix->av[pix->ac - 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0666);
		if (pix->outfl == -1)
			return (1);
		if (dup2(pix->outfl, 1) == -1)
			return (1);
	}
	return (-1);
}
