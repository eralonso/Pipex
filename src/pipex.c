/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:39:36 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/03 17:06:59 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pix	pix;

	if (ac != 5)
		return (ft_error(NUM_ARG));
	if (!ft_init_pipex(&pix, ac, av, env))
		return (ft_error(pix.err));
	int	i = -1;
	while (pix.paths[++i])
		ft_printf(1, "pix.paths[%i] == %s\n", i, pix.paths[i]);
	return (0);
}
