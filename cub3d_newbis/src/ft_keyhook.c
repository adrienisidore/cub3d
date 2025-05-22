/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:05:27 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:06:36 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_mlx_data *data)
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
	else if (keycode == XK_Escape)
		ft_stop(data);
	return (0);
}

int key_release(int keycode, t_mlx_data *data)
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

static void	ft_fbmove(int key, t_mlx_data *pdata)
{
	if (key == XK_w)
	{
		if (!worldMap[(int)(pdata->posY)][(int)(pdata->posX + pdata->dirX * pdata->moveSpeed)])
			pdata->posX += pdata->dirX * pdata->moveSpeed;
		if (!worldMap[(int)(pdata->posY + pdata->dirY * pdata->moveSpeed)][(int)(pdata->posX)])
			pdata->posY += pdata->dirY * pdata->moveSpeed;
	}
	if (key == XK_s)
	{
		if (!worldMap[(int)(pdata->posY)][(int)(pdata->posX - pdata->dirX * pdata->moveSpeed)])
			pdata->posX -= pdata->dirX * pdata->moveSpeed;
		if (!worldMap[(int)(pdata->posY - pdata->dirY * pdata->moveSpeed)][(int)(pdata->posX)])
			pdata->posY -= pdata->dirY * pdata->moveSpeed;
	}
}

static void	ft_latmove(int key, t_mlx_data *pdata)
{
	if (key == XK_d)
	{
		if (!worldMap[(int)(pdata->posY)][(int)(pdata->posX + pdata->planeX * pdata->moveSpeed)])
			pdata->posX += pdata->planeX * pdata->moveSpeed;
		if (!worldMap[(int)(pdata->posY + pdata->planeY * pdata->moveSpeed)][(int)(pdata->posX)])
			pdata->posY += pdata->planeY * pdata->moveSpeed;
	}
	if (key == XK_a)
	{
		if (!worldMap[(int)(pdata->posY)][(int)(pdata->posX - pdata->planeX * pdata->moveSpeed)])
			pdata->posX -= pdata->planeX * pdata->moveSpeed;
		if (!worldMap[(int)(pdata->posY - pdata->planeY * pdata->moveSpeed)][(int)(pdata->posX)])
			pdata->posY -= pdata->planeY * pdata->moveSpeed;
	}
}

static void	ft_turnview(int key, t_mlx_data *pdata)
{
	double oldDirX = pdata->dirX;
	double oldPlaneX = pdata->planeX;
	double angle = (key == XK_Right) ? -pdata->rotSpeed : pdata->rotSpeed;

	pdata->dirX = pdata->dirX * cos(angle) - pdata->dirY * sin(angle);
	pdata->dirY = oldDirX * sin(angle) + pdata->dirY * cos(angle);

	pdata->planeX = pdata->planeX * cos(angle) - pdata->planeY * sin(angle);
	pdata->planeY = oldPlaneX * sin(angle) + pdata->planeY * cos(angle);
}

int loop_hook(t_mlx_data *data)
{
	if (data->move_forward)
		ft_fbmove(XK_w, data);
	if (data->move_backward)
		ft_fbmove(XK_s, data);
	if (data->move_left)
		ft_latmove(XK_a, data);
	if (data->move_right)
		ft_latmove(XK_d, data);
	if (data->rotate_left)
		ft_turnview(XK_Left, data);
	if (data->rotate_right)
		ft_turnview(XK_Right, data);

	ft_display(data); // Mise à jour de l'affichage à chaque frame
	return (0);
}