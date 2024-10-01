#include <stdbool.h>
#include<stdio.h>
#include <fcntl.h>
#include  "mlx.h"
#include "gnl/get_next_line.h"

    int     nblines;

int ft_strnlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0 && str[i] != 10)
		i++;
	return (i);
}


bool verif_input(t_mlx_struct *mlx)
{
	int	i;
	int flag;
	int	len_mlxmap0;
		int j = 1;

	flag = 0;
	i = 0;
    while(mlx->map[j])
    {
        i = 0;
        while(mlx->map[j][i])
        {
            printf("%d ", mlx->map[j][i]);
            i++;
        }
        j++;
        printf("\n");
    }
    printf("\n");
    i = 1;
	len_mlxmap0 = ft_strnlen(mlx->map[1]);
	while (mlx->map[i])
	{
		if (len_mlxmap0 != ft_strnlen(mlx->map[i]))
		{
			// printf("%d : %d -- ligne n : %d\n", len_mlxmap0, ft_strnlen(mlx->map[i]), i);
            printf("i : %d nblines : %d\n", i, nblines);
				return false;
		}
		i++;
	}
	if ((len_mlxmap0 < 4) || (i < 3))
	{
		if ((len_mlxmap0 == 3 && i < 4) || (len_mlxmap0 < 5 && i == 2)) //taille map min
			flag = 1;
		if (flag == 0)
		{
			printf("error code 2");
			return false;
		}
	}
	// if (verif_walls(mlx) == false)
	// 	return false;
	// if (verif_content(mlx) == false)
	// 	return false;
	//	mlx->map2 = mlx->map;
	// path_finding(mlx);
	// if (!(mlx->found_collectible == mlx->tot_collectible && mlx->found_exit == true))
		// return false;
	return true;
}

bool ft_map_parsing(t_mlx_struct *mlx)
{
    char    *map_line;
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
    while(j <= nblines)
    {
        map_line = get_next_line(fd);
        mlx->map[j] = map_line;
        j++;
    }

	if (verif_input(mlx) == false)
    	return false;
	return true;
}

int main(void)
{
    bool parsing;
    t_mlx_struct    mlx;

    parsing = ft_map_parsing(&mlx);
    if (parsing)
        printf("parsing true\n");
    else
        printf("parsing false\n");
}