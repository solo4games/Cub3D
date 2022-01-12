/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:13:38 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:11:00 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_move_w_s(int keycode, t_all *all)
{
	if (keycode == 13)
	{
		if (all->map[(int)(all->pos->pos_x + all->pos->dir_x
				* (all->draw->ms + 0.1))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_x * all->draw->ms;
		if (all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y
					+ all->pos->dir_y * (all->draw->ms + 0.1))] == '0')
			all->pos->pos_y += all->pos->dir_y * all->draw->ms;
	}
	if (keycode == 1)
	{
		if (all->map[(int)(all->pos->pos_x - all->pos->dir_x
				* (all->draw->ms + 0.01))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_x * all->draw->ms;
		if (all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y
					- all->pos->dir_y * (all->draw->ms + 0.01))] == '0')
			all->pos->pos_y -= all->pos->dir_y * all->draw->ms;
	}
}

static void	ft_move_a_d(int keycode, t_all *all)
{
	if (keycode == 0)
	{
		if (all->map[(int)(all->pos->pos_x - all->pos->dir_y
				* (all->draw->ms + 0.1))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x -= all->pos->dir_y * all->draw->ms;
		if (all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y
					+ all->pos->dir_x * (all->draw->ms + 0.1))] == '0')
			all->pos->pos_y += all->pos->dir_x * all->draw->ms;
	}
	if (keycode == 2)
	{
		if (all->map[(int)(all->pos->pos_x + all->pos->dir_y
				* (all->draw->ms + 0.1))][(int)all->pos->pos_y] == '0')
			all->pos->pos_x += all->pos->dir_y * all->draw->ms;
		if (all->map[(int)(all->pos->pos_x)][(int)(all->pos->pos_y
					- all->pos->dir_x * (all->draw->ms + 0.1))] == '0')
			all->pos->pos_y -= all->pos->dir_x * all->draw->ms;
	}
}

static void	ft_rot_left(t_all *all)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = 0;
	old_planex = 0;
	old_dirx = all->pos->dir_x;
	all->pos->dir_x = all->pos->dir_x * cos(all->draw->rs)
		- all->pos->dir_y * sin(all->draw->rs);
	all->pos->dir_y = old_dirx * sin(all->draw->rs)
		+ all->pos->dir_y * cos(all->draw->rs);
	old_planex = all->pos->plane_x;
	all->pos->plane_x = all->pos->plane_x * cos(all->draw->rs)
		- all->pos->plane_y * sin(all->draw->rs);
	all->pos->plane_y = old_planex * sin(all->draw->rs)
		+ all->pos->plane_y * cos(all->draw->rs);
}

static void	ft_rotate(int keycode, t_all *all)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = 0;
	old_planex = 0;
	if (keycode == 124)
	{
		old_dirx = all->pos->dir_x;
		all->pos->dir_x = all->pos->dir_x * cos(-all->draw->rs)
			- all->pos->dir_y * sin(-all->draw->rs);
		all->pos->dir_y = old_dirx * sin(-all->draw->rs)
			+ all->pos->dir_y * cos(-all->draw->rs);
		old_planex = all->pos->plane_x;
		all->pos->plane_x = all->pos->plane_x * cos(-all->draw->rs)
			- all->pos->plane_y * sin(-all->draw->rs);
		all->pos->plane_y = old_planex * sin(-all->draw->rs)
			+ all->pos->plane_y * cos(-all->draw->rs);
	}
	if (keycode == 123)
		ft_rot_left(all);
}

int	drawing(int keycode, t_all *all)
{
	if (keycode == 13 || keycode == 1)
		ft_move_w_s(keycode, all);
	if (keycode == 0 || keycode == 2)
		ft_move_a_d(keycode, all);
	if (keycode == 124 || keycode == 123)
		ft_rotate(keycode, all);
	if (keycode == 53)
		my_exit_from_game();
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2
		|| keycode == 123 || keycode == 124 || keycode == 53)
		draw_frame(all);
	mlx_do_sync(all->win->mlx);
	return (0);
}
