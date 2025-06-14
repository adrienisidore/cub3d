/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/14 19:45:49 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//penser au cas avec une seule ligne ou une seule colonne a tester

int	ft_check_player(t_data *data, int *f, int c, int l)
{
	if ((data->map[l][c] == 'S' || data->map[l][c] == 'E'
		|| data->map[l][c] == 'W' || data->map[l][c] == 'N') && (*f) == 1)
	{
		printf("Error\nMultiple players\n");
		return (1);
	}
	if (data->map[l][c] == 'S' || data->map[l][c] == 'E'
		|| data->map[l][c] == 'W' || data->map[l][c] == 'N')
	{
		(*f) = 1;
		data->pos = data->map[l][c];
		data->pos_x = c;
		data->pos_y = l;
		// printf("x = %d\n", data->pos_x);
		// printf("y = %d\n", data->pos_y);
		// data->pos = data->map[l][c];
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
		printf("Error\nNo player\n");
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
					printf("Error\nInvalid map\n");
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
		printf("Error\nNo map\n");
		return (1);
	}
	if (ft_is_map_valid(data) == 1)
		return (1);
	if (ft_get_pos(data) == 1)
		return (1);
	return (0);
}
