/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/24 16:54:30 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_player(t_data *data, int *f, int c, int l)
{
	if ((data->map[l][c] == 'S' || data->map[l][c] == 'E'
		|| data->map[l][c] == 'W' || data->map[l][c] == 'N') && (*f) == 1)
	{
		write(2, "Error\nMultiple players\n", 24);
		return (1);
	}
	if (data->map[l][c] == 'S' || data->map[l][c] == 'E'
		|| data->map[l][c] == 'W' || data->map[l][c] == 'N')
	{
		(*f) = 1;
		data->pos = data->map[l][c];
		data->pos_x = c;
		data->pos_y = l;
	}
	return (0);
}

int	ft_get_pos(t_data *data)
{
	int	f;
	int	l;
	int	c;

	f = 0;
	l = 0;
	while (l < data->lg)
	{
		c = 0;
		while (c < data->cl)
		{
			if (ft_check_player(data, &f, c, l) == 1)
				return (1);
			c++;
		}
		l++;
	}
	if (f == 0)
	{
		write(2, "Error\nNo player\n", 17);
		return (1);
	}
	return (0);
}

int	ft_flood(t_data *data, int l, int c)
{
	if (!(data->map[l][c + 1] && (data->map[l][c + 1] == '1'
		|| ft_is_o(data->map[l][c + 1]) == 1)))
		return (1);
	if (!(c != 0 && (data->map[l][c - 1] == '1'
			|| ft_is_o(data->map[l][c - 1]) == 1)))
		return (1);
	if (!(l != 0 && (data->map[l - 1][c] == '1'
			|| ft_is_o(data->map[l - 1][c]) == 1)))
		return (1);
	if (!(data->map[l + 1] && (data->map[l + 1][c] == '1'
			|| ft_is_o(data->map[l + 1][c]) == 1)))
		return (1);
	return (0);
}

int	ft_is_map_valid(t_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < data->lg)
	{
		c = 0;
		while (c < data->cl)
		{
			if (ft_is_o(data->map[l][c]) == 1)
			{
				if (ft_flood(data, l, c) == 1)
				{
					write(2, "Error\nInvalid map\n", 19);
					return (1);
				}
			}
			c++;
		}
		l++;
	}
	return (0);
}

int	ft_flood_fill(t_data *data, t_gc *gc)
{
	(void) gc;
	if (!data->map[0])
	{
		write(2, "Error\nNo map\n", 14);
		return (1);
	}
	if (ft_is_map_valid(data) == 1)
		return (1);
	if (ft_get_pos(data) == 1)
		return (1);
	return (0);
}
