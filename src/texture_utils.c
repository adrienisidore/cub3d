/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 17:04:21 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_rgb(int color, double shade)
{
	unsigned char r = ((color >> 16) & 0xFF) * shade;
	unsigned char g = ((color >> 8) & 0xFF) * shade;
	unsigned char b = (color & 0xFF) * shade;
	return (color = (r << 16) | (g << 8) | b);
}

void	ft_choose_texture(t_mlx_data *pdata)
{
	if (pdata->dda.side == 0)
	{
		if (pdata->dda.rayDirX > 0)
			pdata->current_txt = &pdata->txt_west;
		else
			pdata->current_txt = &pdata->txt_east;
	}
	else
	{
		if (pdata->dda.rayDirY > 0)
			pdata->current_txt = &pdata->txt_north;
		else
			pdata->current_txt = &pdata->txt_south;
	}
}
