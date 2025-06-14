/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 18:04:21 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(char *s, t_gc *gc)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = gc_malloc(sizeof(char) * (ft_strlen(s) + 1), gc);
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*read_and_stock(t_data *data, char *line, int *n, t_gc *gc)
{
	int			i;
	int			f;
	char		*temp;
	char		*tmp;

	i = -1;
	while (i == -1 && *n == BUFFER_SIZE && ft_strchr(line, '\n') == -1)
	{
		*n = read(data->fd, data->buffer, BUFFER_SIZE);
		if (*n == -1)
			return (NULL);
		i = ft_strchr(data->buffer, '\n');
		f = (*n);
		if (*n != 0)
		{
			if (i != -1)
				f = i + 1;
			tmp = ft_substr(data->buffer, 0, f, gc);
			temp = ft_strdup(line, gc);
			gc_free(line, gc);
			line = ft_strjoin(temp, tmp, gc);
			(gc_free(temp, gc), gc_free(tmp, gc));
		}
	}
	return (line);
}

void	clean_stash_buffer(t_data *data, int *n, t_gc *gc)
{
	int		i;
	int		j;
	char	*tp;

	i = ft_strchr(data->buffer, '\n');
	j = ft_strchr(data->stash, '\n');
	if (j != -1)
	{
		tp = ft_substr(data->stash, j + 1, ft_strlen(data->stash) - j - 1, gc);
		gc_free(data->stash, gc);
		data->stash = ft_strdup(tp, gc);
		(gc_free(tp, gc), gc_free(data->buffer, gc));
	}
	else
	{
		if (data->stash != NULL)
			gc_free(data->stash, gc);
		data->stash = NULL;
		if (i != -1)
			data->stash = ft_substr(data->buffer, i + 1, *n - i - 1, gc);
		if (*n == 0 && data->stash && (data->stash[0] == '\0'
				|| data->stash[0] == '\n'))
			gc_free(data->stash, gc);
		(gc_free(data->buffer, gc));
	}
}

char	*get_next_line(int fd, t_data *data, t_gc *gc)
{
	char	*line;
	int		n;

	line = NULL;
	if (fd == -1 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	n = BUFFER_SIZE;
	data->buffer = gc_calloc(BUFFER_SIZE + 1, sizeof(char), gc);
	if (data->stash != NULL && data->stash[0] != '\0'
		&& ft_strchr(data->stash, '\n') == -1)
	{
		line = ft_strdup(data->stash, gc);
	}
	else if (data->stash != NULL && data->stash[0] != '\0'
		&& ft_strchr(data->stash, '\n') != -1)
	{
		line = ft_substr(data->stash, 0, ft_strchr(data->stash, '\n') + 1, gc);
	}
	line = read_and_stock(data, line, &n, gc);
	clean_stash_buffer(data, &n, gc);
	return (line);
}
