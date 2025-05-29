/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || str[0] == '\0' || fd < 0)
		exit(1);
	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

int	ft_stop(t_mlx_data *pdata)
{
	if (pdata->txt.data)
		mlx_destroy_image(pdata->connect, pdata->txt.data);
	if (pdata->txt_north.data)
		mlx_destroy_image(pdata->connect, pdata->txt_north.data);
	if (pdata->txt_south.data)
		mlx_destroy_image(pdata->connect, pdata->txt_south.data);
	if (pdata->txt_east.data)
		mlx_destroy_image(pdata->connect, pdata->txt_east.data);
	if (pdata->txt_west.data)
		mlx_destroy_image(pdata->connect, pdata->txt_west.data);
	if (pdata->img_ptr)
		mlx_destroy_image(pdata->connect, pdata->img_ptr);
	if (pdata->win_ptr)
		mlx_destroy_window(pdata->connect, pdata->win_ptr);
	if (pdata->connect)
	{	mlx_destroy_display(pdata->connect);
		free(pdata->connect);
	}
	if (pdata->error)
	{//ft_stop appelé durant l'initialisation, donc y'a eu un pb
		//D'apres le sujet, en + de Error\n il faut ajouter un message explicite
		//Pour ce faire on peut attribuer à error différentes valeurs (1 si on arrive
		//pas à connecter minilibx [par defaut], 2 si img_ptr etc...)
        if (pdata->error == 1)
            ft_putstr_fd(NO_LINK, STDERR_FILENO);
        if (pdata->error == 2)
            ft_putstr_fd(NO_WND, STDERR_FILENO);
        if (pdata->error == 3)
            ft_putstr_fd(NO_IMG, STDERR_FILENO);
        if (pdata->error == 4)
            ft_putstr_fd(NO_TX, STDERR_FILENO);
		exit(1);	
	}
	exit(0);
}
