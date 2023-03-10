/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/21 09:43:21 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex_bonus.h"

void	ft_check_cmd_path(t_pix *pix, int i)
{
	char	*cmd_path;

	while (pix->paths[++i] && !ft_strchr(pix->cmd, '/'))
	{
		cmd_path = ft_strjoin(pix->paths[i], pix->cmd);
		if (!cmd_path)
			exit(ft_clean_pix(pix, ft_error(ERR_MC, 1, NULL)));
		if (!access(cmd_path, F_OK))
		{
			ft_free(&pix->cmd, 2);
			pix->cmd = cmd_path;
			if (access(cmd_path, X_OK))
				exit(ft_clean_pix(pix, ft_error(ERR_PERR, 126, NULL)));
			return ;
		}
		ft_free(&cmd_path, 2);
	}
	if (ft_strchr(pix->cmd, '/') && !access(pix->cmd, F_OK)
		&& access(pix->cmd, X_OK))
		exit(ft_clean_pix(pix, ft_error(ERR_PERM, 126, pix->cmd_args[0])));
	if (ft_strchr(pix->cmd, '/') && !access(pix->cmd, F_OK)
		&& !access(pix->cmd, X_OK))
		return ;
	exit(ft_clean_pix(pix, ft_error(ERR_CNF, 127, pix->cmd_args[0])));
}

int	ft_clean_args(char *cmd_tot, t_pix *pix)
{
	int		i;
	int		j;
	char	del;

	i = -1;
	j = -1;
	pix->cmd_args = (char **)ft_calloc(sizeof(char *), ft_arg_num(cmd_tot) + 1);
	if (!pix->cmd_args)
		return (0);
	while (cmd_tot[++i])
	{
		del = ' ';
		i += ft_count_delimiter(&cmd_tot[i], del, 1);
		if (cmd_tot[i] && ft_strchr("\'\"\0", cmd_tot[i]))
			del = cmd_tot[i++];
		i += ft_count_delimiter(&cmd_tot[i], del, 1);
		if (cmd_tot[i] && !ft_fill_arg(&cmd_tot[i], del, pix->cmd_args, ++j))
			return (*(int *)ft_free(pix->cmd_args, 1));
		i += ft_count_delimiter(&cmd_tot[i], del, 0);
	}
	pix->cmd = ft_strdup(pix->cmd_args[0]);
	if (!pix->cmd)
		return (*(int *)(ft_free(pix->cmd_args, 1)));
	return (1);
}

int	ft_fill_arg(char *cmd_tot, char del, char **cmd_args, int pos)
{
	int		size;
	int		i;
	char	*arg;

	size = 0;
	i = -1;
	while (cmd_tot[++i] && (cmd_tot[i] != del || ft_isscaped(cmd_tot, i)))
		if (cmd_tot[i] != '\\' || ft_isscaped(cmd_tot, i))
			size++;
	arg = (char *)ft_calloc(sizeof(char), size + 1);
	if (!arg)
		return (0);
	size = 0;
	i = -1;
	while (cmd_tot[++i] && (cmd_tot[i] != del || ft_isscaped(cmd_tot, i)))
		if (cmd_tot[i] != '\\' || ft_isscaped(cmd_tot, i))
			arg[size++] = cmd_tot[i];
	cmd_args[pos] = arg;
	return (1);
}

int	ft_arg_num(char *args)
{
	int		size;
	int		i;
	char	del;

	i = -1;
	size = 0;
	while (args[++i])
	{
		del = ' ';
		i += ft_count_delimiter(&args[i], del, 1);
		if (args[i] && ft_strchr("\'\"\0", args[i]))
			del = args[i++];
		i += ft_count_delimiter(&args[i], del, 1);
		if (args[i])
			size++;
		i += ft_count_delimiter(&args[i], del, 0);
	}
	return (size);
}

int	ft_count_delimiter(char *str, char del, int mode)
{
	int	i;

	i = 0;
	if (mode)
		while (str[i] && str[i + 1] && str[i] == del)
			i++;
	else
		while (str[i] && str[i + 1] && (str[i] != del || ft_isscaped(str, i)))
			i++;
	return (i);
}
