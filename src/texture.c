/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:19:47 by aisidore         ###   ########.fr       */
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
	int		disp;
	int		rgb;

	disp = (txt.size_line * y) + ((txt.bpp / 8) * x);
	rgb = *((unsigned int *)(txt.addr + disp));
	return (rgb);
}

static void	ft_initex(t_mlx_data *pdata)
{
	t_texture	*txt;

	txt = pdata->current_txt;
	txt->utils.lineheight = (int)(HEIGHT / pdata->dda.perpwalldist);
	if (txt->utils.lineheight <= 0)
		txt->utils.lineheight = 1;
	txt->utils.drawstart = -txt->utils.lineheight / 2 + HEIGHT / 2;
	if (txt->utils.drawstart < 0)
		txt->utils.drawstart = 0;
	txt->utils.drawend = txt->utils.lineheight / 2 + HEIGHT / 2;
	if (txt->utils.drawend >= HEIGHT)
		txt->utils.drawend = HEIGHT - 1;
	if (!pdata->dda.side)
		txt->utils.wallx = pdata->posy + pdata->dda.perpwalldist * pdata->dda.raydiry;
	else
		txt->utils.wallx = pdata->posx + pdata->dda.perpwalldist * pdata->dda.raydirx;
	txt->utils.wallx -= floor(txt->utils.wallx);
	txt->utils.tex_x = (int)(txt->utils.wallx * (double)txt->width);
	// Ajuster l'orientation de la texture
	if (!pdata->dda.side && pdata->dda.raydirx > 0)
		txt->utils.tex_x = txt->width - txt->utils.tex_x - 1;
	if (pdata->dda.side && pdata->dda.raydiry < 0)
		txt->utils.tex_x = txt->width - txt->utils.tex_x - 1;
	if (txt->utils.tex_x < 0)
		txt->utils.tex_x = 0;
	if (txt->utils.tex_x >= txt->width)
		txt->utils.tex_x = txt->width - 1;
	txt->utils.step = (double)txt->height / txt->utils.lineheight;
	txt->utils.texPos = (txt->utils.drawstart - HEIGHT / 2 + txt->utils.lineheight / 2) * txt->utils.step;
}

void	ft_texture(t_mlx_data *pdata, int x)
{
	int			y;
	double		shade;
	int			color;
	t_texture	*txt;

	txt = pdata->current_txt;
	ft_initex(pdata);
	y = txt->utils.drawstart - 1;
	while (++y <= txt->utils.drawend)
	{
		txt->utils.texPos += txt->utils.step;
		txt->utils.tex_y = (int)txt->utils.texPos;
		if (txt->utils.tex_y < 0)
			txt->utils.tex_y = 0;
		if (txt->utils.tex_y >= txt->height)
			txt->utils.tex_y = txt->height - 1;
		color = ft_pixget(*txt, txt->utils.tex_x, txt->utils.tex_y);
		if (pdata->dda.side)
			shade = 0.6;
		else
			shade = 1.0;
		ft_pixput(pdata, x, y, ft_rgb(color, shade));
	}
}
