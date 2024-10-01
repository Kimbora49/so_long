# include "minilibx-linux/mlx.h"
# include  "minilibx-linux/mlx_int.h"
# include  "mlx.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"

#define ESC				65307
#define W				119
#define A				97
#define S				115
#define D				100

int line; //	indice de parcours de chaque ligne de la map
int col; //	indice de parcours de chaque colonne de la map

int free_map_all(t_mlx_struct *mlx)
{
	unsigned int i;

	i = 1;
	while(mlx->map[i])
	{
		free(mlx->map[i]);
		i++;
	}
	free(mlx->map);
	free(mlx);
	return (0);
}

int	destroy_full(t_mlx_struct *mlx)
{
	if (mlx->player)
		mlx_destroy_image(mlx->mlx_ptr, mlx->player);
	if (mlx->sol)
		mlx_destroy_image(mlx->mlx_ptr, mlx->sol);
	if (mlx->wall)
	mlx_destroy_image(mlx->mlx_ptr, mlx->wall);
	if (mlx->exit)
		mlx_destroy_image(mlx->mlx_ptr, mlx->exit);
	if (mlx->collectible)
		mlx_destroy_image(mlx->mlx_ptr, mlx->collectible);
	if (mlx->win_ptr)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	}
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	return (0);
}

int	ft_free_endgame(t_mlx_struct *mlx)
{
	destroy_full(mlx);
	free_map_all(mlx);
	return (0);
}

int flood_fill(t_mlx_struct *mlx, int x, int y)
{
	if (mlx->map[x][y] == '1' || mlx->map[x][y] == 'X' 
			|| mlx->map[x][y] == '\n' ||  x == mlx->win_height / 64
			|| x <= 1 || y <= 0)
		return (0);
	else
	{
		if (mlx->map[x][y] == 'C')
			mlx->found_collectible++;
		else if (mlx->map[x][y] == 'E')
			mlx->found_exit = true;
		mlx->map[x][y] = 'X';
		flood_fill(mlx, x + 1, y);
		flood_fill(mlx, x, y + 1);
		flood_fill(mlx, x - 1, y);
		flood_fill(mlx, x, y - 1);
	}
	return (0);
}

bool verif_walls(t_mlx_struct *mlx)
{
	int	i;
	int len;
	int	j;

	i = 0;
	j = 1;
	while(mlx->map[j][i])
	{
		if (mlx->map[j][i] != '1' && mlx->map[j][i] != '\n')
			return false;
		i++;
	}
	j = 2;
	while(mlx->map[j + 1])
	{
		len = ft_strlen(mlx->map[j]);
		if (mlx->map[j][0] != '1' || mlx->map[j][len - 2] != '1')
			return false;
		j++;
	}
	i = 0;
	while(mlx->map[j][i])
	{
		if (mlx->map[j][i] != '1')
			return false;
		i++;
	}
	return true;
}
bool verif_content(t_mlx_struct *mlx)
{
	int i;
	int j;
	int Ecount;
	int Pcount;

	Ecount = 0;
	Pcount = 0;
	j = 1;
	while (mlx->map[j])
	{
		i = 0;
		while (mlx->map[j][i])
		{
			if (mlx->map[j][i] != '1' 
				&& mlx->map[j][i] != '0'
				&& mlx->map[j][i] != 'C' 
				&& mlx->map[j][i] != 'E' 
				&& mlx->map[j][i] != 'P'
				&& mlx->map[j][i] != '\n')
				return false;
			if (mlx->map[j][i] == 'C')
				mlx->tot_collectible++;
			if (mlx->map[j][i] == 'E')
				Ecount++;
			if (mlx->map[j][i] == 'P')
			{
				mlx->starter_P_x = j;
				mlx->starter_P_y = i;
				Pcount++;
			}
			i++;
		}
		j++;
	}
	if (mlx->tot_collectible < 1 || Ecount != 1 || Pcount != 1)
		return false;
	return true;
	
}

int ft_strnlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

