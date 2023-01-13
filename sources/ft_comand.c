/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/13 20:03:50 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

void	ft_check_cmd_path(t_pix *pix)
{
	char	*cmd_path;
	int		i;

	i = -1;
	if (!access(pix->cmd_args[0], F_OK) && access(pix->cmd_args[0], X_OK))
		exit(ft_error(ERR_PERR, ft_clean_pix(pix, 126)));
	if (!access(pix->cmd_args[0], F_OK) && !access(pix->cmd_args[0], X_OK))
		return ;
	while (pix->paths[++i])
	{
		cmd_path = ft_strjoin(pix->paths[i], pix->cmd_args[0]);
		if (!cmd_path)
			exit(ft_error(ERR_MC, ft_clean_pix(pix, 1)));
		if (!access(cmd_path, F_OK))
		{
			ft_free(pix->cmd_args, 2);
			pix->cmd_args[0] = cmd_path;
			if (access(cmd_path, X_OK))
				exit(ft_error(ERR_PERR, ft_clean_pix(pix, 126)));
			return ;
		}
		ft_free(&cmd_path, 2);
	}
	exit(ft_error(ERR_CNF, ft_clean_pix(pix, 127)));
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
	dprintf(2, "cmd_tot == %s\nsize == %i\n", cmd_tot, ft_arg_num(cmd_tot));
	while (cmd_tot[++i])
	{
		del = ' ';
		i += ft_count_delimiter(&cmd_tot[i], del, 1);
		if (cmd_tot[i] && ft_strchr("\'\"\0", cmd_tot[i]))
			del = cmd_tot[i++];
		i += ft_count_delimiter(&cmd_tot[i], del, 1);
		if (cmd_tot[i] == '\\')
			i++;
		if (cmd_tot[i] && !ft_fill_arg(&cmd_tot[i], del, pix->cmd_args, ++j))
			return (*(int *)ft_free(pix->cmd_args, 1));
		i += ft_count_delimiter(&cmd_tot[i], del, 0);
	}
	int k = -1;
	while (pix->cmd_args[++k])
		dprintf(2, "cmd_args[%i] == %s\n", k, pix->cmd_args[k]);
	return (1);
}

int	ft_nchrstr(char *str, char c, int size)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i] && i < size)
		if (str[i] == c)
			n++;
	return (i);
}

int	ft_fill_arg(char *cmd_tot, char del, char **cmd_args, int pos)
{
	int		size;
	int		i;
	char	*arg;

	size = 0;
	i = -1;
	while (cmd_tot[++i] && cmd_tot[i] != del)
	{
		if (cmd_tot[i] != '\\' || (cmd_tot[i] == '\\' && ((i && cmd_tot[i - 1] == '\\' && ft_nchrstr(cmd_tot, '\\', i) % 2))))
			i++;
		else
			size++;
	}
	arg = (char *)ft_calloc(sizeof(char), size + 1);
	if (!arg)
		return (0);
	size = 0;
	i = -1;
	while (cmd_tot[++i] && cmd_tot[i] != del)
	{
		if (cmd_tot[i] != '\\' || (cmd_tot[i] == '\\' && ((i && cmd_tot[i - 1] == '\\' && ft_nchrstr(cmd_tot, '\\', i) % 2))))
			arg[size++] = cmd_tot[i];
	}
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
		if (args[i] && ft_strchr("\'\"\0", args[i]) && (!i || (args[i - 1] == '\\' && !(ft_nchrstr(args, '\\', i) % 2))))
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
		while (str[i] && str[i + 1] && (str[i] != del || (i && str[i - 1] == '\\' && ft_nchrstr(str, '\\', i) % 2)))
			i++;
	return (i);
}
