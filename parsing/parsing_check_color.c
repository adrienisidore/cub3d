/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:32:35 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_conformed(char *s)
{
	int	i;

	i = 0;
	if (s[0] && !(s[0] >= '0' && s[0] <= '9'))
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] && s[i++] != ',')
		return (1);
	if (s[i] && !(s[i] >= '0' && s[i] <= '9'))
		return (1);
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] && s[i++] != ',')
		return (1);
	if (s[i] && !(s[i] >= '0' && s[i] <= '9'))
		return (1);
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i])
	{
		if (ft_is_space(s[i++]) == 0)
			return (1);
	}
	return (0);
}

int	ft_get_nb(char *s, int f, int *i)
{
	int	nb;

	nb = 0;
	if (f == 1)
	{
		(*i)++;
		while (s[*i] && s[*i] != ',')
			nb = nb * 10 + s[(*i)++] - '0';
	}
	else
	{
		if (!s[*i] || (s[*i] == ',' && !s[(*i) + 1]))
			return (-1);
		(*i)++;
		while (s[*i] || (s[*i] && ft_is_space(s[*i]) != 1))
			nb = nb * 10 + s[(*i)++] - '0';
	}
	if (!(nb >= 0 && nb <= 255))
		return (-1);
	return (nb);
}

int	ft_get_color_ceiling(t_data *data)
{
	int	i;
	int	nb;

	i = -1;
	nb = ft_get_nb(data->c, 1, &i);
	if (nb == -1)
		return (1);
	data->ceiling[0] = nb;
	if (!(data->c[i]))
		return (1);
	nb = ft_get_nb(data->c, 1, &i);
	if (nb == -1)
		return (1);
	data->ceiling[1] = nb;
	nb = ft_get_nb(data->c, 2, &i);
	if (nb == -1)
		return (1);
	data->ceiling[2] = nb;
	return (0);
}

int	ft_get_color_floor(t_data *data)
{
	int	i;
	int	nb;

	i = -1;
	nb = ft_get_nb(data->f, 1, &i);
	if (nb == -1)
		return (1);
	data->floor[0] = nb;
	if (!(data->f[i]))
		return (1);
	nb = ft_get_nb(data->f, 1, &i);
	if (nb == -1)
		return (1);
	data->floor[1] = nb;
	nb = ft_get_nb(data->f, 2, &i);
	if (nb == -1)
		return (1);
	data->floor[2] = nb;
	return (0);
}

int	ft_check_color(t_data *data, t_gc *gc)
{
	data->ceiling = gc_malloc(sizeof(int) * 3, gc);
	data->floor = gc_malloc(sizeof(int) * 3, gc);
	if (ft_is_conformed(data->c) == 1)
		return (1);
	if (ft_is_conformed(data->f) == 1)
		return (1);
	if (ft_get_color_ceiling(data) == 1)
		return (1);
	if (ft_get_color_floor(data) == 1)
		return (1);
	return (0);
}
