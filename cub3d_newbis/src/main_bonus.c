/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:38 by aisidore         ###   ########.fr       */
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
        printf("smap = %d\n", data->smap);
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

    // Décalage en haut à droite
    int offset_x = WIDTH - MINIMAP_WIDTH - 10;  // 10 px padding
    int offset_y = 10;

    for (mapY = 0; mapY < MAPHEIGHT; mapY++)
    {
        for (mapX = 0; mapX < MAPWIDTH; mapX++)
        {
            if (worldMap[mapY][mapX] == 0)
                color = 0x000000; // noir (sol)
            else if (worldMap[mapY][mapX] == 1)
                color = 0x888888; // gris (mur type 1)
            else if (worldMap[mapY][mapX] == 2)
                color = 0x0000FF; // bleu
            else if (worldMap[mapY][mapX] == 3)
                color = 0xFF0000; // rouge
            else
                color = 0xFFFFFF; // inconnu

            draw_square(data,
                        offset_x + (int)(mapX * cell_w),
                        offset_y + (int)(mapY * cell_h),
                        (int)cell_w,
                        color);
        }
    }

    // Dessine le joueur (petit carré vert)
    draw_square(data,
                offset_x + (int)(data->posX * cell_w),
                offset_y + (int)(data->posY * cell_h),
                3, // taille fixe pour bien voir
                0x00FF00);
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
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop_hook(data.connect, loop_hook_bonus, &data); // appel continu

	mlx_loop(data.connect);
	return (0);	
}