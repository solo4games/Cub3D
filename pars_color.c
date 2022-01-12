/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:38:42 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 12:04:33 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip(char **s, int flag)
{
	int	count;
	int	tmp;

	count = 0;
	tmp = 0;
	if (flag == 0)
	{
		while ((**s == ',' || **s == ' ' || **s == '+') && **s)
		{
			if (tmp == 1 && !ft_isdigit(**s))
				error_handler("bad color\n");
			if (**s == '+')
				tmp++;
			if (**s == ',')
				count++;
			(*s)++;
		}
	}
	if (flag == 1)
		while (**s >= '0' && **s <= '9' && **s)
			(*s)++;
	if (count > 1)
		error_handler("bad color\n");
}

static int	check_bad_char(char *s)
{
	int	count;
	int	i;
	int	count_1;

	count = 0;
	i = 0;
	count_1 = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != ',' && s[i] != '+')
			error_handler("bad color\n");
		if (ft_isdigit(s[i]))
			count_1++;
		while (ft_isdigit(s[i]))
			i++;
		if (s[i] == ',')
			count++;
		if (s[i])
			i++;
	}
	if (count_1 != 3)
		error_handler("bad color\n");
	return (count);
}

static int	color_init(char **s, int *count)
{
	int	color;

	if (len_number(*s, 1) > 3)
		error_handler("bad color\n");
	color = ft_atoi(*s);
	if (color > 255 || color < 0)
		error_handler("bad color\n");
	skip(s, 1);
	skip(s, 0);
	(*count)++;
	if (!ft_isdigit(**s) && *count != 3)
		error_handler("bad color\n");
	return (color);
}

static void	create_color(char **s, t_textures *tex, int *count, int type)
{
	int	r;
	int	g;
	int	b;

	r = color_init(s, count);
	g = color_init(s, count);
	b = color_init(s, count);
	if (type == 0)
		tex->f = r << 16 | g << 8 | b;
	if (type == 1)
		tex->c = r << 16 | g << 8 | b;
}

void	pars_colors(t_textures *tex, int type, char *s)
{
	int	count;

	count = 0;
	if (check_bad_char(s) != 2)
		error_handler("bad color\n");
	check_color(tex, type);
	skip_spaces(&s);
	create_color(&s, tex, &count, type);
	if (count != 3)
		error_handler("bad color\n");
	while (*s)
	{
		if (*s == ' ')
			s++;
		else
			error_handler("bad color\n");
	}
}