bool verif_input(t_mlx_struct *mlx)
{
	int	i;
	int	x;
	int	y;
	int flag;
	int	len_mlxmap0;

	flag = 0;
    i = 1;
	len_mlxmap0 = ft_strnlen(mlx->map[1]);
	while (mlx->map[i])
	{
		if (len_mlxmap0 != ft_strnlen(mlx->map[i]))
		{
			printf("%d : %d i : %d\n", len_mlxmap0, ft_strnlen(mlx->map[i]), i);
			return false;
		}
		i++;
	}
	if ((len_mlxmap0 < 4) || (i < 3))
	{
		if ((len_mlxmap0 == 3 && i < 4) || (len_mlxmap0 < 5 && i == 2)) //taille map min
			flag = 1;
		if (flag == 0)
			return false;
	}
	if (verif_walls(mlx) == false)
	 	return false;
	if (verif_content(mlx) == false)
		return false;
	x = mlx->starter_P_x;
	y = mlx->starter_P_y;
	flood_fill(mlx, x, y);
	if (!(mlx->found_collectible == mlx->tot_collectible && mlx->found_exit == true))
		return false;
	return true;
}

bool ft_map_parsing(t_mlx_struct *mlx)
{
    char    *map_line;
	int     nblines;
    int     fd;
    int     j;

    map_line = "0";
    fd = open("map.ber", O_RDWR);
    nblines = 0;
    while (get_next_line(fd) != NULL)
		nblines++;
	mlx->win_height = nblines * 64;
    mlx->map = (char **)malloc(sizeof(char *) * (nblines + 1));
    if(mlx->map == NULL)
        return false;
    fd = open("map.ber", O_RDWR);
    j = 1;
    while(j - 1 <= nblines)
    {
        map_line = get_next_line(fd);
        mlx->map[j] = map_line;
        j++;
    }
	free(map_line);
	mlx->win_width = (ft_strlen(mlx->map[1]) - 1) * 64;
	return true;
}

// TODO --------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

int	ft_map_display(t_mlx_struct *mlx)
{
	// line = 0;
	// col = 1;
	mlx->y = 64;
	while (mlx->map[mlx->y / 64])
	{
		if (mlx->map[mlx->y / 64][mlx->x / 64] == '1')
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->wall, mlx->x, mlx->y);
			mlx->x += 64;
		}
		else if (mlx->map[mlx->y / 64][mlx->x / 64] == '0')
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->x, mlx->y);
			mlx->x += 64;
		}
		else if (mlx->map[mlx->y / 64][mlx->x / 64] == 'C')
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->collectible, mlx->x, mlx->y);
			mlx->x += 64;
		}
		else if (mlx->map[mlx->y / 64][mlx->x / 64] == 'E')
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->x, mlx->y);
			mlx->x += 64;
		}
		else if (mlx->map[mlx->y / 64][mlx->x / 64] == 'P')
		{
			mlx->map[mlx->y / 64][mlx->x / 64] = '0';
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->x, mlx->y);
			mlx->player_x = mlx->x;
			mlx->player_y = mlx->y - 64;
			mlx->x += 64;
		}
		else if (mlx->map[mlx->y / 64][mlx->x / 64] == '\n' || mlx->map[mlx->y / 64][mlx->x / 64] == '\0')
		{
			mlx->x = 0;
			mlx->y += 64;
		}
	}
	return (0);
}

// ! PLAYER_MOVEMENT--------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

int	walk_up(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) - 1][mlx->player_x / 64] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "sprites/player_back64x64.xpm", &mlx->img_width, &mlx->img_height);
	mlx->player_y -= 64;
	return (0);
}

int	walk_down(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "sprites/player_front64x64.xpm", &mlx->img_width, &mlx->img_height);
	mlx->player_y += 64;
	return (0);
}

int	walk_left(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64)] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player_x -= 64;
	return (0);
}

int	walk_right(t_mlx_struct *mlx)
{
	printf("%d steps\n", ++mlx->tot_moves);
	if (!(mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64)] == 'E'))
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sol, mlx->player_x, mlx->player_y);
	if (mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->exit, mlx->player_x, mlx->player_y);
	if(mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] == 'C')
		mlx->map[(mlx->player_y / 64) + 1][mlx->player_x / 64] = 'X';
	mlx->player_x += 64;
	return (0);
}

// ! KEYPRESS---------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

