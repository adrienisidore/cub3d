/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 19:07:16 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_rgb(int color, double shade)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
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

void	ft_floorceil(t_mlx_data *pdata)
{
	int	y_fill;
	int	x_fill;

	y_fill = 0;
	while (y_fill < HEIGHT / 2)
	{
		x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, y_fill, 0xAAAAAA);
		y_fill++;
	}
	while (y_fill < HEIGHT)
	{
		x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, y_fill, 0x333333);
		y_fill++;
	}
}
