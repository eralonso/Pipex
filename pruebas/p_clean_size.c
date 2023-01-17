/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clean_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:14:43 by eralonso          #+#    #+#             */
/*   Updated: 2023/01/12 17:39:08 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdio.h>
#include	"inc/pipex.h"

int	ft_count_delimiter(char *str, char del, int mode)
{
	int	i;

	i = 0;
	if (mode)
		while (str[i] && str[i + 1] && str[i] == del)
			i++;
	else
		while (str[i] && str[i + 1] && str[i] != del)
			i++;
	return (i);
}

int	ft_final_size(char *str)
{
	int		size;
	int		i;
	char	del;

	i = -1;
	size = 0;
	while (str[++i])
	{
		del = ' ';
		i += ft_count_delimiter(&str[i], del, 1);
		if (str[i] && ft_strchr("\'\"\0", str[i]) && (!i
				|| (i && str[i - 1] != '\\')))
			del = str[i++];
		i += ft_count_delimiter(&str[i], del, 1);
		if (str[i] && !(ft_strchr("\'\" \0", str[i]) && (!i
					|| (i && str[i - 1] != '\\'))))
			size++;
		i += ft_count_delimiter(&str[i], del, 0);
	}
	return (size);
}


		/*if (ft_strchr("\'\"\0", str[i]) && (!i
					|| (i && str[i - 1] != '\\')))
			del = str[i++];
		printf("  del == %c\n", del);
		while (str[i] && str[i] == del)
		{
			if (del == ' ' && ft_strchr("\'\"\0", str[i]) && (!i
					|| (i && str[i - 1] != '\\')))
				break ;
			i++;
		}
		if (str[i] && !(ft_strchr("\'\" \0", str[i]) && (!i
					|| (i && str[i - 1] != '\\'))))
			size++;
		while (str[i] && str[i] != del)
		{
			if (del == ' ' && ft_strchr("\'\"\0", str[i]) && (!i
					|| (i && str[i - 1] != '\\')))
				break ;
			i++;
		}
		i += (str[i] != '\0') * (ft_strchr("\'\"\0", str[i]) && (!i
					|| (i && str[i - 1] != '\\')));*/

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	while (ac-- > 1)
	{
		printf("\n  av[%i] == %s\n", ac, av[ac]);
		printf("\n  El string ha contar va ha ser == %s\n", av[ac]);
		printf("\n  len == %i\n\n", ft_final_size(av[ac]));
	}
	return (0);
}
