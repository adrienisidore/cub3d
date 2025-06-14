/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:48 by aisidore          #+#    #+#             */
/*   Updated: 2025/06/14 12:40:24 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/home/aisidore/Downloads/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/keysymdef.h>

#include <X11/X.h>

# include <math.h>
#include <time.h>//Pour generer carte random

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define NO_LINK	"Error\nMinilibx unavailable.\n"
# define NO_WND		"Error\nCan't create new window.\n"
# define NO_IMG		"Error\nCan't display new image.\n"
# define NO_TX		"Error\nCan't open new texture.\n"


# define WIDTH		600
# define HEIGHT		600

#define MAPWIDTH	24//600 / 25 = 24
#define MAPHEIGHT	24


typedef struct s_texture_utils
{
	int lineHeight;//hauteur du mur
	int drawStart;//le pixel en haut de la ligne du mur
	int drawEnd;//le pixel en bas de la ligne du mur
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

	//Utile à la fois pour dda et pour l'affichage en lui même (ft_keyhook etc ...)
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


	int move_forward;
	int move_backward;
	int rotate_left;
	int rotate_right;
	int move_left;
	int move_right;


	int	error;// == 1 alors on affiche un message d'erreur et exit(1).
	//Si l'initialisation se passe bien on met exit à 0.

	int smap;

	//Pour ft_keyhook
	double moveSpeed;
	double rotSpeed;
	
	t_dda	dda;

	// On aura 4 textures comme ça.
	// Ici par exemple ce sera la texture Nord
	t_texture	txt;

	t_texture	txt_north;
	t_texture	txt_south;
	t_texture	txt_east;
	t_texture	txt_west;
	t_texture	*current_txt; // <== pour choisir dynamiquement la texture utilisée
	
	
}	t_mlx_data;

//A SUPPRIMER
extern int worldMap[MAPHEIGHT][MAPWIDTH];

//init.c
void	ft_init(t_mlx_data *pdata);

//exit.c
int	ft_stop(t_mlx_data *pdata);

//hook_utils.c
int ft_keypress(int keycode, t_mlx_data *data);
int ft_keyrelease(int keycode, t_mlx_data *data);
void	ft_turnview(int key, t_mlx_data *pdata);

//hook.c
int		loop_hook(t_mlx_data *pdata);
double	ft_fb(t_mlx_data *pdata, int which, int key);
void	ft_fbmove(int key, t_mlx_data *pdata);
double	ft_lat(t_mlx_data *pdata, int which, int key);
void	ft_latmove(int key, t_mlx_data *pdata);


//texture_utils.c
int	ft_rgb(int color, double shade);
void	ft_choose_texture(t_mlx_data *pdata);

//texture.c
void	ft_pixput(t_mlx_data *pdata, int x, int y, int color);
void	ft_floorceil(t_mlx_data *pdata);
void ft_texture(t_mlx_data *pdata, int x);

//display.c
void	ft_display(t_mlx_data *pdata, void (*fn)(t_mlx_data *));


#endif