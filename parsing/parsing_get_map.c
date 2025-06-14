/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:33 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/14 19:19:32 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_reinit_fd(t_data *data, t_gc *gc)
{
	int	i;

	close(data->fd);
	data->fd = open(data->arg, O_RDONLY);
	if (data->fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	i = 0;
	while (i < data->start)
	{
		data->line = get_next_line(data->fd, data, gc);
		i++;
	}
	return (0);
}

int	ft_manage_line(int *f, t_data *data)
{
	int	n;

	n = ft_type_line(data->line);
	if (n == 2)
		return (1);
	if (n == 0)
		(*f) = 1;
	if (n == 1 && (*f) == 1)
	{
		printf("Error\nEmpty line in map\n");
		return (1);
	}
	else if (n == 1)
		(data->lg)++;
	return (0);
}

int	ft_arr_size(t_data *data, t_gc *gc)
{
	int	max;
	int	s;
	int	f;

	max = 0;
	data->start = data->lg;
	data->lg = 0;
	f = 0;
	while (data->line != NULL)
	{
		s = 0;
		while (data->line[s] && data->line[s] != '\n')
			s++;
		if (s > max)
			max = s;
		if (ft_manage_line(&f, data) == 1)
			return (1);
		data->line = get_next_line(data->fd, data, gc);
	}
	data->cl = max;
	if (ft_reinit_fd(data, gc) == 1)
		return (1);
	return (0);
}

void	ft_process_line(t_data *data, int k)
{
	int	i;

	i = 0;
	while (data->line[i] && data->line[i] != '\n')
	{
			data->map[k][i] = data->line[i];
		i++;
	}
	while (i < data->cl)
	{
		data->map[k][i] = ' ';
		i++;
	}
	data->map[k][i] = '\0';
}

void	ft_get_map(t_data *data, t_gc *gc)
{
	int	k;

	k = 0;
	data->map = gc_malloc(sizeof(char *) * (data->lg + 1), gc);
	while (data->line != NULL)
	{
		if (ft_type_line(data->line) == 0)
			break ;
		data->map[k] = gc_malloc(sizeof(char) * (data->cl + 1), gc);
		ft_process_line(data, k);
		k++;
		data->line = get_next_line(data->fd, data, gc);
	}
	data->map[k] = NULL;
	k = 0;
	while (data->map[k])
	{
		printf("%s\n", data->map[k]);
		k++;
	}
}
