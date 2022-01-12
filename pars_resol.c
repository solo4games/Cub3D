/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_resol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:39:51 by lbrandy           #+#    #+#             */
/*   Updated: 2021/04/03 12:04:44 by lbrandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_res(char *s, int len)
{
	int	i;
	int	number;

	i = 0;
	if (len > 7)
		return (16384);
	while (s[i] == '0')
		i++;
	if (!ft_isdigit(s[i]))
		error_handler("incorrect resolution\n");
	number = ft_atoi(&s[i]);
	if (number == 0)
		error_handler("incorrect resolution\n");
	return (number);
}

int	len_number(char *s, int flag)
{
	int	len;

	len = 0;
	while (*s == '0')
		s++;
	if (!ft_isdigit(*s) && flag == 0)
		error_handler("incorrect resolution\n");
	if (!ft_isdigit(*s) && flag == 1)
		len++;
	while (*s && ft_isdigit(*s))
	{
		s++;
		len++;
	}
	return (len);
}

static int	check_valid(char *res)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (res[i])
	{
		if (!ft_isdigit(res[i]) && res[i] != ' ' && res[i] != '+')
			return (-1);
		i++;
	}
	i = 0;
	while (res[i])
	{
		if (ft_isdigit(res[i]))
		{
			while (res[i] == '0')
				i++;
			i += len_number(&res[i], 0);
			count++;
		}
		if (res[i])
			i++;
	}
	return (count);
}

void	pars_res(char *res, t_textures *t, int len)
{
	if (check_valid(res) == -1 || check_valid(res) != 2)
		error_handler("incorrect resolution\n");
	if (t->x != -1 && t->y != -1)
		error_handler("duplicate data\n");
	skip_spaces(&res);
	len = len_number(res, 0);
	if (ft_isdigit(*res))
		t->x = count_res(res, len);
	skip(&res, 1);
	skip_spaces(&res);
	len = len_number(res, 0);
	if (ft_isdigit(*res))
		t->y = count_res(res, len);
	skip(&res, 1);
	while (*res)
	{
		if (*res == ' ')
			res++;
		else
			error_handler("incorrect resolution\n");
	}
}
