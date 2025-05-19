/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:46:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:35:01 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Place un pixel à la couleur voulue dans une image
static void	ft_pixput(t_mlx_data *pdata, int x, int y, int color)
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

//transformer pixget en qqchose qui ressemble + a pixput
// static int		ft_pixget(t_texture txt, int x, int y)
// {
// 		unsigned char	color_b;
// 		unsigned char	color_g;
// 		unsigned char	color_r;
// 		int				rgb;

// 		color_b = txt.addr[y * txt.size_line + x * (txt.bpp / 8)];
// 		color_g = txt.addr[y * txt.size_line + x * (txt.bpp / 8) + 1];
// 		color_r = txt.addr[y * txt.size_line + x * (txt.bpp / 8) + 2];
// 		rgb = color_r;
// 		rgb = (rgb << 8) + color_g;
// 		rgb = (rgb << 8) + color_b;
// 		return (rgb);
// }

void	ft_draw_floorceil(t_mlx_data *pdata)
{
	// Dessine plafond (gris clair) et sol (gris foncé)
	int yy = 0;
	while (yy < HEIGHT / 2)
	{
		int x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, yy, 0xAAAAAA); // plafond
		yy++;
	}
	while (yy < HEIGHT)
	{
		int x_fill = 0;
		while (x_fill < WIDTH)
			ft_pixput(pdata, x_fill++, yy, 0x333333); // sol
		yy++;
	}
}

static void	ft_initdraw(t_mlx_data *pdata, double perpWallDist, int side, double rayDirX, double rayDirY)
{
	pdata->txt.utils.lineHeight = (int)(HEIGHT / perpWallDist);
	if (pdata->txt.utils.lineHeight <= 0)
		pdata->txt.utils.lineHeight = 1;
	pdata->txt.utils.drawStart = -pdata->txt.utils.lineHeight / 2 + HEIGHT / 2;
	if (pdata->txt.utils.drawStart < 0)
		pdata->txt.utils.drawStart = 0;
	pdata->txt.utils.drawEnd = pdata->txt.utils.lineHeight / 2 + HEIGHT / 2;
	if (pdata->txt.utils.drawEnd >= HEIGHT)
		pdata->txt.utils.drawEnd = HEIGHT - 1;
	if (side == 0)
		pdata->txt.utils.wallX = pdata->posY + perpWallDist * rayDirY;
	else
		pdata->txt.utils.wallX = pdata->posX + perpWallDist * rayDirX;
	pdata->txt.utils.wallX -= floor(pdata->txt.utils.wallX);
	pdata->txt.utils.tex_x = (int)(pdata->txt.utils.wallX * (double)pdata->txt.width);
	if (side == 0 && rayDirX > 0)
		pdata->txt.utils.tex_x = pdata->txt.width - pdata->txt.utils.tex_x - 1;
	if (side == 1 && rayDirY < 0)
		pdata->txt.utils.tex_x = pdata->txt.width - pdata->txt.utils.tex_x - 1;
	if (pdata->txt.utils.tex_x < 0)
		pdata->txt.utils.tex_x = 0;
	if (pdata->txt.utils.tex_x >= pdata->txt.width)
		pdata->txt.utils.tex_x = pdata->txt.width - 1;
}

void ft_draw(t_mlx_data *pdata, int x, double perpWallDist, int side,
              		double rayDirX, double rayDirY)
{
	double step;
	double texPos;
	int	y;
	int	color;
	
	ft_initdraw(pdata, perpWallDist, side, rayDirX, rayDirY);
	step = (double)pdata->txt.height / pdata->txt.utils.lineHeight;
	texPos = (pdata->txt.utils.drawStart - HEIGHT / 2 + pdata->txt.utils.lineHeight / 2) * step;
	y = pdata->txt.utils.drawStart - 1;
	while (++y <= pdata->txt.utils.drawEnd)
	{
		pdata->txt.utils.tex_y = (int)texPos;
		texPos += step;
		if (pdata->txt.utils.tex_y < 0)
			pdata->txt.utils.tex_y = 0;
		if (pdata->txt.utils.tex_y >= pdata->txt.height)
			pdata->txt.utils.tex_y = pdata->txt.height - 1;
		color = ft_pixget(pdata->txt, pdata->txt.utils.tex_x, pdata->txt.utils.tex_y);
		ft_pixput(pdata, x, y, color);
	}
}


// static int darken_color(int color)
// {
// 	int r = (color >> 16) & 0xFF;
// 	int g = (color >> 8) & 0xFF;
// 	int b = color & 0xFF;

// 	r = r / 2;
// 	g = g / 2;
// 	b = b / 2;

// 	return (r << 16) | (g << 8) | b;
// }

// L’utilisation d’images de la minilibX est fortement recommandée. (Consignes)
//Bien separer les fichiers de la partie _bonus

//Dans la partie oblig : Vous devez afficher des txts différentes (vous avez le choix) selon si les murs
//sont face nord, sud, est, ouest.


