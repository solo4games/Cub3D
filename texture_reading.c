/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_reading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 13:30:58 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 11:45:38 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_all_text(t_all *all, char *texname, t_datatext *tex)
{
	tex->img = mlx_xpm_file_to_image(all->win->mlx, texname,
			&tex->width, &tex->height);
	if (tex->img > 0)
		tex->addr = (char *)mlx_get_data_addr(tex->img, &tex->bpp,
				&tex->length, &tex->endian);
	else
		error_handler("not correct path or extension of file\n");
}

void	reading_textures(t_all *all)
{
	all->no = (t_datatext *)malloc(sizeof(t_datatext));
	all->so = (t_datatext *)malloc(sizeof(t_datatext));
	all->we = (t_datatext *)malloc(sizeof(t_datatext));
	all->ea = (t_datatext *)malloc(sizeof(t_datatext));
	all->s = (t_datatext *)malloc(sizeof(t_datatext));
	if (!all->no || !all->so || !all->we || !all->ea || !all->s)
		error_handler("malloc error\n");
	init_all_text(all, all->textures->no_texture, all->no);
	init_all_text(all, all->textures->so_texture, all->so);
	init_all_text(all, all->textures->we_texture, all->we);
	init_all_text(all, all->textures->ea_texture, all->ea);
	init_all_text(all, all->textures->s_texture, all->s);
}
