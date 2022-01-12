/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:36:48 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 18:41:53 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_check(char *map)
{
	char	*temp;

	if (!map)
		return (0);
	if (ft_strlen(map) < 5)
		return (0);
	temp = ft_strrchr(map, '.');
	if (!temp)
		return (0);
	if (ft_strlen(++temp) > 3)
		return (0);
	if (ft_strncmp("cub", temp, 3) == 0)
		return (1);
	return (0);
}

int	argv_check(int argc, char **argv)
{
	if (argc < 2)
		error_handler("submit the map\n");
	if (argc > 3)
		error_handler("too many arguments\n");
	if (argc > 1)
	{
		if (file_check(argv[1]) == 0)
			error_handler("argv error\n");
		if (argc == 3)
		{
			if ((ft_strlen(argv[2]) != 6))
				error_handler("invalid third argument\n");
			if (ft_strncmp("--save", argv[2], 6) != 0)
				error_handler("invalid third argument\n");
		}
	}
	return (1);
}
