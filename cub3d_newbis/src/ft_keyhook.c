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

static int	ft_fill(int which, t_mlx_data *pdata, int keysym)
{
	if (which == 1)
		return ((int)pdata->posY);
	if (which == 2)
		return ((int)pdata->posX);
	if (which == 3)
	{
		if (keysym == XK_w)
			return ((int)(pdata->posY + pdata->dirY * pdata->moveSpeed));//avancer
		else if (keysym == XK_a)
			return ((int)(pdata->posY - pdata->planeY * pdata->moveSpeed));
		else if (keysym == XK_d)
			return ((int)(pdata->posY + pdata->planeY * pdata->moveSpeed));
		return ((int)(pdata->posY - pdata->dirY * pdata->moveSpeed));//reculer
	}
	if (which == 4)
	{
		if (keysym == XK_w)
			return ((int)(pdata->posX + pdata->dirX * pdata->moveSpeed));//avancer
		else if (keysym == XK_d)
			return ((int)(pdata->posX + pdata->planeX * pdata->moveSpeed));
		else if (keysym == XK_a)
			return ((int)(pdata->posX - pdata->planeX * pdata->moveSpeed));
		return ((int)(pdata->posX - pdata->dirX * pdata->moveSpeed));//reculer
	}
	return (0);
}

static void	ft_latmove(int keysym, t_mlx_data *pdata)
{
	if (keysym == XK_d)
	{
		if (!worldMap[ft_fill(1, pdata, XK_d)][ft_fill(4, pdata, XK_d)])
			pdata->posX += pdata->planeX * pdata->moveSpeed;
		if (!worldMap[ft_fill(3, pdata, XK_d)][ft_fill(2, pdata, XK_d)])
			pdata->posY += pdata->planeY * pdata->moveSpeed;
	}
	if (keysym == XK_a)
	{
		if (!worldMap[ft_fill(1, pdata, XK_a)][ft_fill(4, pdata, XK_a)])
			pdata->posX -= pdata->planeX * pdata->moveSpeed;
		if (!worldMap[ft_fill(3, pdata, XK_a)][ft_fill(2, pdata, XK_a)])
			pdata->posY -= pdata->planeY * pdata->moveSpeed;
	}
	
}
static void	ft_fbmove(int keysym, t_mlx_data *pdata)
{
	if (keysym == XK_w)
	{
		if (!worldMap[ft_fill(1, pdata, XK_w)][ft_fill(4, pdata, XK_w)])
			pdata->posX += pdata->dirX * pdata->moveSpeed;
		if (!worldMap[ft_fill(3, pdata, XK_w)][ft_fill(2, pdata, XK_w)])
			pdata->posY += pdata->dirY * pdata->moveSpeed;
	}
	if (keysym == XK_s)
	{
		//C'est ça qui evite de traverser la map car si par ex à la prochaine
		//coord x y'a un mur alors il va juste avancer en y ce qui donne l'impression
		//qu'il se décale le long du mur
		if (!worldMap[ft_fill(1, pdata, XK_s)][ft_fill(4, pdata, XK_s)])
			pdata->posX -= pdata->dirX * pdata->moveSpeed;
		if (!worldMap[ft_fill(3, pdata, XK_s)][ft_fill(2, pdata, XK_s)])
			pdata->posY -= pdata->dirY * pdata->moveSpeed;
	}
}

static void		ft_turnview(int keysym, t_mlx_data *pdata)
{
	double oldDirX;
	double oldPlaneX;
	
	if (keysym == XK_Right)
	{
		oldDirX = pdata->dirX;
		pdata->dirX = pdata->dirX * cos(-pdata->rotSpeed) - pdata->dirY * sin(-pdata->rotSpeed);
		pdata->dirY = oldDirX * sin(-pdata->rotSpeed) + pdata->dirY * cos(-pdata->rotSpeed);
		oldPlaneX = pdata->planeX;
		pdata->planeX = pdata->planeX * cos(-pdata->rotSpeed) - pdata->planeY * sin(-pdata->rotSpeed);
		pdata->planeY = oldPlaneX * sin(-pdata->rotSpeed) + pdata->planeY * cos(-pdata->rotSpeed);
	}
	if (keysym == XK_Left)
	{
		oldDirX = pdata->dirX;
		pdata->dirX = pdata->dirX * cos(pdata->rotSpeed) - pdata->dirY * sin(pdata->rotSpeed);
		pdata->dirY = oldDirX * sin(pdata->rotSpeed) + pdata->dirY * cos(pdata->rotSpeed);
		oldPlaneX = pdata->planeX;
		pdata->planeX = pdata->planeX * cos(pdata->rotSpeed) - pdata->planeY * sin(pdata->rotSpeed);
		pdata->planeY = oldPlaneX * sin(pdata->rotSpeed) + pdata->planeY * cos(pdata->rotSpeed);
	}
	
}
//ATTENTION quand je fonce sur les bords de la map je traverse le mur
int	ft_keyhook(int keysym, t_mlx_data *pdata)
{
	if (keysym == XK_Escape)
		ft_stop(pdata);
	if (keysym == XK_w || keysym == XK_s)
		ft_fbmove(keysym, pdata);
	if (keysym == XK_a || keysym == XK_d)
		ft_latmove(keysym, pdata);
	if (keysym == XK_Right || keysym == XK_Left)
		ft_turnview(keysym, pdata);
	ft_display(pdata);
	return (0);
}
