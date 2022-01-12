/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 14:39:02 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 18:44:37 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_step(t_raycast *ray, t_pos *pos)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (pos->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - pos->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (pos->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - pos->pos_y) * ray->deltadist_y;
	}
}

void	init_raycast(t_raycast *raycast, int x, int w, t_pos *pos)
{
	raycast->camera_x = 2 * x / (double)w - 1;
	raycast->raydir_x = pos->dir_x + pos->plane_x * raycast->camera_x;
	raycast->raydir_y = pos->dir_y + pos->plane_y * raycast->camera_x;
	raycast->map_x = (int)pos->pos_x;
	raycast->map_y = (int)pos->pos_y;
	if (raycast->raydir_y == 0)
		raycast->deltadist_x = 0;
	else
	{
		if (raycast->raydir_x == 0)
			raycast->deltadist_x = 1;
		else
			raycast->deltadist_x = fabs(1 / raycast->raydir_x);
	}
	if (raycast->raydir_x == 0)
		raycast->deltadist_y = 0;
	else
	{
		if (raycast->raydir_y == 0)
			raycast->deltadist_y = 1;
		else
			raycast->deltadist_y = fabs(1 / raycast->raydir_y);
	}
	raycast->hit = 0;
	raycast->walldist = 0;
}

void	calc_dda(t_raycast *ray, char **map, t_pos *p)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->walldist = (ray->map_x - p->pos_x
				+ (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->walldist = (ray->map_y - p->pos_y
				+ (1 - ray->step_y) / 2) / ray->raydir_y;
}

static void	tex_params(t_all *all, t_draw *draw)
{
	if (all->raycast->side == 0 && all->raycast->step_x == -1)
	{
		draw->tex_width = all->no->width;
		draw->tex_height = all->no->height;
	}
	if (all->raycast->side == 0 && all->raycast->step_x == 1)
	{
		draw->tex_width = all->so->width;
		draw->tex_height = all->so->height;
	}
	if (all->raycast->side == 1 && all->raycast->step_y == -1)
	{
		draw->tex_width = all->we->width;
		draw->tex_height = all->we->height;
	}
	if (all->raycast->side == 1 && all->raycast->step_y == 1)
	{
		draw->tex_width = all->ea->width;
		draw->tex_height = all->ea->height;
	}
}

void	init_draw(t_draw *draw, t_raycast *r, t_all *all, t_pos *p)
{
	draw->color = 0;
	tex_params(all, draw);
	draw->line_h = (int)(all->textures->x * 0.66 / r->walldist);
	draw->start = -draw->line_h / 2 + all->textures->y / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + all->textures->y / 2;
	if (draw->end >= all->textures->y)
		draw->end = all->textures->y - 1;
	if (r->side == 0)
		draw->wall_x = p->pos_y + r->walldist * r->raydir_y;
	else
		draw->wall_x = p->pos_x + r->walldist * r->raydir_x;
	draw->wall_x -= floor((draw->wall_x));
	draw->tex_x = (int)(draw->wall_x * (double)draw->tex_width);
	if (r->side == 0 && r->raydir_x > 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	draw->step = 1.0 * draw->tex_height / draw->line_h;
	draw->tex_pos = (draw->start - all->textures->y / 2
			+ draw->line_h / 2) * draw->step;
}
