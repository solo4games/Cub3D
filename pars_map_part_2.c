/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_part_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:10:08 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 20:16:43 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dir(t_pos *pos, char temp)
{
	if (temp == 'W' || temp == 'E')
	{
		pos->dir_x = 0;
		pos->dir_y = 1;
		pos->plane_x = 0.66;
		pos->plane_y = 0;
		if (temp == 'W')
		{
			pos->dir_y = -1.0;
			pos->plane_x = -0.66;
		}
	}
	else if (temp == 'N' || temp == 'S')
	{
		pos->dir_x = -1;
		pos->dir_y = 0;
		pos->plane_x = 0;
		pos->plane_y = 0.66;
		if (temp == 'S')
		{
			pos->dir_x = 1.0;
			pos->plane_y = -0.66;
		}
	}
}

static void	check_sym(t_all *all, t_pos *pos, int i, int j)
{
	if (ft_strchr(" 012NSEW", all->map[i][j]) == NULL)
		error_handler("trash in file\n");
	else if (all->map[i][j] == 'N' || all->map[i][j] == 'E'
			|| all->map[i][j] == 'W' || all->map[i][j] == 'S')
	{
		if (all->dir == '\0')
		{
			pos->pos_x = i + 0.5;
			pos->pos_y = j + 0.5;
			all->dir = all->map[i][j];
			all->map[i][j] = '0';
			init_dir(pos, all->dir);
		}
		else
			error_handler("duplicate player position\n");
	}
}

void	init_pos(t_all *all, t_pos *pos)
{
	int		i;
	int		j;

	i = 0;
	all->dir = '\0';
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			check_sym(all, pos, i, j);
			j++;
		}
		i++;
	}
	if (all->dir == '\0')
		error_handler("player not found\n");
	pos->map_height = i;
}

void	check_up_down(char **map, int i, int h)
{
	while (map[0][i])
	{
		if (map[0][i] == '1' || map[0][i] == ' ')
			i++;
		else
			error_handler("bad boundaries\n");
	}
	i = 0;
	while (map[h - 1][i])
	{
		if ((map[h - 1][i] == '1' || map[h - 1][i] == ' '))
			i++;
		else
			error_handler("bad boundaries\n");
	}
}

void	check_boundary(t_all *all, char **map, t_pos *pos)
{
	int	i;
	int	h;

	i = 0;
	(void)all;
	h = pos->map_height;
	check_up_down(map, i, h);
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '1' || map[i][0] == ' ')
			i++;
		else
			error_handler("bad boundaries\n");
	}
	i = 0;
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '1'
				|| map[i][ft_strlen(map[i]) - 1] == ' ')
			i++;
		else
			error_handler("bad boundaries\n");
	}
}