int	keypress_W(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[mlx->player_y / 64][mlx->player_x / 64] == '0' || (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'X')))
		walk_up(mlx);
	else if (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'C')
	{
		mlx->found_collectible++;
		walk_up(mlx);
	}
	else if (mlx->map[mlx->player_y / 64][mlx->player_x / 64] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
		{
			printf("Congratulations, You won !\nPress W A S D or ESC to close the game\nYou've completed it in : ");
			mlx->end = true;
		}
		walk_up(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress_A(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == '0') || (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'X'))
		walk_left(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'C')
	{
		mlx->found_collectible++;
		walk_left(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) - 1] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
		{
			printf("Congratulations, You won !\nPress W A S D or ESC to close the game\nYou've completed it in : ");
			mlx->end = true;
		}
		walk_left(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress_S(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == '0') || (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'X'))
		walk_down(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'C')
	{
		mlx->found_collectible++;
			walk_down(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 2][mlx->player_x / 64] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
		{
			printf("Congratulations, You won !\nPress W A S D or ESC to close the game\nYou've completed it in : ");
			mlx->end = true;
		}
		walk_down(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress_D(t_mlx_struct *mlx)
{
	if (mlx->end == true)
		ft_free_endgame(mlx);
	if ((mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == '0') || (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'X'))
		walk_right(mlx);
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'C')
	{
		mlx->found_collectible++;
		walk_right(mlx);
	}
	else if (mlx->map[(mlx->player_y / 64) + 1][(mlx->player_x / 64) + 1] == 'E')
	{
		if (mlx->found_collectible == mlx->tot_collectible)
		{
			printf("Congratulations, You won !\nPress W A S D or ESC to close the game\nYou've completed it in : ");
			mlx->end = true;
		}
		walk_right(mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->player_x, mlx->player_y);
	return (0);
}

int	keypress(int keypress, t_mlx_struct *mlx)
{
	if(keypress == ESC)
		ft_free_endgame(mlx);
	if(keypress == W)
		keypress_W(mlx);
	if(keypress == A)
		keypress_A(mlx);
	if(keypress == S)
		keypress_S(mlx);
	if(keypress == D)
		keypress_D(mlx);
	return (0);
}

// ! SO_LONG----------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------

int	main(void)
{
	t_mlx_struct	mlx;

	mlx.found_exit = false;
	mlx.tot_collectible = 0;
	mlx.found_collectible = 0;
	mlx.tot_moves = 0;
	mlx.x = 0;
	mlx.y = 0;
	mlx.img_width = 32;
	mlx.img_height = 32;
	mlx.end = false;
	if (ft_map_parsing(&mlx) == false)
	{
		write(2, "Error\nMap non valide !\n", 23);
		ft_free_endgame(&mlx);
		return (1);
	}
	if (verif_input(&mlx) == false)
	{
		write(2, "Error\nMap non valide !\n", 23);
		ft_free_endgame(&mlx);
		return (1);
	}
	ft_map_parsing(&mlx);
	mlx.found_collectible = 0;
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
	{
		write(2, "Error\nprobleme d'initialisation minilibx veuillez reessayer\n", 60);
		ft_free_endgame(&mlx);
		return (1);
	}
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_width, mlx.win_height, "chasser_pigeon_aller_dans_tori_lejeu.");
	if (mlx.win_ptr == NULL)
	{
		write(2, "Error\nprobleme de creation de la fenetre veuillez reessayer\n", 60);
		ft_free_endgame(&mlx);
		return (1);
	}
	mlx.player = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/player_front64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.collectible = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/collectible64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.exit = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/exit64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.sol = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/sol64x64.xpm", &mlx.img_width, &mlx.img_height);
	mlx.wall = mlx_xpm_file_to_image(mlx.mlx_ptr, "sprites/wall64x64.xpm", &mlx.img_width, &mlx.img_height);

	ft_map_display(&mlx);
	mlx_hook(mlx.win_ptr, DestroyNotify, StructureNotifyMask, ft_free_endgame, &mlx);
	mlx_key_hook(mlx.win_ptr, keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	ft_free_endgame(&mlx);
	return (0);
}
