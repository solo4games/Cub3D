/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:20 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:31:25 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_full_struct(t_textures *t)
{
	return (t->x != -1 && t->y != -1 && t->no_texture != NULL
		&& t->so_texture != NULL && t->we_texture != NULL
		&& t->ea_texture != NULL && t->s_texture != NULL
		&& t->f != -1 && t->c != -1);
}

void	init_struct(t_textures *t)
{
	t->x = -1;
	t->y = -1;
	t->no_texture = NULL;
	t->so_texture = NULL;
	t->we_texture = NULL;
	t->ea_texture = NULL;
	t->s_texture = NULL;
	t->f = -1;
	t->c = -1;
}

int	main(int argc, char *argv[])
{
	t_all	*all;

	argv_check(argc, argv);
	all = pars_all(argv[1]);
	if (!all)
		error_handler("malloc error\n");
	if (argc == 3)
		screen_save(all, argc);
	all->win = (t_win *)malloc(sizeof(t_win));
	if (!all->win)
		error_handler("malloc error\n");
	init_mlx(all->win, all, argc);
	init_sprite(all);
	reading_textures(all);
	raycasting(all);
	return (0);
}
