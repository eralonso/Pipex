/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/21 10:38:07 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pix	pix;

	if (ac < 5 || (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac < 6))
		return (ft_error(ERR_ARG, 1, NULL));
	if (!ft_init_pipex(&pix, ac, av, env))
		return (ft_error(ERR_PERR, 1, NULL));
	while ((--ac) - 3 - (pix.hdoc != 0))
	{
		if (pipe(pix.fd) == -1)
			return (ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
		pix.pid = fork();
		if (pix.pid < 0)
			exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
		else if (!pix.pid)
			ft_chd_procs(&pix, pix.av[pix.ac - (ac - (pix.hdoc != 0) - 1)], ac);
		if (dup2(pix.fd[0], 0) == -1)
			exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
		if (close(pix.fd[0]) == -1)
			exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
		if (close(pix.fd[1]) == -1)
			exit(ft_clean_pix(&pix, ft_error(ERR_PERR, 1, NULL)));
	}
	ft_prt_proc(&pix, pix.av[pix.ac - (ac - (pix.hdoc != 0) - 1)]);
	return (0);
}

void	ft_chd_procs(t_pix *pix, char *comand, int ac)
{
	if (!comand || !*comand)
		exit(ft_clean_pix(pix, ft_error(ERR_CNF, 127, comand)));
	if (!ft_clean_args(comand, pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix, -1);
	if (close(pix->fd[0]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (dup2(pix->fd[1], 1) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (close(pix->fd[1]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (pix->err != -2 || (pix->ac - (ac - (pix->hdoc != 0) - 1) > 2)
		|| pix->hdoc)
		execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, ft_error(-1, 1, NULL)));
}

void	ft_prt_proc(t_pix *pix, char *comand)
{
	pix->err = ft_open_file(pix, 1);
	if (pix->err >= 0)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, pix->err, NULL)));
	if (close(pix->outfl) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (!comand || !*comand)
		exit(ft_clean_pix(pix, ft_error(ERR_CNF, 127, comand)));
	if (!ft_clean_args(comand, pix))
		exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
	ft_check_cmd_path(pix, -1);
	execve(pix->cmd, pix->cmd_args, pix->env);
	exit(ft_clean_pix(pix, 1));
}

int	ft_open_file(t_pix *pix, int file)
{
	if (!file && !pix->hdoc)
	{
		if (access(pix->av[1], F_OK | R_OK) == -1)
			return (ft_error(ERR_NFD, -2, pix->av[1]));
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
			return (0);
		if (!pix->hdoc)
			pix->outfl = open(pix->av[pix->ac - 1], O_CREAT | O_WRONLY
					| O_TRUNC, 0666);
		else
			pix->outfl = open(pix->av[pix->ac - 1], O_CREAT | O_WRONLY
					| O_APPEND, 0666);
		if (pix->outfl == -1 || dup2(pix->outfl, 1) == -1)
			return (1);
	}
	return (-1);
}

int	ft_ishere_doc(int ac, char **av, t_pix *pix)
{
	int		fd_here_doc[2];
	char	*str;

	if (ac <= 5 || ft_strncmp(av[1], "here_doc\0", ft_strlen(av[1])))
		return (0);
	if (pipe(fd_here_doc) == -1)
		exit (ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	if (ft_printf(1, "> ") == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	str = get_next_line(0);
	while (str && ft_strncmp(str, pix->limiter, ft_strlen(str)))
	{
		if (ft_printf(fd_here_doc[1], str) == -1)
			exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, ft_free(&str, 2))));
		ft_free(&str, 2);
		if (ft_printf(1, "> ") == -1)
			exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
		str = get_next_line(0);
	}
	ft_free(&str, 2);
	if (close(fd_here_doc[1]) == -1)
		exit(ft_clean_pix(pix, ft_error(ERR_PERR, 1, NULL)));
	return (fd_here_doc[0]);
}
