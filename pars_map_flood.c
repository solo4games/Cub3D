/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_flood.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:51:13 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 20:13:51 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_width_map(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	flood_fill(char **map, t_pos *p, int x, int y)
{
	char	new_color;

	new_color = '#';
	if (x > 0 && x < p->map_width && y > 0 && y < (p->map_height + 2)
		&& (map[y][x] == ' ' || map[y][x] == '*'))
		error_handler("bad map\n");
	if (x >= 0 && x < p->map_width && y >= 0 && y < (p->map_height + 2)
		&& (map[y][x] == '0' || map[y][x] == '2') && map[y][x] != new_color)
	{
		map[y][x] = new_color;
		flood_fill(map, p, x + 1, y);
		flood_fill(map, p, x - 1, y);
		flood_fill(map, p, x, y + 1);
		flood_fill(map, p, x, y - 1);
	}
}

void	flood(t_pos *pos, t_all *all)
{
	int		i;
	int		j;
	char	**new_map;

	i = 1;
	pos->map_width = max_width_map(all->map);
	new_map = copy_map(pos, all);
	while (new_map[i] && i < (pos->map_height + 2))
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0' || new_map[i][j] == '2')
				flood_fill(new_map, pos, j, i);
			j++;
		}
		i++;
	}
	free_new_map(pos, new_map);
}
