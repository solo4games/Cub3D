/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:47:59 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 20:22:30 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_of_sprites(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	array_of_sprites(t_all *all, int i)
{
	int	j;
	int	k;

	k = 0;
	all->data_sprite->sprites = (t_sprite *)
		malloc(all->data_sprite->count_sprites * sizeof(t_sprite));
	if (!all->data_sprite->sprites)
		error_handler("malloc error\n");
	while (i < all->pos->map_height && all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				all->map[i][j] = 's';
				all->data_sprite->sprites[k].x = (double)i;
				all->data_sprite->sprites[k].y = (double)j;
				k++;
			}
			j++;
		}
		i++;
	}
}

static void	swap(t_sprite *left, t_sprite *right)
{
	t_sprite	temp;

	temp = *right;
	*right = *left;
	*left = temp;
}

void	quick_sort(t_sprite *sprite, int start, int end)
{
	int			left;
	int			right;
	double		center;

	left = start;
	right = end;
	center = sprite[(left + right) / 2].dist;
	if (left > right)
		return ;
	while (left <= right)
	{
		while (sprite[left].dist > center)
			left++;
		while (sprite[right].dist < center)
			right--;
		if (left <= right)
		{
			if (sprite[left].dist < sprite[right].dist)
				swap(&sprite[left], &sprite[right]);
			left++;
			right--;
		}
	}
	quick_sort(sprite, start, right);
	quick_sort(sprite, left, end);
}
