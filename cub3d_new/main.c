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

int worldMap[MAPWIDTH][MAPHEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	pdata->px = 300;
	pdata->py = 300;
}

int	ft_keyhook(int keysym, t_mlx_data *pdata)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(pdata->connect, pdata->img_ptr);
		ft_stop(pdata, 1, 1, NULL);
	}
	// ft_show(pdata);
	return (0);
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

void	ft_show(t_mlx_data *pdata)
{
	int		x;

	//position joueur
	double posX;
	double posY;
	//direction du regard sur le plan [-1, 1][-1, 1]
	double dirX;
	double dirY;
	//surface sur laquelle les rayons vont se projeter (ligne perpendiculaire au regard dirX, dirY)
	double planeX;
	double planeY;
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	//Initialisation
	posX = 22;
	posY = 12;
	dirX = -1;//Regard a gauche (arbitraire) sur le plan [-1, 1]
	dirY = 0;//regard ni en haut ni en bas mais au milieu sur le plan [1, -1]
	planeX = 0;//permet une ligne perpendiculaire
	planeY = 0.66;//et ps 1 pour que ce soit un peu plus realiste
	
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
	

	x = -1;
	color = 0xFF0000;
	while (++x < WIDTH)
	{
		//On parcourt toute la surface de l'image (chaque ligne verticale)
		cameraX = 2 * x / (double)WIDTH - 1;//normalisation de chaque pixels en coord. [-1, 1]
		//La coord. x du rayon est une fraction de planeX (voir schema). Idem pour y.
		rayDirX = dirX + planeX * cameraX;//Si je regarde au centre planeX = 0 donc rayDirX = dirX 
		rayDirY = dirY + planeY * cameraX;//Si je regarde au centre planeX=Y = 0 donc rayDirY = dirY
		//Si les coord. du joueur sont [22.4, 18.9] alors il est dans la case [22, 18]
		mapX = (int)posX;
		mapY = (int)posY;

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
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
			//Check si j'ai touche un mur
			if (worldMap[mapX][mapY] > 0)
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
			color = color / 2;
		ver_line(pdata, x, drawStart, drawEnd, color); // ligne rouge verticale
	}
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
	
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