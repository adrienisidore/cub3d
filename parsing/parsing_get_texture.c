/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:32:06 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_if_texture(int *i, char *line)
{
	int	r;

	r = 0;
	if (!(line + (*i)))
		return (7);
	if (ft_strcmp(line + (*i), "\0", 1) == 0)
		r = 7;
	if (ft_strcmp(line + (*i), "NO", 2) == 0 && ft_is_space(line[*i + 2]) == 1)
		r = 1;
	if (ft_strcmp(line + (*i), "SO ", 2) == 0
		&& ft_is_space(line[*i + 2]) == 1)
		r = 2;
	if (ft_strcmp(line + (*i), "WE ", 2) == 0 && ft_is_space(line[*i + 2]) == 1)
		r = 3;
	if (ft_strcmp(line + (*i), "EA ", 2) == 0
		&& ft_is_space(line[*i + 2]) == 1)
		r = 4;
	if (ft_strcmp(line + (*i), "C ", 1) == 0 && ft_is_space(line[*i + 1]) == 1)
		r = 5;
	if (ft_strcmp(line + (*i), "F ", 1) == 0 && ft_is_space(line[*i + 1]) == 1)
		r = 6;
	if (ft_strcmp(line + (*i), "1", 1) == 0
		|| ft_strcmp(line + (*i), "0", 1) == 0)
		r = 8;
	return (r);
}

char	*ft_get_file(char *line, t_data *data, t_gc *gc)
{
	char	*s;
	int		size;
	int		t;

	size = data->i;
	while (line[data->i] && (ft_is_space(line[data->i]) == 0))
		(data->i)++;
	ft_lose_space(line, &data->i);
	t = 0;
	while (line[data->i + t] && (line[data->i + t] != '\n'
			|| line[data->i + t] != '\0' || line[data->i + t] == ' '))
		t++;
	s = gc_malloc(sizeof(char) * (t + 1), gc);
	t = 0;
	while (line[data->i] && (line[data->i] != '\n' && line[data->i] != '\0'))
	{
		s[t] = line[data->i];
		(data->i)++;
		t++;
	}
	s[t] = '\0';
	return (s);
}

int	ft_process_data_ter(int r, char *line, t_data *data, t_gc *gc)
{
	if (r == 5)
	{
		if (data->c != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->c = ft_get_file(line, data, gc);
	}
	if (r == 6)
	{
		if (data->f != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->f = ft_get_file(line, data, gc);
	}
	return (0);
}

int	ft_process_data_bis(int r, char *line, t_data *data, t_gc *gc)
{
	if (r == 3)
	{
		if (data->we != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->we = ft_get_file(line, data, gc);
	}
	if (r == 4)
	{
		if (data->ea != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->ea = ft_get_file(line, data, gc);
	}
	return (ft_process_data_ter(r, line, data, gc));
}

int	ft_process_data(int r, char *line, t_data *data, t_gc *gc)
{
	if (r == 1)
	{
		if (data->no != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->no = ft_get_file(line, data, gc);
	}
	if (r == 2)
	{
		if (data->so != NULL)
		{
			printf("Error\nDuplicated texture or color\n");
			return (1);
		}
		data->so = ft_get_file(line, data, gc);
	}
	return (ft_process_data_bis(r, line, data, gc));
}
