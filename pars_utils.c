/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:33:30 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 12:03:18 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char **s)
{
	int	count;

	count = 0;
	while ((**s == ' ' || **s == '\t' || **s == '+') && **s)
	{
		if (count == 1 && !ft_isdigit(**s))
			error_handler("trash in file\n");
		if (**s == '+')
			count++;
		(*s)++;
	}
}

void	check_trash_str(char *s, t_textures *t)
{
	while (*s)
	{
		if (*s != ' ' && check_full_struct(t))
			error_handler("trash in file\n");
		else if (*s != ' ' && !check_full_struct(t))
			error_handler("bad keys\n");
		s++;
	}
}

void	ft_lstfree_cont(void *content)
{
	if (content)
		free(content);
}

void	ft_filling_map(t_list *list, t_all *all, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		all->map[i] = ft_strdup(list->content);
		if (!all->map[i])
			error_handler("malloc error\n");
		list = list->next;
		i++;
	}
}
