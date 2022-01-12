/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:08:50 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 12:04:51 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_textures(t_textures *tex, int side)
{
	if (side == 1)
		if (tex->no_texture != NULL)
			error_handler("duplicate data\n");
	if (side == 2)
		if (tex->so_texture != NULL)
			error_handler("duplicate data\n");
	if (side == 3)
		if (tex->we_texture != NULL)
			error_handler("duplicate data\n");
	if (side == 4)
		if (tex->ea_texture != NULL)
			error_handler("duplicate data\n");
	if (side == 5)
		if (tex->s_texture != NULL)
			error_handler("duplicate data\n");
}

void	check_xpm(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (i < 5)
		error_handler("not correct path or extension of file\n");
	if (ft_strncmp(".xpm", &s[i - 4], 4) != 0)
		error_handler("not correct path or extension of file\n");
}

void	pars_textures(t_textures *text, int side, char *s)
{
	int	i;

	i = 0;
	check_textures(text, side);
	skip_spaces(&s);
	check_xpm(s);
	while (s[i] && s[i] != ' ')
		i++;
	if (side == 1)
		text->no_texture = ft_substr(s, 0, i);
	if (side == 2)
		text->so_texture = ft_substr(s, 0, i);
	if (side == 3)
		text->we_texture = ft_substr(s, 0, i);
	if (side == 4)
		text->ea_texture = ft_substr(s, 0, i);
	if (side == 5)
		text->s_texture = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
			error_handler("not correct path or extension of file\n");
	}
}
