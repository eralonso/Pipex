/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:58:22 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/24 15:58:16 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	"ft_printf.h"
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<stdio.h>
# include	<string.h>
# include	<fcntl.h>

# define PATH		(char *)"PATH="
# define DEF_PATH	(char *)"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define ERR_ARG	(int)1
# define ERR_MC		(int)2
# define ERR_CNF	(int)3
# define ERR_PERM	(int)4
# define ERR_NFD	(int)5
# define ERR_PERR	(int)10

typedef struct s_pix {
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		stat1;
	int		stat2;
	int		infl;
	int		outfl;
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	char	*cmd;
	char	**cmd_args;
	int		c_stat;
	int		err;
}			t_pix;

int		ft_error(int err, int ext, char *cmd);
int		ft_init_pipex(t_pix *pix, int ac, char **av, char **env);
char	**ft_found_paths(t_pix *pix);
int		ft_open_file(t_pix *pix, int file);
int		ft_close_pipes(int fd1, int fd2);
void	ft_check_cmd_path(t_pix *pix, int i);
int		ft_clean_args(char *cmd_tot, t_pix *pix);
int		ft_count_delimiter(char *str, char del, int mode);
int		ft_arg_num(char *cmd_tot);
int		ft_fill_arg(char *cmd_tot, char del, char **cmd_args, int pos);
void	ft_chd_proc(t_pix *pix, int n_cmd);
void	ft_prt_proc(t_pix *pix, int n_cmd);
int		ft_clean_pix(t_pix *pix, int err);
int		ft_isscaped(char *str, int i);
int		ft_close(int *fd);

#endif
