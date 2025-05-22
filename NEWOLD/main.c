/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/12 14:48:10 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//map de taille [HEIGHT / CASE_SIZE : WIDTH / CASE_SIZE]
int	map[HEI_WALL][WID_WALL];

int	ft_close(t_mlx_data *pdata)
{
	mlx_destroy_image(pdata->connect, pdata->img_ptr);
	mlx_destroy_window(pdata->connect, pdata->win_ptr);
	mlx_destroy_display(pdata->connect);
	free(pdata->connect);
	exit(1);
}
void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || str[0] == '\0' || fd < 0)
		exit(1);
	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	ft_exit(char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

void	ft_stop(t_mlx_data *pdata, int des_wnd, int des_disp, char *str)
{
	if (des_wnd == 1)
		mlx_destroy_window(pdata->connect, pdata->win_ptr);
	if (des_disp == 1)
		mlx_destroy_display(pdata->connect);
	free(pdata->connect);
	ft_exit(str);
}


//Division par 10 car chaque 0/1 represente 10 pixel.
			//donc map[0][0] represente tous les pixels allant de 0 à 9
			//Si map[0][0] = 1 alors je les colorie tous
// Fonction pour dessiner les bords de la carte
void ft_drawmap(int map[HEI_WALL][WID_WALL])
{
    int x, y;

    // Dessin des bords
    for (y = 0; y < HEI_WALL; y++) {
        for (x = 0; x < WID_WALL; x++) {
            // Vérifie si on est sur un des bords
            if (x == 0 || x == WID_WALL - 1 || y == 0 || y == HEI_WALL - 1) {
                map[y][x] = 1;  // Mur (1) pour les bords
            }
			else if (rand() % 54 == 0)
				map[y][x] = 1;
			else
                map[y][x] = 0;  // Espace (0) à l'intérieur
        }
    }
}


void	ft_init(t_mlx_data *pdata)
{
	ft_drawmap(map);
	pdata->connect = mlx_init();
	if (!pdata->connect)
		exit (1);
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3d");
	if (!pdata->win_ptr)
		ft_stop(pdata, 0, 1, NULL);
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata, 1, 1, NULL);
	//Acceder aux pixels d'une img. Utile I guess
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
		&pdata->len, &pdata->endian);
	//arbitraire


	//AJOUTER rotSpeed et moveSPEED pour que la vitesse de deplacement de la 
	//minimap soit égale à celle du joueur
	pdata->px = 300;
	pdata->py = 300;
	pdata->an = 2 * PI;
	pdata->dx = cos(pdata->an) * 5;
	pdata->dy = sin(pdata->an) * 5;

	pdata->move_forward = 0;
	pdata->move_backward = 0;
	pdata->rotate_left = 0;
	pdata->rotate_right = 0;
	pdata->move_left = 0;
	pdata->move_right = 0;



	// Vérifier si la position initiale du joueur est sur un mur
    // Si c'est le cas, déplacer le joueur pour qu'il soit sur une case vide
    while (map[pdata->py / CASE_SIZE][pdata->px / CASE_SIZE] == 1) {
        pdata->px += 10;  // Déplace le joueur vers la droite de 10 pixels
        if (pdata->px >= WIDTH) {  // Si le joueur sort de la fenêtre, réinitialiser
            pdata->px = 0;
            pdata->py += 10;  // Déplace le joueur vers le bas de 10 pixels
        }
        if (pdata->py >= HEIGHT) {  // Si le joueur sort de la fenêtre, réinitialiser
            pdata->py = 0;
        }
    }
}

//Place un pixel à la couleur voulue dans une image
//color est au format 0xRRGGBB
void	ft_pixput(t_mlx_data *pdata, int x, int y, int color)
{
	int	disp;

	disp = (pdata->len * y) + ((pdata->bpp / 8) * x);
	*((unsigned int *)(disp + pdata->img_pixptr)) = color;
}

