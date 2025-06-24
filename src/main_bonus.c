/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/24 17:32:14 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//Pour le bonus : VERIFIER QUE C'EST BIEN CE QU'ON ATTEND DE NOUS
static int	ft_mousehook(int x, int y, t_mlx_data *pdata)
{
	static int	last_x = -1;
	double		rotspeed;
	(void)y;

	if (last_x == -1)
		last_x = x;

	int delta_x = x - last_x;
	last_x = x;

	rotspeed = 0.003 * delta_x; // Sensibilité
	// ✅ Rotation avec le bon signe
	double oldDirX = pdata->dirx;
	pdata->dirx = pdata->dirx * cos(rotspeed) - pdata->diry * sin(rotspeed);
	pdata->diry = oldDirX * sin(rotspeed) + pdata->diry * cos(rotspeed);

	double oldPlaneX = pdata->planex;
	pdata->planex = pdata->planex * cos(rotspeed) - pdata->planey * sin(rotspeed);
	pdata->planey = oldPlaneX * sin(rotspeed) + pdata->planey * cos(rotspeed);
	ft_display(pdata, ft_minimap);
	return (0);
}

int ft_loophookbonus(t_mlx_data *data)
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
	ft_display(data, ft_minimap);
	return (0);
}

static t_data	*ft_init_erika(t_gc *gc)
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
	data->pos_y = 'A';
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
	
	t_data	*data_erika;
	t_gc	gc;
	t_mlx_data	data;

	(void)ac;
	gc_init(&gc);
	data_erika = ft_init_erika(&gc);
	data_erika->arg = av[1];
	if (ft_parsing(av, data_erika, &gc) == 1)
	{
		gc_cleanup(&gc);
		return (1);
	}
	ft_init(&data, data_erika, &gc);
	ft_display(&data, ft_minimap);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, ft_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, ft_keyrelease, &data);
	//SAVOIR L'EXPLIQUER
    mlx_hook(data.win_ptr, 6, 1L<<6, ft_mousehook, &data); // 6 = MotionNotify 1L<<6 = 64 je crois
	mlx_loop_hook(data.connect, ft_loophookbonus, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data);
	mlx_loop(data.connect);
	return (0);
}
