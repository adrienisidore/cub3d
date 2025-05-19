/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:09:27 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:23:07 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//qui est static et qui ne l'est pas ?

//Close destroy l'image de xpm
int	ft_close(t_mlx_data *pdata)
{
	mlx_destroy_image(pdata->connect, pdata->txt.data);
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
	{
		ft_putstr_fd(str, STDERR_FILENO);
		exit(1);	
	}
	exit(0);
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