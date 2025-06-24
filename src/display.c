/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:00:57 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:28:51 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_ray_delta(t_mlx_data *pdata)
{
	//La coord. x du rayon est une fraction de pdata->planex (voir schema). Idem pour y.
	pdata->dda.raydirx = pdata->dirx + pdata->planex * pdata->dda.camerax;//Si je regarde au centre pdata->planex = 0 donc raydirx = pdata->dirX
	pdata->dda.raydiry = pdata->diry + pdata->planey * pdata->dda.camerax;//Si je regarde au centre pdata->planex=Y = 0 donc raydiry = pdata->dirY
	//je crois que dda.raydirx et pdata->dirX sont redondants
	if (!pdata->dda.raydirx)
		pdata->dda.deltadistx = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure verticale
	else
		pdata->dda.deltadistx = fabs(1 / pdata->dda.raydirx);
	if (!pdata->dda.raydiry)
		pdata->dda.deltadisty = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure horizontale
	else
		pdata->dda.deltadisty = fabs(1 / pdata->dda.raydiry);
}

static void	ft_init_step_side(t_mlx_data *pdata)
{
	//Initialisation pour connaitre le premier pas a effectuer
	//Si les coord. du joueur sont [22.4, 18.9] alors il est dans la case [22, 18]
	pdata->dda.mapX = (int)pdata->posx;
	pdata->dda.mapY = (int)pdata->posy;
	if (pdata->dda.raydirx < 0)
	{
		pdata->dda.stepx = -1;
		pdata->dda.sidedistx = (pdata->posx - pdata->dda.mapX) * pdata->dda.deltadistx;
	}
	else
	{
		pdata->dda.stepx = 1;
		pdata->dda.sidedistx = (pdata->dda.mapX + 1.0 - pdata->posx) * pdata->dda.deltadistx;
	}
	if (pdata->dda.raydiry < 0)
	{
		pdata->dda.stepy = -1;
		pdata->dda.sidedisty = (pdata->posy - pdata->dda.mapY) * pdata->dda.deltadisty;
	}
	else
	{
		pdata->dda.stepy = 1;
		pdata->dda.sidedisty = (pdata->dda.mapY + 1.0 - pdata->posy) * pdata->dda.deltadisty;
	}
}

static void	ft_dda(t_mlx_data *pdata)
{
	pdata->dda.hit = 0;
	//Lancement de DDA
	while (!pdata->dda.hit)
	{
		if (pdata->dda.sidedistx < pdata->dda.sidedisty)
		{
			pdata->dda.sidedistx += pdata->dda.deltadistx;
			pdata->dda.mapX += pdata->dda.stepx;
			pdata->dda.side = 0;
		}
		else
		{
			pdata->dda.sidedisty += pdata->dda.deltadisty;
			pdata->dda.mapY += pdata->dda.stepy;
			pdata->dda.side = 1;
		}
		if (pdata->map[pdata->dda.mapY][pdata->dda.mapX] == '1')
			pdata->dda.hit = 1;
	}
}

void	ft_display(t_mlx_data *pdata, void (*fn)(t_mlx_data *))
{
	int		x;
	double	epsilon;

	ft_floorceil(pdata);
	epsilon = 0.001;
	x = -1;
	while (++x < WIDTH)
	{
		//On parcourt toute la surface de l'image (chaque ligne verticale)
		pdata->dda.camerax = 2 * x / (double)WIDTH - 1;//normalisation de chaque pixels en coord. [-1, 1]
		ft_init_ray_delta(pdata);
		ft_init_step_side(pdata);
		ft_dda(pdata);
		ft_choose_texture(pdata);
		//Maintenant qu'on connait la dstance entre le joueur et la prochaine bordure verticale
		//d'un mur (sidedistx) et entre le joueur et la prochaine bordure horizontale d'un mur (sidedisty)
		//je definie la distance perpwalldist comme la plus petite des 2, en prenant en compte le fait que
		//sideDist contient la distance jusqu'à l’intérieur du mur, or nous voulons la distance jusqu’à
		//la surface du mur, donc on enlève un delta
		if(!pdata->dda.side)
			pdata->dda.perpwalldist = pdata->dda.sidedistx - pdata->dda.deltadistx;
		else
			pdata->dda.perpwalldist = pdata->dda.sidedisty - pdata->dda.deltadisty;
		if (pdata->dda.perpwalldist < epsilon)
			pdata->dda.perpwalldist = epsilon;
		ft_texture(pdata, x);
	}
	if (pdata->smap && fn)
		fn(pdata);
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
	mlx_do_sync(pdata->connect);/////////////////////////////////////////////////////////////////
}
