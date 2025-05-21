/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:16 by aisidore          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:38 by aisidore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
  
//Utiliser images minilibx https://harm-smits.github.io/42docs/libs/minilibx/images.html

// Si le projet autorise votre libft, vous devez copier ses sources et son Makefile
// associé dans un dossier libft contenu à la racine. Le Makefile de votre projet doit
// compiler la librairie à l’aide de son Makefile, puis compiler le projet.

//Present dans la libft : OUI
//Useful si je veux utiliser les dummies de_wnd etc en cas de prb ou en fin de code.
//En effet en mettant des 0's partout on peut faire des if (!pdata->img_ptr)...
static void	ft_bzero(void *pointer, size_t times)
{
	unsigned char	*buffer;
	unsigned int	i;

	i = 0;
	buffer = (unsigned char *)pointer;
	while (times--)
	{
		buffer[i] = 0;
		i++;
	}
}




//static void	ft_putstr_fd(char *str, int fd)
//{
//	int	i;
//
//	if (!str || str[0] == '\0' || fd < 0)
//		exit(1);
//	i = 0;
//	while (str[i])
//		write(fd, &str[i++], 1);
//}

int	ft_stop(t_mlx_data *pdata)
{
	if (pdata->txt.data)
		mlx_destroy_image(pdata->connect, pdata->txt.data);
	if (pdata->img_ptr)
		mlx_destroy_image(pdata->connect, pdata->img_ptr);
	if (pdata->win_ptr)
		mlx_destroy_window(pdata->connect, pdata->win_ptr);
	if (pdata->connect)
	{	mlx_destroy_display(pdata->connect);
		free(pdata->connect);
	}
	if (pdata->error)
	{//ft_stop appelé durant l'initialisation, donc y'a eu un pb
		//ft_putstr_fd("Error\n", STDERR_FILENO);
		write(STDERR_FILENO, "Error\n", 6);
		exit(1);	
	}
	exit(0);
}


static void	ft_initplayer(t_mlx_data *pdata)
{
	pdata->posX = 12;
	pdata->posY = 10;
	pdata->dirX = -1;//Regard a gauche (arbitraire) sur le plan [-1, 1]
	pdata->dirY = 0;//regard ni en haut ni en bas mais au milieu sur le plan [1, -1]
	pdata->planeX = 0;//permet une ligne perpendiculaire
	pdata->planeY = 0.66;//et ps 1 pour que ce soit un peu plus realiste
	pdata->moveSpeed = 0.2;
	pdata->rotSpeed = 0.1;
	pdata->error = 0;//Initialisation terminée, pas de message d'erreur dans ft_stop
}


static void	ft_init(t_mlx_data *pdata)
{
	ft_bzero(pdata, sizeof(t_mlx_data));
	pdata->error = 1;
	pdata->connect = mlx_init();
	if (!pdata->connect)
		exit (1);//plutot ft_stop
	pdata->win_ptr = mlx_new_window(pdata->connect, WIDTH, HEIGHT, "Cub3d");
	if (!pdata->win_ptr)
		ft_stop(pdata);
	pdata->img_ptr = mlx_new_image(pdata->connect, WIDTH, HEIGHT);
	if (!pdata->img_ptr)
		ft_stop(pdata);
	//Acceder aux pixels d'une img. Utile I guess
	pdata->img_pixptr = mlx_get_data_addr(pdata->img_ptr, &pdata->bpp,
		&pdata->len, &pdata->endian);
		
	pdata->txt.data = mlx_xpm_file_to_image(pdata->connect,
		"./textures/wall_1.xpm",&pdata->txt.width, &pdata->txt.height);
	if (!pdata->txt.data)
	{
		//mlx_destroy_image(pdata->connect, pdata->txt.data);
		ft_stop(pdata);
	}
	pdata->txt.addr = mlx_get_data_addr(pdata->txt.data,
		&pdata->txt.bpp, &pdata->txt.size_line, &pdata->txt.endian);
	ft_initplayer(pdata);
}

//Pour le bonus
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


int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx_data	data;


	
	ft_init(&data);
	ft_display(&data);
	mlx_hook(data.win_ptr, 17, 0, ft_stop, &data);
	//mlx_hook(data.win_ptr, 6, 1L<<6, mouse_move_hook, &data); // 6 = MotionNotify 1L<<6 = 64 je crois
	mlx_key_hook(data.win_ptr, ft_keyhook, &data);
	mlx_loop(data.connect);
	return (0);	
}
