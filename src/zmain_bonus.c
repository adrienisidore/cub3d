/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zmain_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/23 11:28:36 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//Pour le bonus : VERIFIER QUE C'EST BIEN CE QU'ON ATTEND DE NOUS
int	mouse_move_hook(int x, int y, t_mlx_data *pdata)
{
	static int	last_x = -1;
	double		rotSpeed;
	(void)y;

	if (last_x == -1)
		last_x = x;

	int delta_x = x - last_x;
	last_x = x;

	rotSpeed = 0.003 * delta_x; // Ajuste ce facteur à ta sensibilité souhaitée

	double oldDirX = pdata->dirX;
	pdata->dirX = pdata->dirX * cos(-rotSpeed) - pdata->dirY * sin(-rotSpeed);
	pdata->dirY = oldDirX * sin(-rotSpeed) + pdata->dirY * cos(-rotSpeed);

	double oldPlaneX = pdata->planeX;
	pdata->planeX = pdata->planeX * cos(-rotSpeed) - pdata->planeY * sin(-rotSpeed);
	pdata->planeY = oldPlaneX * sin(-rotSpeed) + pdata->planeY * cos(-rotSpeed);

	ft_display_bonus(pdata); // Rafraîchir l'affichage

	return (0);
}

int ft_keypress_bonus(int keycode, t_mlx_data *data)
{
	if (keycode == XK_w)
		data->move_forward = 1;
	else if (keycode == XK_s)
		data->move_backward = 1;
	else if (keycode == XK_a)
		data->move_left = 1;
	else if (keycode == XK_d)
		data->move_right = 1;
	else if (keycode == XK_Left)
		data->rotate_left = 1;
	else if (keycode == XK_Right)
		data->rotate_right = 1;
    else if (keycode == XK_m)
    {
        data->smap = !data->smap;//changer pour pdata PARTOUT
        //printf("smap = %d\n", data->smap);
    }
	else if (keycode == XK_Escape)
		ft_stop(data);
	return (0);
}



static void	ft_pixput(t_mlx_data *pdata, int x, int y, int color)
{
	int	disp;

	disp = (pdata->len * y) + ((pdata->bpp / 8) * x);
	*((unsigned int *)(disp + pdata->img_pixptr)) = color;
}


void draw_square(t_mlx_data *data, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            ft_pixput(data, x + j, y + i, color);
            //mlx_pixel_put(data->mlx, data->win, x + j, y + i, color);
        }
    }
}


//AJOUTER LE/LES LASERS
void draw_minimap(t_mlx_data *data)
{
    int mapX, mapY;
    int color;

    double cell_w = (double)MINIMAP_WIDTH / MAPWIDTH;
    double cell_h = (double)MINIMAP_HEIGHT / MAPHEIGHT;

    int offset_x = WIDTH - MINIMAP_WIDTH - 10;
    int offset_y = 10;

    // --- Dessin des cases de la carte ---
    for (mapY = 0; mapY < MAPHEIGHT; mapY++)
    {
        for (mapX = 0; mapX < MAPWIDTH; mapX++)
        {
            if (worldMap[mapY][mapX] == 0)
                color = 0x000000;
            else if (worldMap[mapY][mapX] == 1)
                color = 0x888888;
            else if (worldMap[mapY][mapX] == 2)
                color = 0x0000FF;
            else if (worldMap[mapY][mapX] == 3)
                color = 0xFF0000;
            else
                color = 0xFFFFFF;

            draw_square(data,
                        offset_x + (int)((MAPWIDTH - 1 - mapX) * cell_w),
                        offset_y + (int)(mapY * cell_h),
                        (int)cell_w,
                        color);
        }
    }

    // --- Dessin du joueur ---
    double player_map_x = (MAPWIDTH - 1 - data->posX) * cell_w;
    double player_map_y = data->posY * cell_h;

    int px = offset_x + (int)player_map_x;
    int py = offset_y + (int)player_map_y;
    draw_square(data, px, py, 3, 0x00FF00);

    // --- Ligne de vision jusqu'au mur ---
    double ray_x = data->posX;
    double ray_y = data->posY;
    double step = 0.05;

        while (1)
    {
        // On cast les coordonnées "rayon" vers des indices entiers map
        int map_check_x = (int)(ray_x + 0.001); // légère compensation pour éviter de rater les coins
        int map_check_y = (int)(ray_y + 0.001);

        // vérification bord de carte
        if (map_check_x < 0 || map_check_x >= MAPWIDTH ||
            map_check_y < 0 || map_check_y >= MAPHEIGHT)
            break;

        // arrêt si mur
        if (worldMap[map_check_y][map_check_x] > 0)
            break;

        int draw_x = offset_x + (int)((MAPWIDTH - 1 - ray_x) * cell_w);
        int draw_y = offset_y + (int)(ray_y * cell_h);

        if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
            ft_pixput(data, draw_x, draw_y, 0x0000FF);

        ray_x += data->dirX * step;
        ray_y += data->dirY * step;
    }

}



//mettre void plutot que ac av
int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx_data	data;

	ft_init(&data);
	ft_display_bonus(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress_bonus, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
    mlx_hook(data.win_ptr, 6, 1L<<6, mouse_move_hook, &data); // 6 = MotionNotify 1L<<6 = 64 je crois
	mlx_loop_hook(data.connect, loop_hook_bonus, &data); // appel continu
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop(data.connect);
	return (0);	
}
