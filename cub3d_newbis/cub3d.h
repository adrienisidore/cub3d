/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/20 18:06:22 by aisidore         ###   ########.fr       */
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


typedef struct s_texture_utils
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX;
	int tex_x;
	int	tex_y;
	
	
	double step;
	double texPos;
	
}	t_texture_utils;

typedef struct s_texture
{
	void		*data;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	t_texture_utils		utils;
	
}	t_texture;

typedef struct s_dda
{
	double	cameraX;//normaliser chaque pixel en coord. [-1;1]
	double	rayDirX;//coord. X du regard du joueur
	double	rayDirY;//coord. Y du regard du joueur
	
	int		mapX;//coord. X de la case du joueur
	int		mapY;//coord. Y de la case du joueur
	//Pour demarrer DDA on devra savoir quel cote de la case du joeur le rayon touche en premier
	double	sideDistX;//distance jusqu'a la prochaine bordure vertical
	double	sideDistY;//distance jusqu'a la prochaine bordure horizontale
	double	deltaDistX;//distance (statique) a parcourir pour toucher la prochaine bordure verticale
	double	deltaDistY;//distance (statique) a parcourir pour toucher la prochaine bordure horizontale

	//DDA
	int		stepX;//Si +1 on passe a la bordure verticale suivante a droit (resp a gauche pour -1)
	int		stepY;//Si +1 on passe a la bordure horizontale suivante en bas  (resp en haut pour -1)
	int		hit;// ==1 j'ai touche un mur
	int		side;//==0 j'ai touche une bordure horizontale (resp ==1 verticale)
	double	perpWallDist;//distance (projetee/perpendiculaire a l'ecran) entre le joueur et le mur,
	//pour eviter que les murs semblent incurves : perpWallDist = Euclidean / |rayDir|

}	t_dda;

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
	
	// t_texture_utils		utils;
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

//display_utils.c
void ft_draw(t_mlx_data *pdata, int x, double perpWallDist, int side,
              		double rayDirX, double rayDirY);

//ft_show.c
void	ft_draw_floorceil(t_mlx_data *pdata);
void	ft_show(t_mlx_data *pdata);


#endif