/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_copy_mainmap.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:42:42 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 20:11:52 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_main_map(t_pos *p, char **map, int i, t_all *all)
{
	int		k;
	int		j;
	char	new_symbol;

	k = 0;
	new_symbol = '*';
	while (k < p->map_height)
	{
		map[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
		if (!map[i])
			error_handler("malloc error\n");
		ft_strcpy(map[i], all->map[k]);
		if ((int)ft_strlen(all->map[k]) < p->map_width)
		{
			j = ft_strlen(all->map[k]);
			while (j < p->map_width)
			{
				map[i][j] = new_symbol;
				j++;
			}
		}
		k++;
		i++;
	}
	return (i);
}

char	**copy_map(t_pos *p, t_all *all)
{
	char			**new;
	int				i;
	unsigned char	new_symbol;

	new_symbol = '*';
	i = 0;
	new = (char **)ft_calloc(p->map_height + 3, sizeof(char *));
	new[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
	if (!new || !new[i])
		error_handler("malloc error\n");
	ft_memset(new[i++], new_symbol, p->map_width);
	i = copy_main_map(p, new, i, all);
	new[i] = (char *)ft_calloc(p->map_width + 1, sizeof(char));
	if (!new[i])
		error_handler("malloc error\n");
	ft_memset(new[i], new_symbol, p->map_width);
	i = 0;
	return (new);
}

void	free_new_map(t_pos *p, char **new_map)
{
	int	i;

	i = 0;
	while (i < p->map_height + 2)
	{
		free(new_map[i]);
		i++;
	}
	free(new_map);
}
