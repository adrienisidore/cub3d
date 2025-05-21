/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:00:57 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/20 18:04:44 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Faut il utiliser SDL pour + de fluidité et pour les sprites animés ?
void	ft_show(t_mlx_data *pdata)
{
	int		x;

	//Image
	// int		lineHeight;//hauteur du mur
	// int		drawStart;//le pixel en haut de la ligne du mur
	// int		drawEnd;//le pixel en bas de la ligne du mur

	ft_draw_floorceil(pdata);

	x = -1;
	//color = 0xFF0000;
	while (++x < WIDTH)
	{
		//On parcourt toute la surface de l'image (chaque ligne verticale)
		pdata->dda.cameraX = 2 * x / (double)WIDTH - 1;//normalisation de chaque pixels en coord. [-1, 1]
		//La coord. x du rayon est une fraction de pdata->planeX (voir schema). Idem pour y.
		pdata->dda.rayDirX = pdata->dirX + pdata->planeX * pdata->dda.cameraX;//Si je regarde au centre pdata->planeX = 0 donc rayDirX = pdata->dirX 
		pdata->dda.rayDirY = pdata->dirY + pdata->planeY * pdata->dda.cameraX;//Si je regarde au centre pdata->planeX=Y = 0 donc rayDirY = pdata->dirY
		//Si les coord. du joueur sont [22.4, 18.9] alors il est dans la case [22, 18]
		pdata->dda.mapX = (int)pdata->posX;
		pdata->dda.mapY = (int)pdata->posY;

		if (!pdata->dda.rayDirX)
			pdata->dda.deltaDistX = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure verticale
		else
			pdata->dda.deltaDistX = fabs(1 / pdata->dda.rayDirX);
		if (!pdata->dda.rayDirY)
			pdata->dda.deltaDistY = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure horizontale
		else
			pdata->dda.deltaDistY = fabs(1 / pdata->dda.rayDirY);

		pdata->dda.hit = 0;

		//Initialisation pour connaitre le premier pas a effectuer
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
			// Sécurité bord de carte, a priori ça s'active jamais puisque la map est entourée de mur
			//if (mapX < 0 || mapX >= MAPWIDTH || mapY < 0 || mapY >= MAPHEIGHT)
			//	break;
			//Check si j'ai touche un mur
			if (worldMap[pdata->dda.mapY][pdata->dda.mapX] > 0)
				pdata->dda.hit = 1;
		}

		//Maintenant qu'on connait la dstance entre le joueur et la prochaine bordure verticale
		//d'un mur (sideDistX) et entre le joueur et la prochaine bordure horizontale d'un mur (sideDistY)
		//je definie la distance perpWallDist comme la plus petite des 2, en prenant en compte le fait que
		//sideDistX contient la distance jusqu'à l’intérieur du mur, or nous voulons la distance jusqu’à
		//la surface du mur, donc on enlève un delta
		if(!pdata->dda.side)
			pdata->dda.perpWallDist = pdata->dda.sideDistX - pdata->dda.deltaDistX;
		else
			pdata->dda.perpWallDist = pdata->dda.sideDistY - pdata->dda.deltaDistY;
		// lineHeight = (int)(HEIGHT / perpWallDist);
		// drawStart = -lineHeight / 2 + HEIGHT / 2;
		// drawEnd = lineHeight / 2 + HEIGHT / 2;
		// if(drawStart < 0)
		// 	drawStart = 0;
    	// if(drawEnd >= HEIGHT)
	  	// 	drawEnd = HEIGHT - 1;
		ft_draw(pdata, x, pdata->dda.perpWallDist, pdata->dda.side, pdata->dda.rayDirX, pdata->dda.rayDirY);
	}
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
	
}
