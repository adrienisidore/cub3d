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

#include "cub3d_bonus.h"



static double	ft_fb(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_w)
	{
		if (!which)
			return (pdata->posX + pdata->dirX * pdata->moveSpeed);
		return (pdata->posY + pdata->dirY * pdata->moveSpeed);
	}
	if (key == XK_s)
	{
		if (!which)
			return (pdata->posX - pdata->dirX * pdata->moveSpeed);
		return (pdata->posY - pdata->dirY * pdata->moveSpeed);
	}
	return (0.0);
}

static void	ft_fbmove(int key, t_mlx_data *pdata)
{
	if (key == XK_w)
	{
		if (!worldMap[(int)(pdata->posY)][(int)ft_fb(pdata, 0, XK_w)])
			pdata->posX += pdata->dirX * pdata->moveSpeed;
		if (!worldMap[(int)ft_fb(pdata, 1, XK_w)][(int)(pdata->posX)])
			pdata->posY += pdata->dirY * pdata->moveSpeed;
	}
	if (key == XK_s)
	{
		if (!worldMap[(int)(pdata->posY)][(int)ft_fb(pdata, 0, XK_s)])
			pdata->posX -= pdata->dirX * pdata->moveSpeed;
		if (!worldMap[(int)ft_fb(pdata, 1, XK_s)][(int)(pdata->posX)])
			pdata->posY -= pdata->dirY * pdata->moveSpeed;
	}
}

static double	ft_lat(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_d)
	{
		if (!which)
			return (pdata->posX + pdata->planeX * pdata->moveSpeed);
		return (pdata->posY + pdata->planeY * pdata->moveSpeed);
	}
	if (key == XK_a)
	{
		if (!which)
			return (pdata->posX - pdata->planeX * pdata->moveSpeed);
		return (pdata->posY - pdata->planeY * pdata->moveSpeed);
	}
	return (0.0);
}

static void	ft_latmove(int key, t_mlx_data *pdata)
{
	if (key == XK_d)
	{
		if (!worldMap[(int)(pdata->posY)][(int)ft_lat(pdata, 0, XK_d)])
			pdata->posX += pdata->planeX * pdata->moveSpeed;
		if (!worldMap[(int)ft_lat(pdata, 1, XK_d)][(int)(pdata->posX)])
			pdata->posY += pdata->planeY * pdata->moveSpeed;
	}
	if (key == XK_a)
	{
		if (!worldMap[(int)(pdata->posY)][(int)ft_lat(pdata, 0, XK_a)])
			pdata->posX -= pdata->planeX * pdata->moveSpeed;
		if (!worldMap[(int)ft_lat(pdata, 1, XK_a)][(int)(pdata->posX)])
			pdata->posY -= pdata->planeY * pdata->moveSpeed;
	}
}

int loop_hook_bonus(t_mlx_data *data)
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
	ft_display_bonus(data); // Mise à jour de l'affichage à chaque frame
	return (0);
}