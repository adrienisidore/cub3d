/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/20 18:06:22 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"
#define MINIMAP_WIDTH  200
#define MINIMAP_HEIGHT 200

int	mouse_move_hook(int x, int y, t_mlx_data *pdata);
void draw_square(t_mlx_data *data, int x, int y, int size, int color);
void draw_minimap(t_mlx_data *data);
int loop_hook_bonus(t_mlx_data *data);
void draw_dda_on_minimap(t_mlx_data *pdata, int offset_x, int offset_y, double cell_w, double cell_h);
void	ft_display_bonus(t_mlx_data *pdata);

#endif
