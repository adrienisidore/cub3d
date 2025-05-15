/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/15 16:42:27 by aisidore         ###   ########.fr       */
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


# define WIDTH		600
# define HEIGHT		600

#define MAPWIDTH	24//600 / 25 = 24
#define MAPHEIGHT	24

typedef struct s_texture
{
	void		*data;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	
}	t_texture;

typedef struct s_trigo
{
	
}	t_trigo;

typedef struct s_mlx_data
{
	void	*connect;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_pixptr;//unused ?

	int		bpp;
	int		endian;
	int		len;

	//position joueur
	double posX;
	double posY;
	//direction du regard sur le plan [-1, 1][-1, 1]
	double dirX;
	double dirY;
	//surface sur laquelle les rayons vont se projeter (ligne perpendiculaire au regard pdata->dirX, pdata->dirY)
	double planeX;
	double planeY;
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	

	double moveSpeed;
	double rotSpeed;
	
	t_texture	txt;
	
	
}	t_mlx_data;

extern int worldMap[MAPHEIGHT][MAPWIDTH];
//exit.c
int		ft_close(t_mlx_data *pdata);
void	ft_putstr_fd(char *str, int fd);
void	ft_exit(char *str);
void	ft_stop(t_mlx_data *pdata, int des_wnd, int des_disp, char *str);

//ft_keyhook.c
int		ft_keyhook(int keysym, t_mlx_data *pdata);

//ft_show.c
void	ft_show(t_mlx_data *pdata);


#endif