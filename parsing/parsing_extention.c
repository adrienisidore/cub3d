/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extention.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:13:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/06/03 17:20:55 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_xpm_extention(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i < 5)
		return (1);
	if (s[i - 1] != 'm')
		return (1);
	if (s[i - 2] != 'p')
		return (1);
	if (s[i - 3] != 'x')
		return (1);
	if (s[i - 4] != '.')
		return (1);
	return (0);
}

int	ft_check_extention(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i < 5)
		return (1);
	if (s[i - 1] != 'b')
		return (1);
	if (s[i - 2] != 'u')
		return (1);
	if (s[i - 3] != 'c')
		return (1);
	if (s[i - 4] != '.')
		return (1);
	return (0);
}

int	ft_is_o(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
		return (1);
	return (0);
}
