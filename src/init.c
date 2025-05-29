/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/23 11:26:04 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// pdata->dirX = -1;//Regard a gauche (arbitraire) sur le plan [-1, 1]
// pdata->dirY = 0;//regard ni en haut ni en bas mais au milieu
//  sur le plan [1, -1] pdata->planeX = 0;//permet une ligne perpendiculaire
// pdata->planeY = 0.66;//et ps 1 pour que ce soit un peu plus realiste
// ...
//(A TESTER)
// pdata->error = 0;//Initialisation terminée,
//  pas de message d'erreur dans ft_stop

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

static void	ft_initplayer(t_mlx_data *pdata)
{
	pdata->posX = 12;
	pdata->posY = 10;
	pdata->dirX = -1;
	pdata->dirY = 0;
	pdata->planeX = 0;
	pdata->planeY = 0.66;
	pdata->moveSpeed = 0.0125;
	pdata->rotSpeed = 0.00625;
	pdata->move_forward = 0;
	pdata->move_backward = 0;
	pdata->rotate_left = 0;
	pdata->rotate_right = 0;
	pdata->move_left = 0;
	pdata->move_right = 0;
	pdata->error = 0;
	pdata->smap = 0;
}

void	ft_init(t_mlx_data *pdata)
{
	ft_bzero(pdata, sizeof(t_mlx_data));
	pdata->error = 1;
	pdata->connect = mlx_init();
	if (!pdata->connect)
		ft_stop(pdata);
	pdata->error = 2;
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3d");
	if (!pdata->win_ptr)
		ft_stop(pdata);
	pdata->error = 3;
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata);
	pdata->error = 4;
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
			&pdata->len, &pdata->endian);

	//pdata->txt.data = mlx_xpm_file_to_image(pdata->connect,
	//		"./textures/wall_1.xpm", &pdata->txt.width, &pdata->txt.height);
	//Pour chaque texture N S E O on fait la même chose :
	pdata->txt_north.data = mlx_xpm_file_to_image(pdata->connect, "./textures/wall_1.xpm", &pdata->txt_north.width, &pdata->txt_north.height);
	pdata->txt_south.data = mlx_xpm_file_to_image(pdata->connect, "./textures/wall_2.xpm", &pdata->txt_south.width, &pdata->txt_south.height);
	pdata->txt_east.data  = mlx_xpm_file_to_image(pdata->connect, "./textures/wall_3.xpm", &pdata->txt_east.width, &pdata->txt_east.height);
	pdata->txt_west.data  = mlx_xpm_file_to_image(pdata->connect, "./textures/wall_4.xpm", &pdata->txt_west.width, &pdata->txt_west.height);
	if (!pdata->txt_north.data || !pdata->txt_south.data || !pdata->txt_east.data || !pdata->txt_west.data)
		ft_stop(pdata); 
	pdata->txt_north.addr = mlx_get_data_addr(pdata->txt_north.data, &pdata->txt_north.bpp, &pdata->txt_north.size_line, &pdata->txt_north.endian);
	pdata->txt_south.addr = mlx_get_data_addr(pdata->txt_south.data, &pdata->txt_south.bpp, &pdata->txt_south.size_line, &pdata->txt_south.endian);
	pdata->txt_east.addr = mlx_get_data_addr(pdata->txt_east.data, &pdata->txt_east.bpp, &pdata->txt_east.size_line, &pdata->txt_east.endian);
	pdata->txt_west.addr = mlx_get_data_addr(pdata->txt_west.data, &pdata->txt_west.bpp, &pdata->txt_west.size_line, &pdata->txt_west.endian);
	//////////////////////////////////////////////////////////////////
	//if (!pdata->txt.data)
	//	ft_stop(pdata);
	//pdata->txt.addr = mlx_get_data_addr(pdata->txt.data, &pdata->txt.bpp,
	//		&pdata->txt.size_line, &pdata->txt.endian);



	



	ft_initplayer(pdata);
}
