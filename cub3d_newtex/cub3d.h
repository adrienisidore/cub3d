/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/12 16:54:23 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/home/aisidore/Documents/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# include <math.h>
#include <time.h>//Pour generer carte random

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


# define WIDTH		600
# define HEIGHT		600

#define MAPWIDTH	24//600 / 25 = 24
#define MAPHEIGHT	24

typedef struct s_ig
{
	void		*data;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	
}	t_ig;	


typedef struct s_mlx_data
{
	void	*connect;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_pixptr;//unused ?

	int		bpp;
	int		endian;
	int		len;

	int		px;//useful for minimap
	int		py;//useful for minimap

	//position joueur
	double posX, posY;
	//direction du regard sur le plan [-1, 1][-1, 1]
	double dirX, dirY;
	//surface sur laquelle les rayons vont se projeter (ligne perpendiculaire au regard pdata->dirX, pdata->dirY)
	double planeX, planeY;
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	t_ig	texture;
	
	
	

	
}	t_mlx_data;

//exit.c
int		ft_close(t_mlx_data *pdata);
void	ft_putstr_fd(char *str, int fd);
void	ft_exit(char *str);
void	ft_stop(t_mlx_data *pdata, int des_wnd, int des_disp, char *str);

#endif