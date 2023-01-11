/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:58:22 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/11 13:01:35 by eralonso         ###   ########.fr       */
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
# define ERR_DUP	(int)12

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
	char	**cmd_args;
	int		err;
	int		c_stat;
}			t_pix;

int		ft_error(int err);
int		ft_init_pipex(t_pix *pix, int ac, char **av, char **env);
char	**ft_found_paths(t_pix *pix);
int		ft_open_file(t_pix *pix, int file);
int		ft_close_file(int fd);
int		ft_check_cmd_path(t_pix *pix);
int		ft_check_cmd(t_pix *pix, int n_cmd);
char	*ft_clean_cmd(char *cmd_tot);
char	*ft_get_cmd(char *cmd_tot);
int		ft_clean_size(char *cmd_tot);
void	ft_chd_proc(t_pix *pix);
void	ft_prt_proc(t_pix *pix);

#endif