void	ft_show(t_mlx_data *pdata)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Par défaut : fond noir
			color = 0x000000;

			// Si c'est le perso (zone autour de px, py)
			if (x >= pdata->px - 2 && x <= pdata->px + 2 &&
				y >= pdata->py - 2 && y <= pdata->py + 2)
			{
				color = 0xFF0000; // Rouge pour le perso
			}
			// Si la coordonnee du pixel se situe dans une case
			// on la colore en vert
			else if (map[y / CASE_SIZE][x / CASE_SIZE] == 1)	   
			{
				color = 0x00FF00; // Vert pour les murs
			}
			// Sinon : tracer la grille
			else if (x % CASE_SIZE == 0 || y % CASE_SIZE == 0)
			{
				color = 0x202020; // Gris foncé pour les lignes de la grille
			}
			ft_pixput(pdata, x, y, color);

			x++;
		}
		y++;
	}

	int	line_length = 50;  // Longueur de la ligne
	// Dessiner chaque pixel de la ligne
	int i = 0;
	while (i < line_length)
	{
		int line_x = pdata->px + pdata->dx * i;//coordonnee x du pixel suivant de la ligne
		int line_y = pdata->py + pdata->dy * i;//coordonnee y du pixel suivant de la ligne
		//On s'assure de ne pas depasser les frontieres WIDTH et HEIGHT de la fenetre
		if (line_x >= 0 && line_x < WIDTH && line_y >= 0 && line_y < HEIGHT)
			ft_pixput(pdata, line_x, line_y, 0x0000FF);  // Bleu pour la ligne

		i++;
	}


	
	mlx_put_image_to_window(pdata->connect, pdata->win_ptr, pdata->img_ptr, 0, 0);
}
			








int key_press(int keycode, t_mlx_data *data)
{
	if (keycode == XK_w)
		data->move_forward = 1;
	else if (keycode == XK_s)
		data->move_backward = 1;
	else if (keycode == XK_a)
		data->move_left = 1;//
	else if (keycode == XK_d)
		data->move_right = 1;//
	else if (keycode == XK_Left)
		data->rotate_left = 1;
	else if (keycode == XK_Right)
		data->rotate_right = 1;
	else if (keycode == XK_Escape)
		ft_close(data);
	return (0);
}

int key_release(int keycode, t_mlx_data *data)
{
	if (keycode == XK_w)
		data->move_forward = 0;
	else if (keycode == XK_s)
		data->move_backward = 0;
	else if (keycode == XK_a)
		data->move_left = 0;
	else if (keycode == XK_d)
		data->move_right = 0;
	else if (keycode == XK_Left)
		data->rotate_left = 0;
	else if (keycode == XK_Right)
		data->rotate_right = 0;

	return (0);
}


int loop_hook(t_mlx_data *data)
{
	if (data->move_forward)
	{
		data->px += data->dx;
		data->py += data->dy;
	}
	if (data->move_backward)
	{
		data->px -= data->dx;
		data->py -= data->dy;
	}
	if (data->move_left)
	{
		// Vecteur perpendiculaire à la gauche
		data->px -= data->dy;
		data->py += data->dx;
	}
	if (data->move_right)
	{
		// Vecteur perpendiculaire à la droite
		data->px += data->dy;
		data->py -= data->dx;
	}
	if (data->rotate_left)
	{
		data->an -= 0.05;
		if (data->an < 0)
			data->an += 2 * PI;
		data->dx = cos(data->an) * 5;
		data->dy = sin(data->an) * 5;
	}
	if (data->rotate_right)
	{
		data->an += 0.05;
		if (data->an > 2 * PI)
			data->an -= 2 * PI;
		data->dx = cos(data->an) * 5;
		data->dy = sin(data->an) * 5;
	}
	ft_show(data); // redraw
	return (0);
}



int	main(int ac, char **av)
{
	(void) ac;
	(void)av;
	t_mlx_data	data;

	ft_init(&data);
	ft_show(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_press, &data);//
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, key_release, &data);//
	mlx_hook(data.win_ptr, 17, 0, ft_close, &data);
	//mlx_key_hook(data.win_ptr, ft_keyhook, &data);
	mlx_loop_hook(data.connect, loop_hook, &data);//
	mlx_loop(data.connect);
	return (0);
}


