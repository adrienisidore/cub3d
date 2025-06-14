/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 19:07:03 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Place un pixel à la couleur voulue dans une image
void	ft_pixput(t_mlx_data *pdata, int x, int y, int color)
{
	int	disp;

	disp = (pdata->len * y) + ((pdata->bpp / 8) * x);
	*((unsigned int *)(disp + pdata->img_pixptr)) = color;
}

static int	ft_pixget(t_texture txt, int x, int y)
{
	int	disp;
	int	rgb;

	disp = (txt.size_line * y) + ((txt.bpp / 8) * x);
	rgb = *((unsigned int *)(txt.addr + disp));
	return (rgb);
}

static void	ft_initex(t_mlx_data *pdata)
{
	t_texture	*txt;

	txt = pdata->current_txt;
	txt->utils.lineHeight = (int)(HEIGHT / pdata->dda.perpWallDist);
	if (txt->utils.lineHeight <= 0)
		txt->utils.lineHeight = 1;
	txt->utils.drawStart = -txt->utils.lineHeight / 2 + HEIGHT / 2;
	if (txt->utils.drawStart < 0)
		txt->utils.drawStart = 0;
	txt->utils.drawEnd = txt->utils.lineHeight / 2 + HEIGHT / 2;
	if (txt->utils.drawEnd >= HEIGHT)
		txt->utils.drawEnd = HEIGHT - 1;
	if (!pdata->dda.side)
		txt->utils.wallX = pdata->posY + pdata->dda.perpWallDist * pdata->dda.rayDirY;
	else
		txt->utils.wallX = pdata->posX + pdata->dda.perpWallDist * pdata->dda.rayDirX;
	txt->utils.wallX -= floor(txt->utils.wallX);
	txt->utils.tex_x = (int)(txt->utils.wallX * (double)txt->width);
	// Ajuster l'orientation de la texture
	if (!pdata->dda.side && pdata->dda.rayDirX > 0)
		txt->utils.tex_x = txt->width - txt->utils.tex_x - 1;
	if (pdata->dda.side && pdata->dda.rayDirY < 0)
		txt->utils.tex_x = txt->width - txt->utils.tex_x - 1;
	if (txt->utils.tex_x < 0)
		txt->utils.tex_x = 0;
	if (txt->utils.tex_x >= txt->width)
		txt->utils.tex_x = txt->width - 1;
	txt->utils.step = (double)txt->height / txt->utils.lineHeight;
	txt->utils.texPos = (txt->utils.drawStart - HEIGHT / 2 + txt->utils.lineHeight / 2) * txt->utils.step;
}

void	ft_texture(t_mlx_data *pdata, int x)
{
	int			y;
	double		shade;
	int			color;
	t_texture	*txt;

	txt = pdata->current_txt;
	ft_initex(pdata);
	y = txt->utils.drawStart - 1;
	while (++y <= txt->utils.drawEnd)
	{
		txt->utils.texPos += txt->utils.step;
		txt->utils.tex_y = (int)txt->utils.texPos;
		if (txt->utils.tex_y < 0)
			txt->utils.tex_y = 0;
		if (txt->utils.tex_y >= txt->height)
			txt->utils.tex_y = txt->height - 1;
		color = ft_pixget(*txt, txt->utils.tex_x, txt->utils.tex_y);
		// Ombre les murs perpendiculaires
		if (pdata->dda.side)
			shade = 0.6;
		else
			shade = 1.0;
		ft_pixput(pdata, x, y, ft_rgb(color, shade));
	}
}


