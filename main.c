/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/04/22 17:55:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_mlx_data *pdata)
{
	mlx_destroy_image(pdata->connect, pdata->img_ptr);
	mlx_destroy_window(pdata->connect, pdata->win_ptr);
	mlx_destroy_display(pdata->connect);
	free(pdata->connect);
	exit(1);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data.connect = mlx_init();
	if (!data.connect)
		exit (1);
	data.win_ptr = mlx_new_window(data.connect, 600, 600, "Titre");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.connect);
		exit (1);
	}
	data.img_ptr = mlx_new_image(data.connect, 600, 600);
	if (!data.img_ptr)
	{
		mlx_destroy_window(data.connect, data.win_ptr);
		mlx_destroy_display(data.connect);
		exit (1);
	}
	//A quoi ca sert ca ?
	// pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
	// 	&pdata->len, &pdata->endian);

	//Quand j'ai fini : 17 == touche escape
	mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
	
	mlx_loop(data.connect);
	return (0);
}