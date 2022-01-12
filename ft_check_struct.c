/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:45:38 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:11:38 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(t_textures *tex, int type)
{
	if (type == 0)
		if (tex->f != -1)
			error_handler("duplicate data\n");
	if (type == 1)
		if (tex->c != -1)
			error_handler("duplicate data\n");
}
