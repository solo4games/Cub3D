/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:05:41 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 11:59:59 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_letter(char *str, t_textures *t)
{
	if (str)
	{
		if (ft_strncmp("R ", str, 2) == 0)
			pars_res(str + 2, t, 0);
		else if (ft_strncmp("NO ", str, 3) == 0)
			pars_textures(t, 1, str + 3);
		else if (ft_strncmp("SO ", str, 3) == 0)
			pars_textures(t, 2, str + 3);
		else if (ft_strncmp("WE ", str, 3) == 0)
			pars_textures(t, 3, str + 3);
		else if (ft_strncmp("EA ", str, 3) == 0)
			pars_textures(t, 4, str + 3);
		else if (ft_strncmp("S ", str, 2) == 0)
			pars_textures(t, 5, str + 2);
		else if (ft_strncmp("F ", str, 2) == 0)
			pars_colors(t, 0, str + 2);
		else if (ft_strncmp("C ", str, 2) == 0)
			pars_colors(t, 1, str + 2);
		else
			check_trash_str(str, t);
	}
}

t_list	*pars_struct(t_textures *t, t_list **list)
{
	t_list		*tmp;

	tmp = *list;
	init_struct(t);
	while (tmp)
	{
		if (!check_full_struct(t))
		{
			check_letter(tmp->content, t);
			tmp = tmp->next;
		}
		else
			break ;
	}
	return (tmp);
}

void	pars_file(t_list **list, t_all *all)
{
	t_list	*tmp;

	all->textures = (t_textures *)malloc(sizeof(t_textures));
	if (!all->textures)
		error_handler("malloc error\n");
	tmp = pars_struct(all->textures, list);
	all->pos = pars_map(tmp, all);
	ft_lstclear(list, ft_lstfree_cont);
}
