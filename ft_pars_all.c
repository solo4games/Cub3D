/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:28:39 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/02 19:23:27 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

static t_list	*file_read(int fd)
{
	char	*line;
	t_list	*list;
	int		i;

	line = NULL;
	list = NULL;
	i = get_next_line(fd, &line);
	while (i > 0)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
		i = get_next_line(fd, &line);
	}
	ft_lstadd_back(&list, ft_lstnew(line));
	if (i < 0)
		return (NULL);
	return (list);
}

t_all	*pars_all(char *name_of_file)
{
	int		fd;
	t_all	*all;
	t_list	*list;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		error_handler("malloc error\n");
	fd = open_file(name_of_file);
	if (fd < 0)
		error_handler("opening error\n");
	list = file_read(fd);
	if (!list)
		error_handler("reading error\n");
	pars_file(&list, all);
	return (all);
}
