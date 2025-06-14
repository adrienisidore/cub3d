/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 19:48:12 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
  
//Utiliser images minilibx https://harm-smits.github.io/42docs/libs/minilibx/images.html

// Si le projet autorise votre libft, vous devez copier ses sources et son Makefile
// associé dans un dossier libft contenu à la racine. Le Makefile de votre projet doit
// compiler la librairie à l’aide de son Makefile, puis compiler le projet.

//PARFOIS JE RENTE DANS LE MUR SI JE FONCE DIRECT DEDANS

t_data	*ft_init_erika(t_gc *gc)
{
	t_data	*data;

	data = gc_malloc(sizeof(t_data), gc);
	data->f = NULL;
	data->c = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->no = NULL;
	data->we = NULL;
	data->map = NULL;
	data->flag = 0;
	data->ceiling = NULL;
	data->floor = NULL;
	data->pos_x = -1;
	data->pos_y = -1;
	data->pos_y = 'A'; //initialisation direction joueur
	data->stash = NULL;
	data->fd = -1;
	data->buffer = NULL;
	data->lg = 0;
	data->cl = 0;
	data->start = 0;
	data->arg = NULL;
	data->line = NULL;
	return (data);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;
	t_data	*data_erika;
	t_gc	gc;

	/////ERIKA
	(void)ac;
	gc_init(&gc);
	data_erika = NULL;
	data_erika = ft_init_erika(&gc);
	data_erika->arg = av[1];
	if (ft_parsing(av, data_erika, &gc) == 1)
	{
		gc_cleanup(&gc);
		return (1);
	}
	//////////////////
	ft_init(&data);
	ft_display(&data, NULL);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
	mlx_loop_hook(data.connect, ft_loophook, &data); // appel continu
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop(data.connect);
	gc_cleanup(&gc);
	return (0);	
}

