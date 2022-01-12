/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_texture_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 12:14:26 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 11:53:22 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor(int *j, int end, t_all *all, int i)
{
	while (*j < end - 1)
	{
		my_mlx_pixel_put(all, i, *j, all->textures->f);
		(*j)++;
	}
}

static void	draw_ceil(int *j, int end, t_all *all, int i)
{
	while (*j < end)
	{
		my_mlx_pixel_put(all, i, *j, all->textures->c);
		(*j)++;
	}
}

void	draw_frame(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < all->textures->x)
	{
		j = 0;
		init_raycast(all->raycast, i, all->textures->x, all->pos);
		init_step(all->raycast, all->pos);
		calc_dda(all->raycast, all->map, all->pos);
		init_draw(all->draw, all->raycast, all, all->pos);
		draw_ceil(&j, all->draw->start, all, i);
		draw_wall(all, all->draw, &j, i);
		draw_floor(&j, all->textures->y, all, i);
		all->data_sprite->z_buffer[i] = all->raycast->walldist;
		i++;
	}
	draw_sprites(all);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, all->win->win);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

void	draw_wall(t_all *all, t_draw *d, int *y, int x)
{
	while (*y < d->end)
	{
		d->tex_y = (int)d->tex_pos;
		d->tex_pos += d->step;
		if (all->raycast->side == 0 && all->raycast->step_x == -1)
			d->color = (*(unsigned int *)(all->no->addr + (d->tex_y
							* all->no->length + d->tex_x
							* (all->no->bpp / 8))));
		else if (all->raycast->side == 0 && all->raycast->step_x == 1)
			d->color = (*(unsigned int *)(all->so->addr + (d->tex_y
							* all->so->length + d->tex_x
							* (all->so->bpp / 8))));
		else if (all->raycast->side == 1 && all->raycast->step_y == -1)
			d->color = (*(unsigned int *)(all->we->addr + (d->tex_y
							* all->we->length + d->tex_x
							* (all->we->bpp / 8))));
		else if (all->raycast->side == 1 && all->raycast->step_y == 1)
			d->color = (*(unsigned int *)(all->ea->addr + (d->tex_y
							* all->ea->length + d->tex_x
							* (all->ea->bpp / 8))));
		my_mlx_pixel_put(all, x, *y, d->color);
		(*y)++;
	}
}

int	raycasting(t_all *all)
{
	int	i;

	i = 0;
	all->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	all->draw = (t_draw *)malloc(sizeof(t_draw));
	if (!all->raycast || !all->draw)
		error_handler("malloc error\n");
	all->draw->ms = 0.2;
	all->draw->rs = 0.15;
	draw_frame(all);
	mlx_hook(all->win->win, 2, (1L << 0), &drawing, all);
	mlx_hook(all->win->win, 17, (1L << 0), &my_exit_from_game, all);
	mlx_loop(all->win->mlx);
	return (0);
}
