/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:48:10 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:32:21 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *a, int x, int y, int color)
{
	char	*dst;

	dst = a->win->addr + (y * a->win->length + x * (a->win->bpp / 8));
	*(unsigned int *)dst = color;
}

int	my_exit_from_game(void)
{
	write(1, "Thank you, goodbye!\n", 20);
	exit(0);
}

void	check_screen_size(t_all *all)
{
	if (all->textures->x > 16384)
		all->textures->x = 16384;
	if (all->textures->y > 16384)
		all->textures->y = 16384;
}

void	init_mlx(t_win *w, t_all *all, int argc)
{
	int	x;
	int	y;

	w->mlx = mlx_init();
	mlx_get_screen_size(w->mlx, &x, &y);
	if (argc != 3)
	{
		if (all->textures->x > x)
			all->textures->x = x;
		if (all->textures->y > y)
			all->textures->y = y;
	}
	if (argc == 3)
		check_screen_size(all);
	w->win = mlx_new_window(w->mlx, all->textures->x,
			all->textures->y, "cub3D");
	if (!w->win)
		error_handler("malloc error\n");
	w->img = (char *)mlx_new_image(w->mlx, all->textures->x, all->textures->y);
	w->addr = (char *)mlx_get_data_addr(w->img, &(w->bpp),
			&(w->length), &(w->endian));
}

void	init_sprite(t_all *all)
{
	int	i;

	i = 0;
	all->data_sprite = (t_datasprite *)malloc(sizeof(t_datasprite));
	if (!all->data_sprite)
		error_handler("malloc error\n");
	all->data_sprite->count_sprites = count_of_sprites(all->map);
	array_of_sprites(all, i);
	all->data_sprite->z_buffer = (double *)
		malloc((all->textures->x + 1) * sizeof(double));
	if (!all->data_sprite->z_buffer)
		error_handler("malloc error\n");
}
