/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:55 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_first_part(t_data *data, t_gc *gc)
{
	int		r;

	while (data->line != NULL && data->flag == 0)
	{
		data->i = 0;
		data->line = get_next_line(data->fd, data, gc);
		ft_lose_space(data->line, &data->i);
		r = ft_check_if_texture(&data->i, data->line);
		if (r == 9)
			return (1);
		if (r == 0)
		{
			printf("Error\nMissing texture or color\n");
			return (1);
		}
		if (r == 8)
			data->flag = 1;
		ft_lose_space(data->line, &data->i);
		if (r != 7 && ft_process_data(r, data->line, data, gc) == 1)
			return (1);
		(data->lg)++;
	}
	return (0);
}

int	ft_second_part(t_data *data, t_gc *gc)
{
	if (ft_arr_size(data, gc) == 1)
		return (1);
	ft_get_map(data, gc);
	if (ft_flood_fill(data, gc) == 1)
		return (1);
	return (0);
}

int	ft_get_data(t_data *data, t_gc *gc)
{
	data->line = ft_strdup_bis("", gc);
	data->i = 0;
	if (ft_first_part(data, gc) == 1)
		return (1);
	if (ft_check_walls(data, gc) == 1)
		return (1);
	if (ft_second_part(data, gc) == 1)
		return (1);
	return (0);
}

int	ft_parsing(char **argv, t_data *data, t_gc *gc)
{
	if (!argv[1])
	{
		write(2, "Error: No file found\n", 22);
		return (1);
	}
	if (ft_check_extention(argv[1]) == 1)
	{
		write(2, "Error\nWrong filetype\n", 22);
		return (1);
	}
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	if (ft_get_data(data, gc) == 1)
		return (close(data->fd), (1));
	close(data->fd);
	return (0);
}
