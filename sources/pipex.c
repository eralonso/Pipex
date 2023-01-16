/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/16 19:35:47 by eralonso         ###   ########.fr       */
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
	pix.err = ft_open_file(&pix, 0);
	if (pix.err >= 0)
		exit(ft_clean_pix(&pix, ft_error(ERR_PERR, pix.err, NULL)));
	pix.pid = fork();
	if (pix.pid < 0)
		exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	else if (!pix.pid)
		ft_chd_proc(&pix, 2);
	ft_prt_proc(&pix, 3);
	//if (wait(&pix.c_stat) == -1)
	//	exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	//if (pix.c_stat)
	//	exit(ft_clean_pix(&pix, ft_error(0, WEXITSTATUS(pix.c_stat), NULL)));
	return (0);
}
	//if (wait(&pix->c_stat) == -1)
	//	exit(ft_error(ERR_PERR, ft_clean_pix(pix, 1)));
	//if (pix->c_stat)
	//	exit(ft_error(0, ft_clean_pix(pix, WEXITSTATUS(pix->c_stat))));

void	ft_chd_proc(t_pix *pix, int n_cmd)
{
	if (close(pix->fd[0]))
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	//if (!pix->av[n_cmd] || !*pix->av[n_cmd])
	//	exit(ft_clean_pix(pix, ft_error(ERR_PERM, 126, NULL)));
	if (!ft_clean_args(pix->av[n_cmd], pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix);
	if (dup2(pix->infl, 0) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (dup2(pix->fd[1], 1) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (close(pix->fd[1]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (close(pix->infl) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
}

	//int i = -1;
	//while (pix->cmd_args[++i])
	//	dprintf(2, "pix->cmd_args[%i] == %s\n", i, pix->cmd_args[i]);
	//int i = -1;
	//while (pix->env[++i])
	//	dprintf(2, "pix->env[%i] == %s\n", i, pix->env[i]);

void	ft_prt_proc(t_pix *pix, int n_cmd)
{
	if (close(pix->fd[1]))
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	pix->err = ft_open_file(pix, 1);
	if (pix->err >= 0)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, pix->err, NULL)));
	if (dup2(pix->fd[0], 0) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (close(pix->fd[0]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (close(pix->outfl) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	//if (!pix->av[n_cmd] || !*pix->av[n_cmd])
	//	exit(ft_clean_pix(pix, ft_error(ERR_PERM, 126, NULL)));
	if (!ft_clean_args(pix->av[n_cmd], pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix);
	execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, 1));
}

int	ft_open_file(t_pix *pix, int file)
{
	if (!file)
	{
		if (access(pix->av[1], F_OK | R_OK) == -1)
			return (ft_error(ERR_NFD, -1, NULL));
		pix->infl = open(pix->av[1], O_RDONLY);
		if (pix->infl == -1)
			return (1);
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
