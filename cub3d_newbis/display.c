/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:00:57 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:34:54 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



//Faut il utiliser SDL pour + de fluidité et pour les sprites animés ?
void	ft_show(t_mlx_data *pdata)
{
	int		x;
	
	double	cameraX;//normaliser chaque pixel en coord. [-1;1]
	double	rayDirX;//coord. X du regard du joueur
	double	rayDirY;//coord. Y du regard du joueur
	
	int		mapX;//coord. X de la case du joueur
	int		mapY;//coord. Y de la case du joueur
	//Pour demarrer DDA on devra savoir quel cote de la case du joeur le rayon touche en premier
	double	sideDistX;//distance jusqu'a la prochaine bordure vertical
	double	sideDistY;//distance jusqu'a la prochaine bordure horizontale
	double	deltaDistX;//distance (statique) a parcourir pour toucher la prochaine bordure verticale
	double	deltaDistY;//distance (statique) a parcourir pour toucher la prochaine bordure horizontale

	//DDA
	int		stepX;//Si +1 on passe a la bordure verticale suivante a droit (resp a gauche pour -1)
	int		stepY;//Si +1 on passe a la bordure horizontale suivante en bas  (resp en haut pour -1)
	int		hit;// ==1 j'ai touche un mur
	int		side;//==0 j'ai touche une bordure horizontale (resp ==1 verticale)
	double	perpWallDist;//distance (projetee/perpendiculaire a l'ecran) entre le joueur et le mur,
	//pour eviter que les murs semblent incurves : perpWallDist = Euclidean / |rayDir|

	//Image
	int		lineHeight;//hauteur du mur
	int		drawStart;//le pixel en haut de la ligne du mur
	int		drawEnd;//le pixel en bas de la ligne du mur

	ft_draw_floorceil(pdata);

	x = -1;
	//color = 0xFF0000;
	while (++x < WIDTH)
	{
		//On parcourt toute la surface de l'image (chaque ligne verticale)
		cameraX = 2 * x / (double)WIDTH - 1;//normalisation de chaque pixels en coord. [-1, 1]
		//La coord. x du rayon est une fraction de pdata->planeX (voir schema). Idem pour y.
		rayDirX = pdata->dirX + pdata->planeX * cameraX;//Si je regarde au centre pdata->planeX = 0 donc rayDirX = pdata->dirX 
		rayDirY = pdata->dirY + pdata->planeY * cameraX;//Si je regarde au centre pdata->planeX=Y = 0 donc rayDirY = pdata->dirY
		//Si les coord. du joueur sont [22.4, 18.9] alors il est dans la case [22, 18]
		mapX = (int)pdata->posX;
		mapY = (int)pdata->posY;

		if (rayDirX == 0)
			deltaDistX = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure verticale
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;//Si le joueur ne regarde ni a gauche ni a droite il ne touchera jamais de bordure horizontale
		else
			deltaDistY = fabs(1 / rayDirY);

		hit = 0;

		//Initialisation pour connaitre le premier pas a effectuer
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (pdata->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - pdata->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (pdata->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - pdata->posY) * deltaDistY;
		}

		//Lancement de DDA
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Sécurité bord de carte, a priori ça s'active jamais puisque la map est entourée de mur
			//if (mapX < 0 || mapX >= MAPWIDTH || mapY < 0 || mapY >= MAPHEIGHT)
			//	break;
			//Check si j'ai touche un mur
			if (worldMap[mapY][mapX] > 0)
				hit = 1;
		}

		//Maintenant qu'on connait la dstance entre le joueur et la prochaine bordure verticale
		//d'un mur (sideDistX) et entre le joueur et la prochaine bordure horizontale d'un mur (sideDistY)
		//je definie la distance perpWallDist comme la plus petite des 2, en prenant en compte le fait que
		//sideDistX contient la distance jusqu'à l’intérieur du mur, or nous voulons la distance jusqu’à
		//la surface du mur, donc on enlève un delta
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		lineHeight = (int)(HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
    	if(drawEnd >= HEIGHT)
	  		drawEnd = HEIGHT - 1;
		ft_draw(pdata, x, perpWallDist, side, rayDirX, rayDirY);
	}
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
	
}
