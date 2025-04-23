/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/04/23 12:50:21 by aisidore         ###   ########.fr       */
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
void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || str[0] == '\0' || fd < 0)
		exit(1);
	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	ft_exit(char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

void	ft_stop(t_mlx_data *pdata, int des_wnd, int des_disp, char *str)
{
	if (des_wnd == 1)
		mlx_destroy_window(pdata->connect, pdata->win_ptr);
	if (des_disp == 1)
		mlx_destroy_display(pdata->connect);
	free(pdata->connect);
	ft_exit(str);
}

int	ft_keyhook(int keysym, t_mlx_data *pdata)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(pdata->connect, pdata->img_ptr);
		ft_stop(pdata, 1, 1, NULL);
	}
	// ft_show(pdata);
	return (0);
}

void	ft_init(t_mlx_data *pdata)
{
	pdata->connect = mlx_init();
	if (!pdata->connect)
		exit (1);
	pdata->win_ptr = mlx_new_window(pdata->connect, 600, 600, "Titre");
	if (!pdata->win_ptr)
		ft_stop(pdata, 0, 1, NULL);
	pdata->img_ptr = mlx_new_image(pdata->connect, 600, 600);
	if (!pdata->img_ptr)
		ft_stop(pdata, 1, 1, NULL);
	//Acceder aux pixels d'une img
	// pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
	// 	&pdata->len, &pdata->endian);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	ft_init(&data);
	mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
	mlx_key_hook(data.win_ptr, ft_keyhook, &data);
	mlx_loop(data.connect);
	return (0);
}
