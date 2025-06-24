/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:05:27 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:31:22 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_fb(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_w)
	{
		if (!which)
			return (pdata->posx + pdata->dirx * pdata->movespeed);
		return (pdata->posy + pdata->diry * pdata->movespeed);
	}
	if (key == XK_s)
	{
		if (!which)
			return (pdata->posx - pdata->dirx * pdata->movespeed);
		return (pdata->posy - pdata->diry * pdata->movespeed);
	}
	return (0.0);
}

void	ft_fbmove(int key, t_mlx_data *pdata)
{
	if (key == XK_w)
	{
		if (pdata->map[(int)(pdata->posy)][(int)ft_fb(pdata, 0, XK_w)] != '1')
			pdata->posx += pdata->dirx * pdata->movespeed;
		if (pdata->map[(int)ft_fb(pdata, 1, XK_w)][(int)(pdata->posx)] != '1')
			pdata->posy += pdata->diry * pdata->movespeed;
	}
	if (key == XK_s)
	{
		if (pdata->map[(int)(pdata->posy)][(int)ft_fb(pdata, 0, XK_s)] != '1')
			pdata->posx -= pdata->dirx * pdata->movespeed;
		if (pdata->map[(int)ft_fb(pdata, 1, XK_s)][(int)(pdata->posx)] != '1')
			pdata->posy -= pdata->diry * pdata->movespeed;
	}
}

double	ft_lat(t_mlx_data *pdata, int which, int key)
{
	if (key == XK_d)
	{
		if (!which)
			return (pdata->posx + pdata->planex * pdata->movespeed);
		return (pdata->posy + pdata->planey * pdata->movespeed);
	}
	if (key == XK_a)
	{
		if (!which)
			return (pdata->posx - pdata->planex * pdata->movespeed);
		return (pdata->posy - pdata->planey * pdata->movespeed);
	}
	return (0.0);
}

void	ft_latmove(int key, t_mlx_data *pdata)
{
	if (key == XK_d)
	{
		if (pdata->map[(int)(pdata->posy)][(int)ft_lat(pdata, 0, XK_d)] != '1')
			pdata->posx += pdata->planex * pdata->movespeed;
		if (pdata->map[(int)ft_lat(pdata, 1, XK_d)][(int)(pdata->posx)] != '1')
			pdata->posy += pdata->planey * pdata->movespeed;
	}
	if (key == XK_a)
	{
		if (pdata->map[(int)(pdata->posy)][(int)ft_lat(pdata, 0, XK_a)] != '1')
			pdata->posx -= pdata->planex * pdata->movespeed;
		if (pdata->map[(int)ft_lat(pdata, 1, XK_a)][(int)(pdata->posx)] != '1')
			pdata->posy -= pdata->planey * pdata->movespeed;
	}
}

int ft_loophook(t_mlx_data *data)
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
	if (data->exit_requested)
		ft_stop(data);
	ft_display(data, NULL);
	return (0);
}
