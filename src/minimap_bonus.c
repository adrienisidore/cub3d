/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:06:45 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:24:55 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
//"forbidden copy.cub" ne fonctionne pas, y compris quand je mets des " " ou que je retire l'espace
//trop de parametres
//ceil recast
static void ft_square(t_mlx_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
    {
		j = -1;
		while (++j < size)
            ft_pixput(data, x + j, y + i, color);
    }
}

static int	ft_mapwidth(char **map)
{
	int i;
	int	max;
	int	len;

	max = 0;
	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);//Utilisation du ft_strlen d'erika
		if (len > max)
			max = len;	
	}
	return (max);
}

static int	ft_mapheight(char **map)
{
	int	i = 0;
	while (map[i])
		i++;
	return (i);
}

void ft_minimap(t_mlx_data *data)
{
	int mapX, mapY, color;

	int mapwidth;
	int mapheight;

	mapwidth = ft_mapwidth(data->map);
	mapheight = ft_mapheight(data->map);
	// Adapte à la taille réelle de la map
	double cell_w = (double)MINIMAP_WIDTH / mapwidth;
	double cell_h = (double)MINIMAP_HEIGHT / mapheight;
	// double cell_w = 3.0;
	// double cell_h = 13.0;
	//Position de la minimap dans la fenetre
	int offset_x = WIDTH - MINIMAP_WIDTH - 10;
	int offset_y = 10;

	// --- Dessin des cases de la carte ---
	for (mapY = 0; mapY < mapheight; mapY++)
	{
		for (mapX = 0; mapX < (int)ft_strlen(data->map[mapY]); mapX++)
		{
			color = (data->map[mapY][mapX] == '0' || data->map[mapY][mapX] == 'N' || data->map[mapY][mapX] == 'S' || data->map[mapY][mapX] == 'E' || data->map[mapY][mapX] == 'W') ?  0xFFFFFF : 0x000000;
			ft_square(data,
				offset_x + (int)(mapX * cell_w),
				offset_y + (int)(mapY * cell_h),
				(int)cell_w,
				color);
		}
	}

	// --- Dessin du joueur ---
	double player_map_x = data->posx * cell_w;
	double player_map_y = data->posy * cell_h;

	int px = offset_x + (int)player_map_x;
	int py = offset_y + (int)player_map_y;
	ft_square(data, px, py, 3, 0x00FF00);

	// --- Ligne de vision ---
	//Faire partir le rayon du milieu
	double ray_x = data->posx;
	double ray_y = data->posy;
	double step = 0.05;

	while (1)
	{
		int map_check_x = (int)(ray_x);
		int map_check_y = (int)(ray_y);

		if (map_check_x < 0 || map_check_x >= mapwidth ||
			map_check_y < 0 || map_check_y >= mapheight)
			break;
		if (data->map[map_check_y][map_check_x] == '1')
			break;

		int draw_x = offset_x + (int)(ray_x * cell_w);
		int draw_y = offset_y + (int)(ray_y * cell_h);

		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			ft_pixput(data, draw_x, draw_y, 0x0000FF);

		ray_x += data->dirx * step;
		ray_y += data->diry * step;
	}
}