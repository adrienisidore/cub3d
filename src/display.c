/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:00:57 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 18:04:52 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_ray_delta(t_mlx_data *pdata)
{
	//La coord. x du rayon est une fraction de pdata->planeX (voir schema). Idem pour y.
	pdata->dda.rayDirX = pdata->dirX + pdata->planeX * pdata->dda.cameraX;//Si je regarde au centre pdata->planeX = 0 donc rayDirX = pdata->dirX 
	pdata->dda.rayDirY = pdata->dirY + pdata->planeY * pdata->dda.cameraX;//Si je regarde au centre pdata->planeX=Y = 0 donc rayDirY = pdata->dirY

	//je crois que dda.rayDirX et pdata->dirX sont redondants
	if (!pdata->dda.rayDirX)
		pdata->dda.deltaDistX = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure verticale
	else
		pdata->dda.deltaDistX = fabs(1 / pdata->dda.rayDirX);
	if (!pdata->dda.rayDirY)
		pdata->dda.deltaDistY = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure horizontale
	else
		pdata->dda.deltaDistY = fabs(1 / pdata->dda.rayDirY);
}

static void	ft_init_step_side(t_mlx_data *pdata)
{
	//Initialisation pour connaitre le premier pas a effectuer
	//Si les coord. du joueur sont [22.4, 18.9] alors il est dans la case [22, 18]
	pdata->dda.mapX = (int)pdata->posX;
	pdata->dda.mapY = (int)pdata->posY;
	if (pdata->dda.rayDirX < 0)
	{
		pdata->dda.stepX = -1;
		pdata->dda.sideDistX = (pdata->posX - pdata->dda.mapX) * pdata->dda.deltaDistX;
	}
	else
	{
		pdata->dda.stepX = 1;
		pdata->dda.sideDistX = (pdata->dda.mapX + 1.0 - pdata->posX) * pdata->dda.deltaDistX;
	}
	if (pdata->dda.rayDirY < 0)
	{
		pdata->dda.stepY = -1;
		pdata->dda.sideDistY = (pdata->posY - pdata->dda.mapY) * pdata->dda.deltaDistY;
	}
	else
	{
		pdata->dda.stepY = 1;
		pdata->dda.sideDistY = (pdata->dda.mapY + 1.0 - pdata->posY) * pdata->dda.deltaDistY;
	}	
}

static void	ft_dda(t_mlx_data *pdata)
{
	pdata->dda.hit = 0;
	//Lancement de DDA
	while (!pdata->dda.hit)
	{
		if (pdata->dda.sideDistX < pdata->dda.sideDistY)
		{
			pdata->dda.sideDistX += pdata->dda.deltaDistX;
			pdata->dda.mapX += pdata->dda.stepX;
			pdata->dda.side = 0;
		}
		else
		{
			pdata->dda.sideDistY += pdata->dda.deltaDistY;
			pdata->dda.mapY += pdata->dda.stepY;
			pdata->dda.side = 1;
		}
		//Check si j'ai touche un mur
		if (worldMap[pdata->dda.mapY][pdata->dda.mapX] > '0')
			pdata->dda.hit = 1;
	}
}

//Faut il utiliser SDL pour + de fluidité et pour les sprites animés ?
void	ft_display(t_mlx_data *pdata, void (*fn)(t_mlx_data *))
{
	int		x;

	ft_floorceil(pdata);
	x = -1;
	while (++x < WIDTH)
	{
		//On parcourt toute la surface de l'image (chaque ligne verticale)
		pdata->dda.cameraX = 2 * x / (double)WIDTH - 1;//normalisation de chaque pixels en coord. [-1, 1]
		ft_init_ray_delta(pdata);
		ft_init_step_side(pdata);
		ft_dda(pdata);
		ft_choose_texture(pdata);
		//Maintenant qu'on connait la dstance entre le joueur et la prochaine bordure verticale
		//d'un mur (sideDistX) et entre le joueur et la prochaine bordure horizontale d'un mur (sideDistY)
		//je definie la distance perpWallDist comme la plus petite des 2, en prenant en compte le fait que
		//sideDist contient la distance jusqu'à l’intérieur du mur, or nous voulons la distance jusqu’à
		//la surface du mur, donc on enlève un delta
		if(!pdata->dda.side)
			pdata->dda.perpWallDist = pdata->dda.sideDistX - pdata->dda.deltaDistX;
		else
			pdata->dda.perpWallDist = pdata->dda.sideDistY - pdata->dda.deltaDistY;

		ft_texture(pdata, x);
	}
	if (pdata->smap && fn)
		fn(pdata);
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
}
