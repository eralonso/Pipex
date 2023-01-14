/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:58:22 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/13 12:53:49 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include	"../lib/ft_printf/inc/ft_printf.h"
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<stdio.h>
# include	<string.h>
# include	<fcntl.h>

# define PATH		(char *)"PATH="
# define ERR_ARG	(int)1
# define ERR_MC		(int)2
# define ERR_CNF	(int)3
# define ERR_PERR	(int)10

typedef struct s_pix {
	int		fd[2];
	pid_t	pid;
	int		infl;
	int		outfl;
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	char	**cmd_args;
	int		c_stat;
	int		err;
}			t_pix;

int		ft_error(int err, int ext);
int		ft_init_pipex(t_pix *pix, int ac, char **av, char **env);
char	**ft_found_paths(t_pix *pix);
int		ft_open_file(t_pix *pix, int file);
int		ft_close_pipes(int fd1, int fd2);
void	ft_check_cmd_path(t_pix *pix);
int		ft_clean_args(char *cmd_tot, t_pix *pix);
int		ft_count_delimiter(char *str, char del, int mode);
int		ft_arg_num(char *cmd_tot);
int		ft_fill_arg(char *cmd_tot, char del, char **cmd_args, int pos);
void	ft_chd_proc(t_pix *pix);
void	ft_prt_proc(t_pix *pix);
int		ft_clean_pix(t_pix *pix, int err);
int		ft_isscaped(char *str, int i);

#endif
