/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/04/23 14:02:04 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/home/aisidore/Downloads/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# include <math.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define WIDTH		600
# define HEIGHT		600

typedef struct s_mlx_data
{
	void	*connect;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_pixptr;//unused
}	t_mlx_data;

#endif