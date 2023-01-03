/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:22:33 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/03 19:58:08 by eralonso         ###   ########.fr       */
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
	pix->cmd_args = ++cmd_tot;
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
