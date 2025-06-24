/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:55:31 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_files(t_data *data)
{
	int	fd;

	fd = open(data->ea, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->no, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->we, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(data->so, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	ft_check_walls(t_data *data, t_gc *gc)
{
	if (data->no == NULL || data->so == NULL || data->we == NULL
		|| data->ea == NULL || data->c == NULL || data->f == NULL)
	{
		write(2, "Error\nMissing texture or color\n", 32);
		return (1);
	}
	if (ft_xpm_extention(data->no) == 1 || ft_xpm_extention(data->so) == 1
		|| ft_xpm_extention(data->we) == 1 || ft_xpm_extention(data->ea) == 1)
	{
		write(2, "Error\nWrong texture extention\n", 31);
		return (1);
	}
	if (ft_check_color(data, gc) == 1)
	{
		write(2, "Error\nWrong color data\n", 24);
		return (1);
	}
	if (ft_check_files(data) == 1)
	{
		write(2, "Error\nProblem while opening xpm file\n", 38);
		return (1);
	}
	return (0);
}
