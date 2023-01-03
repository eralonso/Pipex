/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:58:22 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/03 19:29:09 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	"../lib/ft_printf/inc/ft_printf.h"
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<stdio.h>
# include	<string.h>
# include	<fcntl.h>

# define PATH		(char *)"PATH="
# define NUM_ARG	(int)1
# define ERR_ARG	(int)2
# define ERR_PIPE	(int)3
# define ERR_FORK	(int)4
# define ERR_MC		(int)5
# define ERR_PRT	(int)6
# define ERR_OPEN	(int)7
# define ERR_CLOSE	(int)8
# define ERR_ACS	(int)9
# define ERR_WAIT	(int)10
# define ERR_PATH	(int)11

typedef struct s_pix {
	int		fd[2];
	pid_t	pid;
	int		infl;
	int		outfl;
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	char	*cmd;
	char	*cmd_path;
	char	*cmd_args;
	int		err;
	int		c_stat;
}			t_pix;

int		ft_error(int err);
int		ft_init_pipex(t_pix *pix, int ac, char **av, char **env);
char	**ft_found_paths(t_pix *pix);
int		ft_close_file(int fd);
int		ft_check_cmd_paths(t_pix *pix);
char	*ft_check_cmd(t_pix *pix);

#endif
