/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/07 17:52:21 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Si le projet autorise votre libft, vous devez copier ses sources et son Makefile
// associé dans un dossier libft contenu à la racine. Le Makefile de votre projet doit
// compiler la librairie à l’aide de son Makefile, puis compiler le projet.

int worldMap[MAPHEIGHT][MAPWIDTH]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  };

void	ft_init(t_mlx_data *pdata)
{
	pdata->connect = mlx_init();
	if (!pdata->connect)
		exit (1);
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3d");
	if (!pdata->win_ptr)
		ft_stop(pdata, 0, 1, NULL);
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata, 1, 1, NULL);
	//Acceder aux pixels d'une img. Utile I guess
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
		&pdata->len, &pdata->endian);
	pdata->px = 12;//22 useless
	pdata->py = 10;//12 useless

	pdata->posX = 12;
	pdata->posY = 10;
	pdata->dirX = -1;//Regard a gauche (arbitraire) sur le plan [-1, 1]
	pdata->dirY = 0;//regard ni en haut ni en bas mais au milieu sur le plan [1, -1]
	pdata->planeX = 0;//permet une ligne perpendiculaire
	pdata->planeY = 0.66;//et ps 1 pour que ce soit un peu plus realiste

}


//Place un pixel à la couleur voulue dans une image
void	ft_pixput(t_mlx_data *pdata, int x, int y, int color)
{
	int	disp;

	disp = (pdata->len * y) + ((pdata->bpp / 8) * x);
	*((unsigned int *)(disp + pdata->img_pixptr)) = color;
}

void	ver_line(t_mlx_data *pdata, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			ft_pixput(pdata, x, y, color);
		y++;
	}
}

int darken_color(int color)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	r = r / 2;
	g = g / 2;
	b = b / 2;

	return (r << 16) | (g << 8) | b;
}

// L’utilisation d’images de la minilibX est fortement recommandée. (Consignes)
//Bien separer les fichiers de la partie _bonus

//Dans la partie oblig : Vous devez afficher des textures différentes (vous avez le choix) selon si les murs
//sont face nord, sud, est, ouest.

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
	int		color;
	
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
		while (hit == 0)
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
		//les faces d'un mur n'ont pas la meme couleur
		if (side == 1)
			color = darken_color(color);

		//if (side == 1)
		//	color = color / 2;
		//if (side)
		//	color = (color & 0xFEFEFE) >> 1; 

		switch(worldMap[mapX][mapY])
      	{
        	case 1: color = 0xFF0000; break; // Rouge
			case 2: color = 0x00FF00; break; // Vert
			case 3: color = 0x0000FF; break; // Bleu
			case 4: color = 0xFFFF00; break; // Jaune
			default: color = 0xAAAAAA; break; // Gris clair
      	}
      	if (side == 1) {color = color / 2;}

		ver_line(pdata, x, drawStart, drawEnd, color); // ligne rouge verticale
	}
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
	
}

//int	ft_keyhook(int keysym, t_mlx_data *pdata)
//{
//	if (keysym == XK_Escape)
//	{
//		mlx_destroy_image(pdata->connect, pdata->img_ptr);
//		ft_stop(pdata, 1, 1, NULL);
//	}
//	// ft_show(pdata);
//	return (0);
//}

//A MODIFIER
//Les touches flèches du gauche et droite du clavier doivent permettre de faire
//une rotation de la caméra (regarder a gauche et a droite)
//◦ Les touches W, A, S et D doivent permettre de déplacer la caméra (déplacement
//du personnage)
int	ft_keyhook(int keysym, t_mlx_data *pdata)
{
	double moveSpeed = 0.2;
	double rotSpeed = 0.1;

	//printf("Touche pressée : %d\n", keysym);
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(pdata->connect, pdata->img_ptr);
		ft_stop(pdata, 1, 1, NULL);
	}

	// Z - Avancer
	if (keysym == XK_z)
	{
		if (worldMap[(int)(pdata->posX + pdata->dirX * moveSpeed)][(int)pdata->posY] == 0)
			pdata->posX += pdata->dirX * moveSpeed;
		if (worldMap[(int)pdata->posX][(int)(pdata->posY + pdata->dirY * moveSpeed)] == 0)
			pdata->posY += pdata->dirY * moveSpeed;
	}
	// S - Reculer
	if (keysym == XK_s)
	{
		if (worldMap[(int)(pdata->posX - pdata->dirX * moveSpeed)][(int)pdata->posY] == 0)
			pdata->posX -= pdata->dirX * moveSpeed;
		if (worldMap[(int)pdata->posX][(int)(pdata->posY - pdata->dirY * moveSpeed)] == 0)
			pdata->posY -= pdata->dirY * moveSpeed;
	}
	// D - Tourner à droite
	if (keysym == XK_d)
	{
		double oldDirX = pdata->dirX;
		pdata->dirX = pdata->dirX * cos(-rotSpeed) - pdata->dirY * sin(-rotSpeed);
		pdata->dirY = oldDirX * sin(-rotSpeed) + pdata->dirY * cos(-rotSpeed);
		double oldPlaneX = pdata->planeX;
		pdata->planeX = pdata->planeX * cos(-rotSpeed) - pdata->planeY * sin(-rotSpeed);
		pdata->planeY = oldPlaneX * sin(-rotSpeed) + pdata->planeY * cos(-rotSpeed);
	}
	// Q - Tourner à gauche
	if (keysym == XK_q)
	{
		double oldDirX = pdata->dirX;
		pdata->dirX = pdata->dirX * cos(rotSpeed) - pdata->dirY * sin(rotSpeed);
		pdata->dirY = oldDirX * sin(rotSpeed) + pdata->dirY * cos(rotSpeed);
		double oldPlaneX = pdata->planeX;
		pdata->planeX = pdata->planeX * cos(rotSpeed) - pdata->planeY * sin(rotSpeed);
		pdata->planeY = oldPlaneX * sin(rotSpeed) + pdata->planeY * cos(rotSpeed);
	}

	ft_show(pdata); // Rafraîchir l'image après déplacement
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx_data	data;


	
	ft_init(&data);
	ft_show(&data);
	mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
	mlx_key_hook(data.win_ptr, ft_keyhook, &data);
	mlx_loop(data.connect);
	return (0);	
}