/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/04/28 18:37:22 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/home/aisidore/Downloads/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# include <math.h>
#include <time.h>//Pour generer carte random

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define PI		3.141593
# define WIDTH		600
# define HEIGHT		600
#define CASE_SIZE 10
#define WID_WALL (WIDTH / CASE_SIZE)  // 60
#define HEI_WALL (HEIGHT / CASE_SIZE) // 60
# define BLACK 0x000000
# define COL  0xFF6600

typedef struct s_mlx_data
{
	void	*connect;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_pixptr;//unused ?

	int		bpp;
	int		endian;
	int		len;

	int		px;
	int		py;
	float		dx;//delta(x)
	float		dy;//delta(y)
	float		an;//angle : en C on utilise les radians (de 0pi - pi/2 - pi - 3pi/2 - 2pi) et pas les degres (allant de 0 a 360)
	float		fov;//field of view (jusqu'ou il voit)
	
}	t_mlx_data;

#endif