/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/09 14:00:50 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"pipex.h"

int	ft_check_cmd(t_pix *pix, int n_cmd)
{
	pix->cmd = ft_get_cmd(pix->av[n_cmd]);
	if (!pix->cmd)
		return (0);
	pix->cmd_args = (char **)ft_calloc(sizeof(char *), 3);
	if (!pix->cmd_args)
		return (0);
	pix->av[n_cmd] += ft_strlen(pix->cmd) + 1;
	pix->cmd_args[1] = ft_clean_cmd(pix->av[n_cmd]);
	if (!pix->cmd_args[1])
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
	ft_strlcpy(cmd, cmd_tot, i + 1);
	return (cmd);
}

char	*ft_clean_cmd(char *cmd_tot)
{
	int		i;
	int		size;
	char	*cmd_clean;

	i = 0;
	size = 0;
	cmd_clean = (char *)ft_calloc(sizeof(char), ft_clean_size(cmd_tot) + 1);
	if (!cmd_clean)
		return (0);
	while (cmd_tot[i])
	{
		while (cmd_tot[i] && cmd_tot[i] != '\\')
		{
			if (!ft_strchr("\"\'\0", cmd_tot[i]))
				cmd_clean[size++] = cmd_tot[i];
			i++;
		}
		if (cmd_tot[i] && cmd_tot[i + 1] && cmd_tot[i] == '\\'
			&& ft_strchr("\"\'\\\0", cmd_tot[i + 1]))
				cmd_clean[size++] = cmd_tot[++i];
		i += (cmd_tot[i] != '\0');
	}
	return (cmd_clean);
}

int	ft_clean_size(char *cmd_tot)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (cmd_tot[i])
	{
		while (cmd_tot[i] && cmd_tot[i] != '\\')
		{
			if (!ft_strchr("\"\'\0", cmd_tot[i]))
				size++;
			i++;
		}
		if (cmd_tot[i] && cmd_tot[i + 1] && cmd_tot[i] == '\\'
			&& ft_strchr("\"\'\\\0", cmd_tot[i + 1]))
				size++;
		i += (cmd_tot[i] != '\0');
	}
	return (size);
}
