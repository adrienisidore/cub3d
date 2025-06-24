/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:32:01 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Present dans la libft : OUI
//Useful si je veux utiliser les dummies de_wnd etc en cas de prb ou en fin de
//code.
//En effet en mettant des 0's partout on peut faire des if (!pdata->img_ptr)...
static void	ft_bzero(void *pointer, size_t times)
{
	unsigned char	*buffer;
	unsigned int	i;

	i = 0;
	buffer = (unsigned char *)pointer;
	while (times--)
	{
		buffer[i] = 0;
		i++;
	}
}

static void ft_initdir(t_mlx_data *data, char direction)
{
	data->dirx = 0;
	data->diry = -1;
	data->planex = 0.66;
	data->planey = 0;
	if (direction == 'S')
	{
		data->diry = 1;
		data->planex = -0.66;
	}
	else if (direction == 'E')
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.66;
	}
	else if (direction == 'W')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -0.66;
	}
}

static void	ft_initplayer(t_mlx_data *pdata, t_data *data_erika)
{
	pdata->crr = data_erika->ceiling[0];
	pdata->cgg = data_erika->ceiling[1];
	pdata->cbb = data_erika->ceiling[2];
	pdata->frr = data_erika->floor[0];
	pdata->fgg = data_erika->floor[1];
	pdata->fbb = data_erika->floor[2];
	// pdata->lg = data_erika->lg;
	// pdata->cl = data_erika->cl;
	pdata->map = data_erika->map;
	pdata->posx = (double)data_erika->pos_x + 0.5;
	pdata->posy = (double)data_erika->pos_y + 0.5;
	ft_initdir(pdata, data_erika->pos);
	pdata->movespeed = 0.0125;
	pdata->rotspeed = 0.0125;
	pdata->move_forward = 0;
	pdata->move_backward = 0;
	pdata->rotate_left = 0;
	pdata->rotate_right = 0;
	pdata->move_left = 0;
	pdata->move_right = 0;
	pdata->error = 0;
	pdata->smap = 0;
	pdata->exit_requested = 0;
}

static void	ft_window(t_mlx_data *pdata, t_gc *gc)
{
	ft_bzero(pdata, sizeof(t_mlx_data));
	pdata->gc = gc;
	pdata->error = 1;
	pdata->connect = mlx_init();
	if (!pdata->connect)
		ft_stop(pdata);
	pdata->error = 2;
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3D");
	if (!pdata->win_ptr)
		ft_stop(pdata);
	pdata->error = 3;
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata);
	pdata->error = 4;
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
			&pdata->len, &pdata->endian);
}

void	ft_init(t_mlx_data *pdata, t_data *data_erika, t_gc *gc)
{
	ft_window(pdata, gc);
	pdata->txt_north.data = mlx_xpm_file_to_image(pdata->connect,
		data_erika->no, &pdata->txt_north.width, &pdata->txt_north.height);
	pdata->txt_south.data = mlx_xpm_file_to_image(pdata->connect,
		data_erika->so, &pdata->txt_south.width, &pdata->txt_south.height);
	pdata->txt_east.data  = mlx_xpm_file_to_image(pdata->connect,
		data_erika->ea, &pdata->txt_east.width, &pdata->txt_east.height);
	pdata->txt_west.data  = mlx_xpm_file_to_image(pdata->connect,
		data_erika->we, &pdata->txt_west.width, &pdata->txt_west.height);
	if (!pdata->txt_north.data || !pdata->txt_south.data
		|| !pdata->txt_east.data || !pdata->txt_west.data)
		ft_stop(pdata);
	pdata->txt_north.addr = mlx_get_data_addr(pdata->txt_north.data,
		&pdata->txt_north.bpp, &pdata->txt_north.size_line,
		&pdata->txt_north.endian);
	pdata->txt_south.addr = mlx_get_data_addr(pdata->txt_south.data,
		&pdata->txt_south.bpp, &pdata->txt_south.size_line,
		&pdata->txt_south.endian);
	pdata->txt_east.addr = mlx_get_data_addr(pdata->txt_east.data,
		&pdata->txt_east.bpp, &pdata->txt_east.size_line,
		&pdata->txt_east.endian);
	pdata->txt_west.addr = mlx_get_data_addr(pdata->txt_west.data,
		&pdata->txt_west.bpp, &pdata->txt_west.size_line,
		&pdata->txt_west.endian);
	ft_initplayer(pdata, data_erika);
	// pdata->gc = gc;
}

