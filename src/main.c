/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 12:12:17 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
  
//Utiliser images minilibx https://harm-smits.github.io/42docs/libs/minilibx/images.html

// Si le projet autorise votre libft, vous devez copier ses sources et son Makefile
// associé dans un dossier libft contenu à la racine. Le Makefile de votre projet doit
// compiler la librairie à l’aide de son Makefile, puis compiler le projet.

//PARFOIS JE RENTE DANS LE MUR SI JE FONCE DIRECT DEDANS


int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx_data	data;

	ft_init(&data);
	ft_display(&data, NULL);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
	mlx_loop_hook(data.connect, loop_hook, &data); // appel continu
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop(data.connect);
	return (0);	
}
