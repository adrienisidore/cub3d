/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:09:27 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 18:30:08 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_keypress(int keycode, t_mlx_data *data)
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

int ft_keyrelease(int keycode, t_mlx_data *data)
{
	if (keycode == XK_w)
		data->move_forward = 0;
	else if (keycode == XK_s)
		data->move_backward = 0;
	else if (keycode == XK_a)
		data->move_left = 0;
	else if (keycode == XK_d)
		data->move_right = 0;
	else if (keycode == XK_Left)
		data->rotate_left = 0;
	else if (keycode == XK_Right)
		data->rotate_right = 0;
	return (0);
}

void	ft_turnview(int key, t_mlx_data *pdata)
{
	double oldDirX;
	double oldPlaneX;
	double angle;

	angle = -pdata->rotSpeed; 
	if (key == XK_Right)
		angle = pdata->rotSpeed;
	oldDirX = pdata->dirX;
	pdata->dirX = pdata->dirX * cos(angle) - pdata->dirY * sin(angle);
	pdata->dirY = oldDirX * sin(angle) + pdata->dirY * cos(angle);
	oldPlaneX = pdata->planeX;
	pdata->planeX = pdata->planeX * cos(angle) - pdata->planeY * sin(angle);
	pdata->planeY = oldPlaneX * sin(angle) + pdata->planeY * cos(angle);
}