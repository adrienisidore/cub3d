/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//Pour le bonus : VERIFIER QUE C'EST BIEN CE QU'ON ATTEND DE NOUS
int	mouse_move_hook(int x, int y, t_mlx_data *pdata)
{
	static int	last_x = -1;
	double		rotSpeed;
	(void)y;

	if (last_x == -1)
		last_x = x;

	int delta_x = x - last_x;
	last_x = x;

	rotSpeed = 0.003 * delta_x; // Ajuste ce facteur à ta sensibilité souhaitée

	double oldDirX = pdata->dirX;
	pdata->dirX = pdata->dirX * cos(-rotSpeed) - pdata->dirY * sin(-rotSpeed);
	pdata->dirY = oldDirX * sin(-rotSpeed) + pdata->dirY * cos(-rotSpeed);

	double oldPlaneX = pdata->planeX;
	pdata->planeX = pdata->planeX * cos(-rotSpeed) - pdata->planeY * sin(-rotSpeed);
	pdata->planeY = oldPlaneX * sin(-rotSpeed) + pdata->planeY * cos(-rotSpeed);

	ft_display(pdata); // Rafraîchir l'affichage

	return (0);
}

//mettre void plutot que ac av
int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx_data	data;

	ft_init(&data);
	ft_display(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
    mlx_hook(data.win_ptr, 6, 1L<<6, mouse_move_hook, &data); // 6 = MotionNotify 1L<<6 = 64 je crois
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data); // Event "fermer la fenêtre"
	mlx_loop_hook(data.connect, loop_hook, &data); // appel continu

	mlx_loop(data.connect);
	return (0);	
}