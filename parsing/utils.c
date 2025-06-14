/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/02 19:26:14 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && n)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*ft_strdup_bis(char *s, t_gc *gc)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = gc_malloc(sizeof(char) * (ft_strlen(s) + 1), gc);
	if (str == NULL)
		return (NULL);
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_lose_space(char *s, int *i)
{
	while (s && s[*i] && ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32))
		(*i) = (*i) + 1;
}

int	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_type_line(char *line)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1'
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W' || (line[i] >= 9 && line[i] <= 13)))
		{
			printf("Error\nInvalid line\n");
			return (2);
		}
		if (line[i] == '1' || line[i] == '0')
			f = 1;
		i++;
	}
	return (f);
}
