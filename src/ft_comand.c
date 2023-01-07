/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/07 16:05:43 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	ft_check_cmd(t_pix *pix, int n_cmd)
{
	pix->cmd = ft_get_cmd(pix->av[n_cmd]);
	if (!pix->cmd)
		return (0);
	pix->av[n_cmd] += ft_strlen(cmd);
	pix->cmd_args = ft_clean_cmd(pix->av[n_cmd]);
	if (!pix->cmd_args)
		return (0);
	return (1);
}

int	ft_check_cmd_path(t_pix *pix)
{
	int		i;

	i = -1;
	if (!access(pix->cmd, F_OK))
	{
		pix->cmd_path = pix->cmd;
		return (1);
	}
	while (pix->paths[++i])
	{
		pix->cmd_path = ft_strjoin(pix->paths[i], pix->cmd);
		if (!access(pix->cmd_path, F_OK))
			return (1);
		ft_free(&(pix->cmd_path), 2);
	}
	pix->err = ERR_PATH;
	return (0);
}

char	*ft_get_cmd(char *cmd_tot)
{
	char	*cmd;
	int		i;

	i = 0;
	while (cmd_tot[i] && cmd_tot[i] != ' ')
		i++;
	cmd = (char *)ft_calloc(sizeof(char), i + 1);
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, cmd_tot, i + 1)
	return (cmd);
}

char	**ft_clean_cmd(char *cmd_tot)
{
	int		i;
	int		j;
	int		size;
	char	**cmd_clean;

	i = -1;
	cmd_clean = (char **)ft_calloc(sizeof(char *), ft_clean_size(cmd_tot) + 1);
	while (cmd_tot[++i])
	{
		j = -1;
		size = ft_true_size(cmd_tot[i]);
		cmd_clean[i] = (char *)ft_calloc(sizeof(char),
				(ft_strlen(cmd_tot[i]) - size) + 1);
		while (cmd_tot[i][++j])
		{
			if (ft_strnstr(&cmd_tot[i][j], "\\\"", 2)
				|| ft_strnstr(&cmd_tot[i][j], "\\\'", 2))
				size += 2;
			else if (cmd_tot[i][j] == '\\')
				size++;
			else if (size == -1)
				cmd_clean[i][j] = cmd_tot[i][j];
		}
	}
	ft_free(cmd_tot, 1);
	return (cmd_clean);
}

int	ft_true_size(char *args)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (args[++i])
	{
		if (ft_strnstr(&args[i], "\\\"", 2)
			|| ft_strnstr(&args[i], "\\\'", 2))
			size += 2;
		else if (args[i] == '\\')
			size++;
	}
	return (size);
}

int	ft_clean_size(char *cmd_tot)
{
	int	size;
	int	i;
	int	j;
	int	flag;

	size = 0;
	i = -1;
	while (cmd_tot[++i])
	{
		flag = 0;
		if (ft_strnstr(&cmd_tot[i], "\\\"", 2))
			flag = 34;
		else if (ft_strnstr(&cmd_tot[i], "\\\'", 2))
			flag = 39;
		else if (cmd_tot[i] == '\\')
			flag = 92;
		else
		{
			while (!ft_strnstr("\\\\\'\\\"\0", &cmd_tot[i], 2))
				i++;
			if (cmd_tot[i])
				size++
		}
	}
	return (size);
}
