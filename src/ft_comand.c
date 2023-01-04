/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/04 12:31:17 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

char	*ft_check_cmd(t_pix *pix, int cmd)
{
	char	**cmd_tot;
	char	*cmd;

	cmd_tot = ft_split(pix->av[cmd], ' ');
	if (!cmd_tot)
		return (NULL);
	pix->cmd = cmd_tot[0];
	i = 0;
	ft_clean_cmd(cmd_tot, 0);
	pix->cmd_args = cmd_tot;
	return (cmd);
}

int	ft_check_cmd_path(t_pix *pix)
{
	char	*tmp;
	int		i;

	i = -1;
	while (pix->paths[++i])
	{
		pix->cmd_path = ft_strjoin(pix->paths[i], pix->cmd);
		if (!access(pix->cmd_path, F_OK))
			return (1);
		ft_free(&(pix->cmd_path));
	}
	pix->err = ERR_PATH;
	return (0);
}

int	ft_clean_cmd(char **cmd_tot, int mode)
{
	int		i;
	int		j;
	int		size;
	char	**cmd_clean;

	size = 0;
	while (cmd_tot[++i])
	{
		j = -1;
		if (!mode)
		{
			size = ft_clean_cmd(cmd_tot, 1);
			cmd_clean[i] = (char *)ft_calloc(sizeof(char),
					(ft_strlen(cmd_tot[i]) - size) + 1);
		}
		while (cmd_tot[i][++j])
		{
			if ((ft_strnstr(&cmd_tot[i][j], "\\\"")
					|| ft_strnstr(&cmd_tot[i][j], "\\\'")) && mode == 1)
				size += 2;
			else if (cmd_tot[i][j] == '\\')
				size++;
			else if (!mode)
				cmd_clean[i][j] = cmd_tot[i][j];
		}
	}
	if (!mode)
	{
		ft_free(cmd_tot, 1);
		cmd_tot = cmd_clean;
	}
	return (size);
}
