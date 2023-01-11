/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/11 18:19:07 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	ft_check_cmd(t_pix *pix, int n_cmd)
{
	pix->cmd = ft_get_cmd(pix->av[n_cmd]);
	if (!pix->cmd)
		return (0);
	pix->cmd_args = ft_clean_cmd(pix->av[n_cmd]);
	if (!pix->cmd_args)
		return (*(int *)ft_free(pix->cmd_args, 2));
	return (1);
}

int	ft_check_cmd_path(t_pix *pix)
{
	char	*cmd;
	char	*cmd_path;
	int		i;

	i = -1;
	cmd = pix->cmd_args[0];
	if (!access(cmd, F_OK))
		return (1);
	while (pix->paths[++i])
	{
		cmd_path = ft_strjoin(pix->paths[i], cmd);
		if (!access(cmd_path, F_OK))
		{
			ft_free(&cmd, 2);
			pix->cmd_args[0] = cmd_path;
			return (1);
		}
		ft_free(&cmd_path, 2);
	}
	pix->err = ERR_PATH;
	return (0);
}

char	*ft_get_cmd(char *cmd_tot)
{
	char	*cmd;
	int		i;

	i = 0;
	while (cmd_tot[i] == ' ')
		i++;
	while (cmd_tot[i] && cmd_tot[i] != ' ')
		i++;
	cmd = (char *)ft_calloc(sizeof(char), i + 1);
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, cmd_tot, i + 1);
	return (cmd);
}

char	**ft_clean_cmd(char *cmd_tot)
{
	int		i;
	int		j;
	char	**cmd_clean;

	i = 0;
	j = -1;
	cmd_clean = (char **)ft_calloc(sizeof(char *), ft_arg_num(cmd_tot) + 1);
	if (!cmd_clean)
		return (0);
	while (cmd_tot[i])
	{
		del = ' ';
		while (cmd_tot[i] && cmd_tot[i] == ' ')
			i++;
		if (cmd_tot[i] && ft_strchr("\'\"\0", cmd_tot[i]) && (!i
				|| (i && cmd_tot[i - 1] != '\\')))
			del = cmd_tot[i++];
		while (cmd_tot[i] && cmd_tot[i] == del)
			i++;
		if (cmd_tot[i] && !(ft_strchr("\'\" \0", cmd_tot[i]) && (!i
					|| (i && cmd_tot[i - 1] != '\\'))))
		{
			cmd_clean[++j] = ft_fill_arg(&cmd_tot[i], del);
			if (!cmd_clean[j])
				return (ft_free(cmd_clean, 1));
		}
		while (cmd_tot[i] && cmd_tot[i] != del)
			i++;
		i += (cmd_tot[i] != '\0') * (ft_strchr("\'\" \0", cmd_tot[i]) && (!i
					|| (i && cmd_tot[i - 1] != '\\')));
	}
	return (cmd_clean);
}

int	ft_arg_len(char *cmd_tot, char del)
{
	int		size;
	int		i;
	char	*arg;

	size = 0;
	i = -1;
	if (!cmd_tot)
		return (NULL);
	while (cmd_tot[size] && cmd_tot[size] != del)
		size++;
	arg = (char *)ft_calloc(sizeof(char), size + 1);
	if (!arg)
		return (NULL);
	while (cmd_tot[++i] && cmd_tot[i] != del)
		arg[i] = cmd_tot[i];
	return (arg);
}

int	ft_arg_num(char *args)
{
	int		size;
	int		i;
	char	del;

	i = 0;
	size = 0;
	{
		del = ' ';
		while (args[i] && args[i] == ' ')
			i++;
		if (args[i] && ft_strchr("\'\"\0", args[i]) && (!i
				|| (i && args[i - 1] != '\\')))
			del = args[i++];
		while (args[i] && args[i] == del)
			i++;
		if (args[i] && !(ft_strchr("\'\" \0", args[i]) && (!i
					|| (i && args[i - 1] != '\\'))))
			size++;
		while (args[i] && args[i] != del)
			i++;
		i += (args[i] != '\0') * (ft_strchr("\'\" \0", args[i]) && (!i
					|| (i && args[i - 1] != '\\')));
	}
	return (size);
}
