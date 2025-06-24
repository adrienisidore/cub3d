/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:03:15 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_rgb(int color, double shade)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
	return (color = (r << 16) | (g << 8) | b);
}

void	ft_choose_texture(t_mlx_data *pdata)
{
	if (pdata->dda.side == 0)
	{
		if (pdata->dda.raydirx > 0)
			pdata->current_txt = &pdata->txt_west;
		else
			pdata->current_txt = &pdata->txt_east;
	}
	else
	{
		if (pdata->dda.raydiry > 0)
			pdata->current_txt = &pdata->txt_north;
		else
			pdata->current_txt = &pdata->txt_south;
	}
}

static int	ft_rgb_convert(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
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
			ft_pixput(pdata, x_fill++, y_fill, ft_rgb_convert(pdata->crr, pdata->cgg, pdata->cbb));
		y_fill++;
	}
	while (y_fill < HEIGHT)
	{
		x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, y_fill, ft_rgb_convert(pdata->frr, pdata->fgg, pdata->fbb));
		y_fill++;
	}
}
